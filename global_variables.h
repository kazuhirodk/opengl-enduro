#ifndef global_variables_h
#define global_variables_h

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
#include <time.h>

#define PI M_PI
#define false GL_FALSE
#define true GL_TRUE

typedef struct {
  GLfloat x, y, z;
  GLboolean cor ;
  GLfloat dx;
  GLboolean bot;
  GLfloat curve;
}tPoint, *Ponto ;

typedef struct {
  tPoint *point;
  size_t used;
  size_t size;
} Array;

extern GLfloat
  black[],   white[],   verde[],   verdeGrama[], verdeEsc[], azul[],     azulEsc[],    azulCeu[],
  amarelo[], furchsia[], rosa[],    rosaBri[],    abobora[],  ciano[],    marinho[],    fuligem[],
  roxo[],    jambo[],    laranja[], marrom[],     cinza[],    cinzaEsc[], cinzaFosco[], red[],
  cinzaClaro[], roadColorA[], roadColorB[], grassColorA[], grassColorB[], rundleColorA[], rundleColorB[];

GLint sw, sh, winPosX, winPosY;
GLfloat w_width, w_height;
GLfloat mouseX, mouseY, mouseClickX, mouseClickY;

//Camera
extern GLdouble theta, aspect, d_near, d_far;
extern GLdouble x_0,    y_0,    z_0,
                x_ref,  y_ref,  z_ref,
                V_x,    V_y,   V_z,
                xCam,   yCam,   zCam;

// Game
extern GLboolean anima, hasCollided;
extern GLint retreat, contaCor, voltaAnt;
GLint posQndoBateu, voltaAnt2,contaCor2, vetorEstrelasY[200], vetorEstrelasX[200];
GLfloat ambiente[5], position[4];
extern GLfloat pontuacao, posCeu, R, G, B;
extern GLchar score[12];

// Pista
Array Points;
GLfloat x, dx;
extern GLint trackSize, trackWidth;

// Teclas
extern GLboolean buttons[];

// Player
extern GLfloat s_car;
extern GLint pos;
extern GLfloat s_car, carPosX, turnCar, speed;

// Bot
extern GLfloat *botColor[], speed;
extern GLint posBot;
GLfloat rotBot;
GLint count, dxBot;

int main(int, char**);
void draw();
int isTouchingLeft();
int isTouchingRight();
void initArray(Array *a, size_t initialSize);
void insertArray(Array *a, tPoint element);
void freeArray(Array *a);
void Msg(char *string, GLfloat x, GLfloat y);
void screenMessage(char *string, GLfloat x, GLfloat y, GLfloat *cor);
void delay(float secs);
void FitWindow(GLsizei w, GLsizei h);
void InitScreen();
void moveMouse(int, int);
void MouseFunc(int, int, int, int);
void Keyboard(unsigned char, int, int);
void UpKeyboard(unsigned char, int, int);
void SpecialKeys(int, int, int);
void TimerFunc(int );
void Reshape(int, int);
void Msg(char *, GLfloat , GLfloat );
void Msg2(char *string, GLfloat x, GLfloat y, GLfloat *cor);
void drawCar(GLfloat *);
void drawBots(GLfloat *, GLint, GLint);
void drawTrack();
void drawSegment(GLfloat *cor, float x1, float z1, float y1, float x2, float z2, float y2, float w2);
void IdleFunc();
#endif
