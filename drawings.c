#include "global_variables.h"

void drawSegment(GLfloat *color, float x1, float y1, float z1,
                              float x2, float y2, float z2, float w){
  glColor3fv(color);
  glBegin(GL_QUADS);
    glVertex3f(x1-w,y1,z1);
    glVertex3f(x2-w,y2,z2);
    glVertex3f(x2+w,y2,z2);
    glVertex3f(x1+w,y1,z1);
  glEnd();
}

void drawTrack(){
  tPoint *p2, *p1;
  int n;
  x= 0;
  dx = 0;
  glPushMatrix();
  glTranslatef(skyPosition,0,-2000);
  for(int i = 0; i < 200; i++){
    glPushMatrix();
      glColor3f(R-B,G-B,1);
      glTranslatef(starsX[i],starsY[i],0);
      glutSolidSphere(3,10,10);
    glPopMatrix();
  }
  glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(0,-200,0);
    glTranslatef(1000,800*(R-B),0);
    glutSolidSphere(70,50,50);

  glPopMatrix();
  glPopMatrix();

  for(n = pos; n < pos+2500; n++){
    p1 = &(Points.point[(n-1)%trackSize]);
    p2 = &(Points.point[n%trackSize]);
    x += dx;
    dx += p2->curve;
    p2->x = x;

    drawSegment( p1->color? grassColorA : grassColorB,
                p1->x, p1->y-2, p1->z+pos-(n-1>=trackSize?trackSize:0),
                p2->x, p2->y-2, p2->z+pos-(n  >=trackSize?trackSize:0), trackWidth*200);
    drawSegment( p1->color? black : white,
                p1->x, p1->y-1, p1->z+pos-(n-1>=trackSize?trackSize:0),
                p2->x, p2->y-1, p2->z+pos-(n  >=trackSize?trackSize:0), trackWidth*1.2);
    drawSegment( p1->color? roadColorA: roadColorB,
                p1->x, p1->y,   p1->z+pos-(n-1>=trackSize?trackSize:0),
                p2->x, p2->y,   p2->z+pos-(n  >=trackSize?trackSize:0), trackWidth);
  }
  glutPostRedisplay();
}

void draw(){
  // buffer clear
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_COLOR_MATERIAL);

  glLightfv(GL_LIGHT1, GL_AMBIENT, ambience);

  GLfloat difusion[] = {1.0, 1.0, 1.0, 1.0};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, difusion);
  InitScreen();

  glPushMatrix();
  drawTrack();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(carPosX, 0,  -180);
    glTranslatef(0,0,-5);
    glRotatef(turnCar - Points.point[pos].curve * 1800, 0, 1, 0);
    glRotatef(-0.4*turnCar + Points.point[pos].curve * 2000, 0, 0, 1);
    glTranslatef(0,0, 5);
    glScalef(s_car, s_car, s_car);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    drawCar(red);
  glPopMatrix();

  for(int i = 0; i < trackSize; i+=991){
    glPushMatrix();
      if(count == 0){
        count++;
        dxBot = 0;
        drawBots(botColor[count], i, dxBot);
      }else if(count == 1){
        count++;
        dxBot = 35;
        drawBots(botColor[count], i, dxBot);
      }else if(count == 2){
        count++;
        dxBot = 0;
        drawBots(botColor[count], i, dxBot);
      }else if(count == 3){
        count = 0;
        dxBot = -35;
        drawBots(botColor[count], i, dxBot);
      }
    glPopMatrix();
  }

  if(!hasCollided){
    if(buttons[0] && animate){
      pos += (0.12 * speed);
      posBot += 0.01 * speed;
    }
    if((buttons[1] ) && animate){
      pos -= (0.12 * speed);
      posBot += 0.15 * speed;
      speed -= 0.02;
    }
    if(buttons[2] && !isTouchingLeft()){
      carPosX = carPosX >= -(trackWidth/2+30)? carPosX - 1.5 * speed/(15+(retreat*2)) : carPosX;
      if(turnCar < 0)
        turnCar = turnCar > 25 ? turnCar : turnCar + 1.5;
      turnCar = turnCar > 25 ? turnCar : turnCar + 0.8;
      if(animate) speed = speed > 1 ? speed + abs(carPosX) * 0.0001 * speed/(15+(retreat*2)) : 1;
    }
    if(buttons[3] && !isTouchingRight()){
      carPosX = carPosX <= trackWidth/2+30? carPosX + 1.5 * speed/(15+(retreat*2)) : carPosX;
      if(turnCar > 0)
        turnCar = turnCar < -25 ? turnCar : turnCar - 1.5;
      turnCar = turnCar < -25 ? turnCar : turnCar - 0.8;
      if(animate) speed = speed > 1 ? speed + abs(carPosX) * 0.0001 * speed/(15+(retreat*2)) : 1;
    }

    if(!buttons[2] && !buttons[3]){
      if(turnCar > 0){
        turnCar = turnCar * 0.92;
      }else if (turnCar < 0){
        turnCar = turnCar * 0.92;
      }
    }
  }
  while(pos >= trackSize)       pos -= trackSize;
  while(pos < 0)                pos += trackSize;
  while(posBot >= trackSize)    posBot -= trackSize;
  while(posBot < 0)             posBot += trackSize;

  screenMessage(scoreArray, -.7,.99, white);

  glFlush();
  glutSwapBuffers();
}
