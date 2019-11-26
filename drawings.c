#include "global_variables.h"

void DesenhaSeg(GLfloat *cor, float x1, float y1, float z1,
                              float x2, float y2, float z2, float w){
  glColor3fv(cor);
  glBegin(GL_QUADS);
    glVertex3f(x1-w,y1,z1);
    glVertex3f(x2-w,y2,z2);
    glVertex3f(x2+w,y2,z2);
    glVertex3f(x1+w,y1,z1);
  glEnd();
}

void DesenhaPista(){
  Ponto_t *p2, *p1;
  int n;
  x= 0;
  dx = 0;
  glPushMatrix();
  glTranslatef(posCeu,0,-2000);
  for(int i = 0; i < 200; i++){
    glPushMatrix();
      glColor3f(R-B,G-B,1);
      glTranslatef(vetorEstrelasX[i],vetorEstrelasY[i],0);
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
  // Points.point[posBot].bot = true;
  for(n = pos; n < pos+2500; n++){
    p1 = &(Points.point[(n-1)%tamPista]);
    p2 = &(Points.point[n%tamPista]);
    x += dx;
    dx += p2->curve;
    p2->x = x;

    DesenhaSeg( p1->cor? grassColorA : grassColorB,
                p1->x, p1->y-2, p1->z+pos-(n-1>=tamPista?tamPista:0),
                p2->x, p2->y-2, p2->z+pos-(n  >=tamPista?tamPista:0), larPista*200);
    DesenhaSeg( p1->cor? preto : branco,
                p1->x, p1->y-1, p1->z+pos-(n-1>=tamPista?tamPista:0),
                p2->x, p2->y-1, p2->z+pos-(n  >=tamPista?tamPista:0), larPista*1.2);
    DesenhaSeg( p1->cor? roadColorA: roadColorB,
                p1->x, p1->y,   p1->z+pos-(n-1>=tamPista?tamPista:0),
                p2->x, p2->y,   p2->z+pos-(n  >=tamPista?tamPista:0), larPista);
  }
  glutPostRedisplay();
}

void Desenha(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer
  glLoadIdentity();

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_COLOR_MATERIAL);

  glLightfv(GL_LIGHT1, GL_AMBIENT, ambiente);

  GLfloat difusao[]={1.0, 1.0, 1.0, 1.0};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, difusao);
  InitScreen();
  //Iluminacao
  // Pista
  glPushMatrix();
    DesenhaPista();
  glPopMatrix();
  // Player
  glPushMatrix();
    glTranslatef(carPosX, 0,  -180);
    glTranslatef(0,0,-5);
    glRotatef(turnCar - Points.point[pos].curve * 1800, 0, 1, 0);
    glRotatef(-0.4*turnCar + Points.point[pos].curve * 2000, 0, 0, 1);
    glTranslatef(0,0, 5);
    glScalef(s_car, s_car, s_car);
    glLightfv(GL_LIGHT0, GL_POSITION, posicao);
    DesenhaCarro(vermelho);
  glPopMatrix();

  for(int i = 0; i < tamPista; i+=991){
    glPushMatrix();
      if(contador == 0){
        contador++;
        dxBot = 0;
        DesenhaBots(corBot[contador], i, dxBot);
      }else if(contador == 1){
        contador++;
        dxBot = 35;
        DesenhaBots(corBot[contador], i, dxBot);
      }else if(contador == 2){
        contador++;
        dxBot = 0;
        DesenhaBots(corBot[contador], i, dxBot);
      }else if(contador == 3){
        contador = 0;
        dxBot = -35;
        DesenhaBots(corBot[contador], i, dxBot);
      }
    glPopMatrix();
  }

  // Verifica Teclas:
  if(!colidiu){
    if(botoes[0] && anima){
      pos += (0.12 * speed);
      posBot += 0.01 * speed;
    }
    if((botoes[1] ) && anima){
      pos -= (0.12 * speed);
      posBot += 0.15 * speed;
      speed -= 0.02;
    }
    if(botoes[2] && !isTouchingLeft()){ // impedir virar pra esquerda quando estiver fora da pista
      carPosX = carPosX >= -(larPista/2+30)? carPosX - 1.5 * speed/(15+(volta*2)): carPosX;
      if(turnCar < 0)
        turnCar = turnCar > 25 ? turnCar : turnCar + 1.5;
      turnCar = turnCar > 25 ? turnCar : turnCar + 0.8;
      if(anima) speed = speed > 1 ? speed + abs(carPosX) * 0.0001 * speed/(15+(volta*2)) : 1;
    }
    if(botoes[3] && !isTouchingRight()){ // impedir virar pra direita quando estiver fora da pista
      carPosX = carPosX <= larPista/2+30? carPosX + 1.5 * speed/(15+(volta*2)): carPosX;
      if(turnCar > 0)
        turnCar = turnCar < -25 ? turnCar : turnCar - 1.5;
      turnCar = turnCar < -25 ? turnCar : turnCar - 0.8;
      if(anima) speed = speed > 1 ? speed + abs(carPosX) * 0.0001 * speed/(15+(volta*2)): 1;
    }

    if(!botoes[2] && !botoes[3]){
      if(turnCar > 0){
        turnCar = turnCar * 0.92;
      }else if (turnCar < 0){
        turnCar = turnCar * 0.92;
      }
    }
  }
  while(pos >= tamPista)    pos -= tamPista;
  while(pos < 0)            pos += tamPista;
  while(posBot >= tamPista) posBot -= tamPista;
  while(posBot < 0)         posBot += tamPista;

  MsgGde(pontuacaoStr, -.7,.99, branco);

  glFlush();
  glutSwapBuffers();
}
