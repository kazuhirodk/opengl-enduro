#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include "global_variables.h"

void TimerFunc(int valor){
  int f = valor;
  if(hasCollided){
    if(crashPosition > 100) {
      hasCollided = false;
    }else{
      speed = 0.98 * speed > 8 ? 0.98 * speed : 2;
      pos = pos - 0.5;
      score -= 3;
      posBot += 2;
      if(turnCar > 0){
        turnCar = turnCar * 0.90;
      }else if (turnCar < 0){
        turnCar = turnCar * 0.90;
      }
      crashPosition++;
    }
  }
  else{
    pos += speed ;
  }
  posBot += 0.8*speed;

  if(score < 0){
    score = 0;
  }else if(!isTouchingRight() && !isTouchingLeft()){
    score += 0.2;
  }

  sprintf(scoreArray, "Velocidade: %.0f km/h                             Score: %.0f",(speed-1)*7, score);

  while(pos >= trackSize){
    pos -= trackSize;
    lap++;
  }
  while(pos < 0)            pos += trackSize;
  while(posBot >= trackSize) posBot -= trackSize;
  while(posBot < 0)         posBot += trackSize;

  if(lap != returnPrevious){
      returnPrevious = lap;
      colorCount = (colorCount+1) % 4;
  }
  if(colorCount == 3){
    B = ((float)(pos+0.1)/(float)trackSize);
    R = 2*B; G = 2*B;
    glClearColor(.0f, .0f, 1.0 - B, .0f);
  }
  else if(colorCount == 2){
    glClearColor(.0f, .0f, 1.0, .0f);
  }
  else if(colorCount == 1){
    B = ((float)pos/(float)trackSize);
    R = 1; G = 1;
    glClearColor(.0f, .0f, B, .0f);
  }
  else{
    glClearColor(.0f, .0f, 0, .0f);
  }

  if(speed<15+(lap*2)) speed += 0.005;
  if(speed<10) speed += 0.005;
  if(speed<5) speed += 0.005;

  if(Points.point[pos].curve > 0 ){
    if(carPosX >= -(trackWidth/2+25))
      carPosX = carPosX-1.3*speed/(15+(lap*2));
  }
  if(Points.point[pos].curve < 0 ){
    if(carPosX <= trackWidth/2+25)
      carPosX = carPosX+1.3*speed/(15+(lap*2));
  }

  if(isTouchingRight() || isTouchingLeft()){
    pos -= (0.12 * speed);
    posBot += 0.15 * speed;
    speed -= 0.02;
    score -= 1;
  }
  if(animate && Points.point[pos].curve > 0.0){
    skyPosition -= speed;
  }
  if(animate && Points.point[pos].curve < 0.0){
    skyPosition += speed;
  }
  InitScreen();
  if(animate)
    glutTimerFunc(5, TimerFunc, f);
  glutPostRedisplay();
}

void drawBots(GLfloat *color, GLint dzBot, GLint dx){
  if((posBot + dzBot) > trackSize){
      dzBot = -(trackSize - dzBot);
  }
  GLint da = abs(Points.point[posBot+dzBot].z - Points.point[pos].z);
  GLint db = abs(trackSize - abs(Points.point[pos].z) + abs(Points.point[posBot+dzBot].z));
  GLint distBotfromPlayer = da > db ? db : da;
  glPushMatrix();
  glTranslatef(Points.point[posBot+dzBot].x + dx, 0,Points.point[posBot+dzBot].z+pos-(Points.point[posBot+dzBot].z+pos > 0 ? trackSize : 0));
  glTranslatef(0,0,-5);
  glRotatef(- ((int)(Points.point[posBot+dzBot].curve*1000) ? Points.point[posBot+dzBot].curve : Points.point[pos].curve) * 1200 * (distBotfromPlayer/35), 0, 1, 0);
  glRotatef(Points.point[posBot+dzBot].curve * 2000, 0, 0, 1);
  glTranslatef(0,0,+5);
  glScalef(s_car, s_car, s_car);
  drawCar(color);
  glPopMatrix();

  if(Points.point[pos].curve == 0.0){
    if( (pos > (posBot+dzBot-220) && pos < posBot+dzBot-140) && (
      (carPosX - 18 <= dx && carPosX >= dx) ||
      (carPosX + 18 >= dx && carPosX <= dx) )
    )
    {
      hasCollided = true;
      crashPosition = 0;
      score -= 3;
    }
}else if(Points.point[pos].curve > 0.0){
    if( (pos > (posBot+dzBot-220) && pos < posBot+dzBot-140) && (
        (carPosX - 26 <= dx && carPosX >= dx) ||
        (carPosX + 10 >= dx && carPosX <= dx) )
    )
    {
      hasCollided = true;
      crashPosition = 0;
      score -= 3;
    }
}else if(Points.point[pos].curve < 0.0){
    if( (pos > (posBot+dzBot-220) && pos < posBot+dzBot-140) && (
      (carPosX - 10 <= dx && carPosX >= dx) ||
      (carPosX + 26 >= dx && carPosX <= dx) )
    )
    {
      hasCollided = true;
      crashPosition = 0;
      score -= 3;
    }
  }
  glutPostRedisplay();
}

int main(int argc, char *argv[]){
  srand(time(NULL));
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  sw = glutGet(GLUT_SCREEN_WIDTH);
  sh = glutGet(GLUT_SCREEN_HEIGHT);
  winPosX = (sw-sh)/2; winPosY = 0;
  position[0] = 0.0; position[1] =  22.0; position[2] = -40.0; position[3] = 1.0;
  glutInitWindowPosition(winPosX, winPosY);
  glutInitWindowSize(sh, sh);
  glutSetKeyRepeat(1);
  GLint c = 0;
  GLboolean flagCor = false;
  x = 0; dx = 0;
  initArray(&Points, trackSize+2);
  for(int j = 0; j < 200; j++){
    starsX[j] = (rand()%10000)-5000;
  }
  for(int j = 0; j < 200; j++){
    starsY[j] = rand()%1000;
  }
  for(int i = 0; i < trackSize; i++){
    tPoint point;
    point.x = 0;
    point.y = 0;
    point.z = -i ;
    point.curve = 0;

    if (c == 50){
      c = 0;
      flagCor = flagCor? false : true;
    }else c++;
    point.color =   flagCor;

    if( i > 1800 && i < 2800) point.curve = 0.001;
    if( i > 3800 && i < 4800) point.curve = -0.001;
    if( i > 5800 && i < 9000) point.curve = 0.001;
    if( i > 10500 && i < 13700) point.curve = -0.001;

    insertArray(&Points, point);
  }

  glutCreateWindow("CG TRAB-FINAL - ENDURO");
    FitWindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutKeyboardUpFunc(UpKeyboard);
    glutSpecialFunc(SpecialKeys);
    glutTimerFunc(0,TimerFunc,1);
    glutIdleFunc(IdleFunc);
    glutDisplayFunc(draw);
    glClearColor(.0f, .0f, .0f, .0f);
    glEnable(GL_DEPTH_TEST);
    InitScreen();
  glutMainLoop();
}
