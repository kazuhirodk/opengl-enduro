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
#include <unistd.h>
#include <time.h>

GLfloat yellow[]={1,1,0}, blue[]={0,0,1}, white[]={1,1,1}, red[]={1,0,0},
        pink[]={1,.75,.8}, green[]={0,1,0}, black[]={0,0,0},
        roadColorA[]={.42,.42,.42}, roadColorB[]={.41,.41,.41},
        grassColorA[]={.06,.78,.06}, grassColorB[]={0.0,.6,0.0};

GLboolean buttons[] = {false, false, false, false};
GLdouble theta=90,  aspect=1,   d_near=1, d_far=1800;
GLdouble x_0=0,     y_0=40.0,   z_0= -100,
         x_ref=0,   y_ref=0,    z_ref=-200,
         V_x=0,     V_y=1,      V_z = 0,
         xCam = 0,  yCam= 0,    zCam=0;

GLboolean anima = false, hasCollided = false;
GLint colorCount = 0, returnPrevious = 0;
GLfloat score = 0, skyPosition = 0, R = 1, G = 1, B = 0;
GLchar scoreArray[12];
GLfloat posAct = -1.9, Ytitulo1 = 0, Xtitulo1 = 0;
GLboolean flagIntro = false, flagIntro2= false;
GLboolean flagIntro3 = false, flagIntro4 = false;

GLint trackSize = 19000, trackWidth = 80, retreat = 0;

GLfloat s_car = 1;
GLint pos = 0;
GLfloat carPosX = 0.0, turnCar = 0, speed = 1;

GLint posBot = 500;
GLfloat *botColor[] = {yellow, green, blue, pink};
GLint teste = 0;

void freeArray(Array *a) {
  free(a->point);
  a->point = NULL;
  a->used = a->size = 0;
}

void delay(float secs){
	float end = clock()/CLOCKS_PER_SEC + secs;
	while((clock()/CLOCKS_PER_SEC) < end);
}

void Msg(char *string, GLfloat x, GLfloat y){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(-1.0,1.0,-1.0,1.0);
    glRasterPos2f(x,y);
    while(*string)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*string++);
  glutPostRedisplay();
}
void screenMessage(char *string, GLfloat x, GLfloat y, GLfloat *color){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(-1.0,1.0,-1.0,1.0);
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glColor3fv(color);
  glRasterPos2f(x,y);
  while(*string)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*string++);
  glutPostRedisplay();
}
void Msg2(char *string, GLfloat x, GLfloat y, GLfloat *color){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 500.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(10, 10, 10, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Altere aqui para visualizar diferentes estilos, seta 3 item para algo 10 pra tu ver
  glScalef(.005,.005,.005); // word size
  glTranslatef(-300+x, y, 0);

  glColor3fv(color);
  glLineWidth(15.0);
  while(*string)
    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,*string++);
  glLineWidth(1.0);
  glutPostRedisplay();
}

void InitScreen(){
  w_width = glutGet(GLUT_WINDOW_WIDTH);
  w_height = glutGet(GLUT_WINDOW_HEIGHT);

  glMatrixMode(GL_PROJECTION); //define que a matrix é a de projeção
  glLoadIdentity(); //carrega a matrix de identidade
  gluPerspective(theta, aspect, d_near, d_far);

  glPushMatrix();
  glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view
  glLoadIdentity(); //carrega a matrix de identidade
  gluLookAt(x_0,   y_0,   z_0,
            x_ref, y_ref, z_ref,
            V_x,   V_y,   V_z);
  glPopMatrix();
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambience);

  //Controle do ambience
  if(retreat != returnPrevious2){
    returnPrevious2 = retreat;
    colorCount2 = (colorCount2+1) % 4;
  }
  if(colorCount2 == 3){
    ambience[0] = 1.0 - B;
    ambience[1] = 1.0 - B;
    ambience[2] = 1.0 - B;
    ambience[4] = 1.0;
  }
  else if(colorCount2 == 2){
    ambience[0] = 1.0;
    ambience[1] = 1.0;
    ambience[2] = 1.0;
    ambience[4] = 1.0;
  }
  else if(colorCount2 == 1){
    ambience[0] = B;
    ambience[1] = B;
    ambience[2] = B;
    ambience[4] = 1.0;
  }
  else{
    ambience[0] = 0.0;
    ambience[1] = 0.0;
    ambience[2] = 0.0;
    ambience[4] = 1.0;
  }
  printf("count: %d  R: %.3f  G: %.3f  B: %.3f\n", colorCount2, R, G, B);
}
void FitWindow(GLsizei w, GLsizei h){
  if (w >= h)
    glutReshapeWindow(h, h);
  else
    glutReshapeWindow(w, w);
}

void IdleFunc(){
  glutPostRedisplay();
}

void Reshape(int w, int h){
  if (w >= h)
    glViewport(0, 0, (GLsizei)h, (GLsizei)h) ;
  else
    glViewport(0, 0, (GLsizei)w, (GLsizei)w) ;
  glMatrixMode(GL_PROJECTION) ;
  glLoadIdentity() ;

  InitScreen();
}

int isTouchingLeft(){
  return carPosX >= -(trackWidth/2+30) ? 0 : 1;
}

int isTouchingRight(){
  return carPosX <= trackWidth/2+30 ? 0 : 1;
}

void moveMouse(int x, int y){
  y = w_height - y;
  mouseX = (double)(((double)y/(double)w_height)*2.0 - 1.0);
  mouseY = (double)(((double)x/(double)w_width)*2.0 -1.0);
}

void MouseFunc(int botao, int estado, int x, int y){
  switch (botao){
    case GLUT_LEFT_BUTTON :
      if (estado == GLUT_DOWN){
        y = w_height - y;
        mouseClickX = (float)(((float)x/(float)w_width)*2.0 -1.0);
        mouseClickY = (float)(((float)y/(float)w_height)*2.0 - 1.0);
      }
      break;
    default :
      break;
  }
}

void Keyboard (unsigned char key, int x, int y){
  int timerID = 0;
  switch (key){
    case 27:            // ESC
      exit (0);
      break;
    case 13:            // ENTER
      break;
    case 32:            // SPACE
      anima = anima ? false : true;
      TimerFunc(timerID);
      speed = 1;
      break;
    case 'w':
    case 'W':  buttons[0] = true;  break;
    case 's':
    case 'S':  buttons[1] = true;  break;
    case 'a':
    case 'A':  buttons[2] = true;  break;
    case 'd':
    case 'D':  buttons[3] = true;  break;

    default: break;
  }
  InitScreen();
}

void UpKeyboard (unsigned char key, int x, int y){
  switch (key){
    case 'w':
    case 'W':  buttons[0] = false;  break;
    case 's':
    case 'S':  buttons[1] = false;  break;
    case 'a':
    case 'A':  buttons[2] = false;  break;
    case 'd':
    case 'D':  buttons[3] = false;  break;
  }
}

void SpecialKeys (int key, int x, int y){
  switch(key){
    case GLUT_KEY_RIGHT:
      carPosX += 1;
      printf("carPosX: %g\n", carPosX);
      break;
    case GLUT_KEY_LEFT:
      carPosX -= 1;
      printf("carPosX: %g\n", carPosX);
      break;
    case GLUT_KEY_UP:
      pos += 1;
      printf("pos: %d - posBot: %d\n", pos, posBot);
      break;
    case GLUT_KEY_DOWN:
      pos -= 1;
      printf("pos: %d - posBot: %d\n", pos, posBot);
      break;
    default:
      break;
  }
  printf("posBot: %d\n", posBot);
}
