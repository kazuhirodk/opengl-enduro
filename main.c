#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
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
//    sprintf(scoreArray, "Speed: %.0f km/h                             Points: %.0f",(speed-1)*7, score);

  while(pos >= trackSize){
    pos -= trackSize;
    retreat++;
  }
  while(pos < 0)            pos += trackSize;
  while(posBot >= trackSize) posBot -= trackSize;
  while(posBot < 0)         posBot += trackSize;
  //Controle do céu
  if(retreat != returnPrevious){
      returnPrevious = retreat;
      colorCount = (colorCount+1) % 4;
  }
  if(colorCount == 3){
    B = ((float)(pos+0.1)/(float)trackSize);// > 0.0 ? ((float)(pos+0.1)/(float)trackSize): 0.0;
    R = 2*B; G = 2*B;
    glClearColor(.0f, .0f, 1.0 - B, .0f);
  }
  else if(colorCount == 2){
    glClearColor(.0f, .0f, 1.0, .0f);
  }
  else if(colorCount == 1){
    B = ((float)pos/(float)trackSize);// > 0.0 ? ((float)pos/(float)trackSize): 0.0;
    R = 1; G = 1;
    glClearColor(.0f, .0f, B, .0f);
  }
  else{
    glClearColor(.0f, .0f, 0, .0f);
  }
  //Controle de velocidade
  // if((int)pos%trackSize == 0) retreat++; //Cada retreat no mapa tem trackSize posições.
  if(speed<15+(retreat*2)) speed += 0.005;//Aceleracao maxima 35, aumenta em 2 para cada retreat.
  if(speed<10) speed += 0.005;			//Aceleracao 0.2 quando abaixo de speed 20.
  if(speed<5) speed += 0.005;			//Aceleracao 0.3 quando abaixo de speed 05.

  //Inércia nas curvas
  if(Points.point[pos].curve > 0 ){ //Curva para a direita.
    if(carPosX >= -(trackWidth/2+25))
      carPosX = carPosX-1.3*speed/(15+(retreat*2));
  }
  if(Points.point[pos].curve < 0 ){ //Curva para a esquerda.
    if(carPosX <= trackWidth/2+25)
      carPosX = carPosX+1.3*speed/(15+(retreat*2));
  }
  // verifica se o carro está tocando alguma das bordas e desacelera
  if(isTouchingRight() || isTouchingLeft()){
    pos -= (0.12 * speed);
    posBot += 0.15 * speed;
    speed -= 0.02;
    score -= 1;
  }
  if(anima && Points.point[pos].curve > 0.0){
    skyPosition -= speed;
  }
  if(anima && Points.point[pos].curve < 0.0){
    skyPosition += speed;
  }
  InitScreen();
  if(anima)
    glutTimerFunc(5, TimerFunc, f);
  glutPostRedisplay();
}

void drawBots(GLfloat *color, GLint dzBot, GLint dx){
  // Verifica se posBot+dzBot esta dentro do range (0-trackSize)
  if((posBot + dzBot) > trackSize){
      dzBot = -(trackSize - dzBot);
  }
  GLint da = abs(Points.point[posBot+dzBot].z - Points.point[pos].z);
  GLint db = abs(trackSize - abs(Points.point[pos].z) + abs(Points.point[posBot+dzBot].z)); // Se um ja reiniciou a pista e o outro nao
  GLint distBotfromPlayer = da > db ? db : da;        // Distancia real entre o bot e o player
  glPushMatrix();     // BOT
  glTranslatef(Points.point[posBot+dzBot].x + dx, 0,Points.point[posBot+dzBot].z+pos-(Points.point[posBot+dzBot].z+pos > 0 ? trackSize : 0));
  glTranslatef(0,0,-5);       // Calculo de quanto o bot vira nas curvas em função da distancia entre ele e o bot e se o player esta ou nao em curva
  glRotatef(- ((int)(Points.point[posBot+dzBot].curve*1000) ? Points.point[posBot+dzBot].curve : Points.point[pos].curve) * 1200 * (distBotfromPlayer/35), 0, 1, 0);
  glRotatef(Points.point[posBot+dzBot].curve * 2000, 0, 0, 1);
  glTranslatef(0,0,+5);
  glScalef(s_car, s_car, s_car);
  drawCar(color);
  glPopMatrix();

  if(Points.point[pos].curve == 0.0){
    if( (pos > (posBot+dzBot-220) && pos < posBot+dzBot-140) && (              // estao na mesma posicao em z
      (carPosX - 18 <= dx && carPosX >= dx) || // player do lado direito do bot
      (carPosX + 18 >= dx && carPosX <= dx) )  // player do lado esquerdo do bot
    )
    {
      hasCollided = true;
      crashPosition = 0;
      score -= 3;
    }
}else if(Points.point[pos].curve > 0.0){
    if( (pos > (posBot+dzBot-220) && pos < posBot+dzBot-140) && (              // estao na mesma posicao em z
        (carPosX - 26 <= dx && carPosX >= dx) || // player do lado direito do bot
        (carPosX + 10 >= dx && carPosX <= dx) )  // player do lado esquerdo do bot
    )
    {
      hasCollided = true;
      crashPosition = 0;
      score -= 3;
    }
}else if(Points.point[pos].curve < 0.0){
    if( (pos > (posBot+dzBot-220) && pos < posBot+dzBot-140) && (              // estao na mesma posicao em z
      (carPosX - 10 <= dx && carPosX >= dx) || // player do lado direito do bot
      (carPosX + 26 >= dx && carPosX <= dx) )  // player do lado esquerdo do bot
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

    //Cor
    if (c == 50){
        c = 0;
        flagCor = flagCor? false : true;
    }else c++;
    point.color =   flagCor;

    // Curvas
    if( i > 1800 && i < 2800) point.curve = 0.001;
    if( i > 3800 && i < 4800) point.curve = -0.001;
    if( i > 5800 && i < 9000) point.curve = 0.001;
    if( i > 10500 && i < 13700) point.curve = -0.001;
    // if( i > 13800 && i < 15800) point.curve = 0.001;
    // if( i > 16800 && i < 19800) point.curve = -0.001;

    insertArray(&Points, point);
  }

  glutCreateWindow("CG TRAB-FINAL - ENDURO");
    FitWindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glutReshapeFunc(Reshape);
    glutPassiveMotionFunc(moveMouse);
    glutMouseFunc(MouseFunc);
    glutKeyboardFunc(Keyboard);
    glutKeyboardUpFunc(UpKeyboard);
    glutSpecialFunc(SpecialKeys);
    glutTimerFunc(0,TimerFunc,1);
    glutIdleFunc(IdleFunc);
    // glutDisplayFunc(desenha_actvision);
    glutDisplayFunc(draw);
    glClearColor(.0f, .0f, .0f, .0f); //define a color de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
    InitScreen();
  glutMainLoop();
}
