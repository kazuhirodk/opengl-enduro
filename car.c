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

void drawCar(GLfloat *color){
  glPushMatrix();
  // front left wheel
  glPushMatrix();
  glTranslatef(-7.0,0.0,-33.0);
  // front right wheel
  glRotatef(turnCar - Points.point[pos].curve * 2000, 0, 1, 0);
  glTranslatef(7.0,0.0,33.0);
  glColor3f(0.05, 0.05, 0.05);
  glBegin(GL_QUADS);
    glVertex3f(-8.5, 0.0, -31.8); glVertex3f(-5.5, 0.0, -31.8);
    glVertex3f(-5.5, 0.0, -34.2); glVertex3f(-8.5, 0.0, -34.2);

    glVertex3f(-8.5, 0.0, -34.2); glVertex3f(-5.5, 0.0, -34.2);
    glVertex3f(-5.5, 2.1, -35.9); glVertex3f(-8.5, 2.1, -35.9);

    glVertex3f(-8.5, 2.1, -35.9); glVertex3f(-5.5, 2.1, -35.9);
    glVertex3f(-5.5, 5.0, -35.9); glVertex3f(-8.5, 5.0, -35.9);

    glVertex3f(-8.5, 5.0, -35.9); glVertex3f(-5.5, 5.0, -35.9);
    glVertex3f(-5.5, 7.1, -34.2); glVertex3f(-8.5, 7.1, -34.2);

    glVertex3f(-8.5, 7.1, -34.2); glVertex3f(-5.5, 7.1, -34.2);
    glVertex3f(-5.5, 7.1, -31.8); glVertex3f(-8.5, 7.1, -31.8);

    glVertex3f(-8.5, 7.1, -31.8); glVertex3f(-5.5, 7.1, -31.8);
    glVertex3f(-5.5, 5.0, -30.1); glVertex3f(-8.5, 5.0, -30.1);

    glVertex3f(-8.5, 5.0, -30.1); glVertex3f(-5.5, 5.0, -30.1);
    glVertex3f(-5.5, 2.1, -30.1); glVertex3f(-8.5, 2.1, -30.1);

    glVertex3f(-8.5, 2.1, -30.1); glVertex3f(-5.5, 2.1, -30.1);
    glVertex3f(-5.5, 0.0, -31.8); glVertex3f(-8.5, 0.0, -31.8);
  glEnd();

  // left side
  glBegin(GL_POLYGON);
    glVertex3f(-8.5, 0.0, -31.8); glVertex3f(-8.5, 0.0, -34.2);
    glVertex3f(-8.5, 2.1, -35.9); glVertex3f(-8.5, 5.0, -35.9);
    glVertex3f(-8.5, 7.1, -34.2); glVertex3f(-8.5, 7.1, -31.8);
    glVertex3f(-8.5, 5.0, -30.1); glVertex3f(-8.5, 2.1, -30.1);
  glEnd();

  glPopMatrix();

  // front right wheel
  glColor3f(0.05, 0.05, 0.05);
  glPushMatrix();
  glTranslatef(7.0,0.0,-33.0);
  glRotatef(turnCar - Points.point[pos].curve * 2000, 0, 1, 0);
  glTranslatef(-7.0,0.0,33.0);
  glBegin(GL_QUADS);
    glVertex3f(5.5, 0.0, -31.8); glVertex3f(8.5, 0.0, -31.8);
    glVertex3f(8.5, 0.0, -34.2); glVertex3f(5.5, 0.0, -34.2);

    glVertex3f(5.5, 0.0, -34.2); glVertex3f(8.5, 0.0, -34.2);
    glVertex3f(8.5, 2.1, -35.9); glVertex3f(5.5, 2.1, -35.9);

    glVertex3f(5.5, 2.1, -35.9); glVertex3f(8.5, 2.1, -35.9);
    glVertex3f(8.5, 5.0, -35.9); glVertex3f(5.5, 5.0, -35.9);

    glVertex3f(5.5, 5.0, -35.9); glVertex3f(8.5, 5.0, -35.9);
    glVertex3f(8.5, 7.1, -34.2); glVertex3f(5.5, 7.1, -34.2);

    glVertex3f(5.5, 7.1, -34.2); glVertex3f(8.5, 7.1, -34.2);
    glVertex3f(8.5, 7.1, -31.8); glVertex3f(5.5, 7.1, -31.8);

    glVertex3f(5.5, 7.1, -31.8); glVertex3f(8.5, 7.1, -31.8);
    glVertex3f(8.5, 5.0, -30.1); glVertex3f(5.5, 5.0, -30.1);

    glVertex3f(5.5, 5.0, -30.1); glVertex3f(8.5, 5.0, -30.1);
    glVertex3f(8.5, 2.1, -30.1); glVertex3f(5.5, 2.1, -30.1);

    glVertex3f(5.5, 2.1, -30.1); glVertex3f(8.5, 2.1, -30.1);
    glVertex3f(8.5, 0.0, -31.8); glVertex3f(5.5, 0.0, -31.8);
  glEnd();

  // right side
  glBegin(GL_POLYGON);
    glVertex3f(8.5, 0.0, -31.8); glVertex3f(8.5, 0.0, -34.2);
    glVertex3f(8.5, 2.1, -35.9); glVertex3f(8.5, 5.0, -35.9);
    glVertex3f(8.5, 7.1, -34.2); glVertex3f(8.5, 7.1, -31.8);
    glVertex3f(8.5, 5.0, -30.1); glVertex3f(8.5, 2.1, -30.1);
  glEnd();

  glPopMatrix();

  // back left wheel
  glColor3f(0.05, 0.05, 0.05);
  glBegin(GL_QUADS);
    glVertex3f(-9.0, 0.0, -5.5);   glVertex3f(-6.0, 0.0, -5.5);
    glVertex3f(-6.0, 0.0, -8.5);   glVertex3f(-9.0, 0.0, -8.5);

    glVertex3f(-9.0, 0.0, -8.5);   glVertex3f(-6.0, 0.0, -8.5);
    glVertex3f(-6.0, 2.1, -10.5);  glVertex3f(-9.0, 2.1, -10.5);

    glVertex3f(-9.0, 2.1, -10.5);  glVertex3f(-6.0, 2.1, -10.5);
    glVertex3f(-6.0, 5.0, -10.5);  glVertex3f(-9.0, 5.0, -10.5);

    glVertex3f(-9.0, 5.0, -10.5);  glVertex3f(-6.0, 5.0, -10.5);
    glVertex3f(-6.0, 7.1, -8.5);   glVertex3f(-9.0, 7.1, -8.5);

    glVertex3f(-9.0, 7.1, -8.5);   glVertex3f(-6.0, 7.1, -8.5);
    glVertex3f(-6.0, 7.1, -5.5);   glVertex3f(-9.0, 7.1, -5.5);

    glVertex3f(-9.0, 7.1, -5.5);   glVertex3f(-6.0, 7.1, -5.5);
    glVertex3f(-6.0, 5.0, -3.5);   glVertex3f(-9.0, 5.0, -3.5);

    glVertex3f(-9.0, 5.0, -3.5);   glVertex3f(-6.0, 5.0, -3.5);
    glVertex3f(-6.0, 2.1, -3.5);   glVertex3f(-9.0, 2.1, -3.5);

    glVertex3f(-9.0, 2.1, -3.5);   glVertex3f(-6.0, 2.1, -3.5);
    glVertex3f(-6.0, 0.0, -5.5);   glVertex3f(-9.0, 0.0, -5.5);
  glEnd();

  // left side
  glBegin(GL_POLYGON);
    glVertex3f(-9.0, 0.0, -5.5);  glVertex3f(-9.0, 0.0, -8.5);
    glVertex3f(-9.0, 2.1, -10.5); glVertex3f(-9.0, 5.0, -10.5);
    glVertex3f(-9.0, 7.1, -8.5);  glVertex3f(-9.0, 7.1, -5.5);
    glVertex3f(-9.0, 5.0, -3.5);  glVertex3f(-9.0, 2.1, -3.5);
  glEnd();

  // back right wheel
  glBegin(GL_QUADS);
    glVertex3f(6.0, 0.0, -5.5);   glVertex3f(9.0, 0.0, -5.5);
    glVertex3f(9.0, 0.0, -8.5);   glVertex3f(6.0, 0.0, -8.5);

    glVertex3f(6.0, 0.0, -8.5);   glVertex3f(9.0, 0.0, -8.5);
    glVertex3f(9.0, 2.1, -10.5);  glVertex3f(6.0, 2.1, -10.5);

    glVertex3f(6.0, 2.1, -10.5);  glVertex3f(9.0, 2.1, -10.5);
    glVertex3f(9.0, 5.0, -10.5);  glVertex3f(6.0, 5.0, -10.5);

    glVertex3f(6.0, 5.0, -10.5);  glVertex3f(9.0, 5.0, -10.5);
    glVertex3f(9.0, 7.1, -8.5);   glVertex3f(6.0, 7.1, -8.5);

    glVertex3f(6.0, 7.1, -8.5);   glVertex3f(9.0, 7.1, -8.5);
    glVertex3f(9.0, 7.1, -5.5);   glVertex3f(6.0, 7.1, -5.5);

    glVertex3f(6.0, 7.1, -5.5);   glVertex3f(9.0, 7.1, -5.5);
    glVertex3f(9.0, 5.0, -3.5);   glVertex3f(6.0, 5.0, -3.5);

    glVertex3f(6.0, 5.0, -3.5);   glVertex3f(9.0, 5.0, -3.5);
    glVertex3f(9.0, 2.1, -3.5);   glVertex3f(6.0, 2.1, -3.5);

    glVertex3f(6.0, 2.1, -3.5);   glVertex3f(9.0, 2.1, -3.5);
    glVertex3f(9.0, 0.0, -5.5);   glVertex3f(6.0, 0.0, -5.5);
  glEnd();

  // right side
  glBegin(GL_POLYGON);
    glVertex3f(9.0, 0.0, -5.5);  glVertex3f(9.0, 0.0, -8.5);
    glVertex3f(9.0, 2.1, -10.5); glVertex3f(9.0, 5.0, -10.5);
    glVertex3f(9.0, 7.1, -8.5);  glVertex3f(9.0, 7.1, -5.5);
    glVertex3f(9.0, 5.0, -3.5);  glVertex3f(9.0, 2.1, -3.5);
  glEnd();

  // side
  glColor3fv(color);
  glBegin(GL_TRIANGLES);
    // left
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-8.5, 5.4, 0.0);   glVertex3f(-8.5, 5.4, -2.5);    glVertex3f(-8.5, 11.6, 0.0);
    glVertex3f(-8.5, 5.4, -2.5);  glVertex3f(-8.5, 8.1, -5.1);    glVertex3f(-8.5, 11.6, 0.0);
    glVertex3f(-8.5, 8.1, -5.1);  glVertex3f(-8.5, 16.2, -10.0);  glVertex3f(-8.5, 11.6, 0.0);
    glVertex3f(-8.5, 8.1, -5.1);  glVertex3f(-8.5, 8.1, -8.9);    glVertex3f(-8.5, 16.2, -10.0);
    glVertex3f(-8.5, 8.1, -8.9);  glVertex3f(-8.5, 16.2, -20.0);  glVertex3f(-8.5, 16.2, -10.0);
    glVertex3f(-8.5, 8.1, -8.9);  glVertex3f(-8.5, 11.8, -26.7);  glVertex3f(-8.5, 16.2, -20.0);
    glVertex3f(-8.5, 8.1, -8.9);  glVertex3f(-8.5, 5.4, -11.5);   glVertex3f(-8.5, 11.8, -26.7);
    glVertex3f(-8.5, 5.4, -11.5); glVertex3f(-8.5, 8.1, -31.5);   glVertex3f(-8.5, 11.8, -26.7);
    glVertex3f(-8.5, 5.4, -11.5); glVertex3f(-8.5, 5.4, -29.3);   glVertex3f(-8.5, 8.1, -31.5);
    glVertex3f(-8.5, 5.4, -11.5); glVertex3f(-8.5, 2.9, -11.5);   glVertex3f(-8.5, 5.4, -29.3);
    glVertex3f(-8.5, 2.9, -11.5); glVertex3f(-8.5, 2.9, -29.3);   glVertex3f(-8.5, 5.4, -29.3);
    glVertex3f(-8.5, 8.1, -31.5); glVertex3f(-8.5, 8.1, -34.5);   glVertex3f(-8.5, 11.8, -26.7);
    glVertex3f(-8.5, 8.1, -34.5); glVertex3f(-8.5, 9.6, -40.0);   glVertex3f(-8.5, 11.8, -26.7);
    glVertex3f(-8.5, 8.1, -34.5); glVertex3f(-8.5, 5.4, -36.7);   glVertex3f(-8.5, 9.6, -40.0);
    glVertex3f(-8.5, 5.4, -36.7); glVertex3f(-8.5, 5.4, -40.0);   glVertex3f(-8.5, 9.6, -40.0);

    // right
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(8.5, 5.4, 0.0);   glVertex3f(8.5, 5.4, -2.5);    glVertex3f(8.5, 11.6, 0.0);
    glVertex3f(8.5, 5.4, -2.5);  glVertex3f(8.5, 8.1, -5.1);    glVertex3f(8.5, 11.6, 0.0);
    glVertex3f(8.5, 8.1, -5.1);  glVertex3f(8.5, 16.2, -10.0);  glVertex3f(8.5, 11.6, 0.0);
    glVertex3f(8.5, 8.1, -5.1);  glVertex3f(8.5, 8.1, -8.9);    glVertex3f(8.5, 16.2, -10.0);
    glVertex3f(8.5, 8.1, -8.9);  glVertex3f(8.5, 16.2, -20.0);  glVertex3f(8.5, 16.2, -10.0);
    glVertex3f(8.5, 8.1, -8.9);  glVertex3f(8.5, 11.8, -26.7);  glVertex3f(8.5, 16.2, -20.0);
    glVertex3f(8.5, 8.1, -8.9);  glVertex3f(8.5, 5.4, -11.5);   glVertex3f(8.5, 11.8, -26.7);
    glVertex3f(8.5, 5.4, -11.5); glVertex3f(8.5, 8.1, -31.5);   glVertex3f(8.5, 11.8, -26.7);
    glVertex3f(8.5, 5.4, -11.5); glVertex3f(8.5, 5.4, -29.3);   glVertex3f(8.5, 8.1, -31.5);
    glVertex3f(8.5, 5.4, -11.5); glVertex3f(8.5, 2.9, -11.5);   glVertex3f(8.5, 5.4, -29.3);
    glVertex3f(8.5, 2.9, -11.5); glVertex3f(8.5, 2.9, -29.3);   glVertex3f(8.5, 5.4, -29.3);
    glVertex3f(8.5, 8.1, -31.5); glVertex3f(8.5, 8.1, -34.5);   glVertex3f(8.5, 11.8, -26.7);
    glVertex3f(8.5, 8.1, -34.5); glVertex3f(8.5, 9.6, -40.0);   glVertex3f(8.5, 11.8, -26.7);
    glVertex3f(8.5, 8.1, -34.5); glVertex3f(8.5, 5.4, -36.7);   glVertex3f(8.5, 9.6, -40.0);
    glVertex3f(8.5, 5.4, -36.7); glVertex3f(8.5, 5.4, -40.0);   glVertex3f(8.5, 9.6, -40.0);
  glEnd();

  // body
  glBegin(GL_QUADS);
    // rear bumper
    glColor3f(0.0, 0.0, 0.0);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-8.5, 5.4, 0.0); glVertex3f(8.5, 5.4, 0.0);
    glVertex3f(8.5, 2.9, 0.0);  glVertex3f(-8.5, 2.9, 0.0);

    glVertex3f(-8.5, 2.9, 0.0); glVertex3f(8.5, 2.9, 0.0);
    glVertex3f(8.5, 2.9, -2.5); glVertex3f(-8.5, 2.9, -2.5);

    glVertex3f(-8.5, 2.9, -2.5);  glVertex3f(8.5, 2.9, -2.5);
    glVertex3f(8.5, 5.4, -2.5);   glVertex3f(-8.5, 5.4, -2.5);

    // left side
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-8.5, 2.9, 0.0);  glVertex3f(-8.5, 2.9, -2.5);
    glVertex3f(-8.5, 5.4, -2.5); glVertex3f(-8.5, 5.4, 0.0);

    // right side
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(8.5, 2.9, 0.0);  glVertex3f(8.5, 2.9, -2.5);
    glVertex3f(8.5, 5.4, -2.5); glVertex3f(8.5, 5.4, 0.0);

    // rear side
    glColor3fv(color);
    glVertex3f(-8.5, 5.4, -2.5);  glVertex3f(8.5, 5.4, -2.5);
    glVertex3f(8.5, 8.1, -5.1);   glVertex3f(-8.5, 8.1, -5.1);

    glVertex3f(-8.5, 8.1, -5.1);  glVertex3f(8.5, 8.1, -5.1);
    glVertex3f(8.5, 8.1, -8.9);   glVertex3f(-8.5, 8.1, -8.9);

    glVertex3f(-8.5, 8.1, -8.9);  glVertex3f(8.5, 8.1, -8.9);
    glVertex3f(8.5, 8.1, -11.5);  glVertex3f(-8.5, 8.1, -11.5);

    glVertex3f(-8.5, 8.1, -11.5); glVertex3f(8.5, 8.1, -11.5);
    glVertex3f(8.5, 2.9, -11.5);  glVertex3f(-8.5, 2.9, -11.5);

    glVertex3f(-8.5, 2.9, -11.5); glVertex3f(8.5, 2.9, -11.5);
    glVertex3f(8.5, 2.9, -29.3);  glVertex3f(-8.5, 2.9, -29.3);

    // frontal side
    glVertex3f(-8.5, 2.9, -29.3); glVertex3f(8.5, 2.9, -29.3);
    glVertex3f(8.5, 5.4, -29.3);  glVertex3f(-8.5, 5.4, -29.3);

    glVertex3f(-8.5, 5.4, -29.3); glVertex3f(8.5, 5.4, -29.3);
    glVertex3f(8.5, 8.1, -31.5);  glVertex3f(-8.5, 8.1, -31.5);

    glVertex3f(-8.5, 8.1, -31.5); glVertex3f(8.5, 8.1, -31.5);
    glVertex3f(8.5, 8.1, -34.5);  glVertex3f(-8.5, 8.1, -34.5);

    glVertex3f(-8.5, 8.1, -34.5); glVertex3f(8.5, 8.1, -34.5);
    glVertex3f(8.5, 5.4, -36.7);  glVertex3f(-8.5, 5.4, -36.7);

    // front bumper
    glColor3f(0.0, 0.0, 0.0);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-8.5, 4.5, -36.7); glVertex3f(8.5, 4.5, -36.7);
    glVertex3f(8.5, 2.9, -36.7);  glVertex3f(-8.5, 2.9, -36.7);

    glVertex3f(-8.5, 2.9, -36.7); glVertex3f(8.5, 2.9, -36.7);
    glVertex3f(8.5, 2.9, -40.0);  glVertex3f(-8.5, 2.9, -40.0);

    glVertex3f(-8.5, 2.9, -40.0); glVertex3f(8.5, 2.9, -40.0);
    glVertex3f(8.5, 4.5, -40.0);  glVertex3f(-8.5, 4.5, -40.0);

    // left side
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-8.5, 2.9, -36.7); glVertex3f(-8.5, 2.9, -40.0);
    glVertex3f(-8.5, 4.5, -40.0); glVertex3f(-8.5, 4.5, -36.7);

    // right side
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(8.5, 2.9, -36.7); glVertex3f(8.5, 2.9, -40.0);
    glVertex3f(8.5, 4.5, -40.0); glVertex3f(8.5, 4.5, -36.7);

    // frontal
    glColor3fv(color);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-8.5, 4.5, -40.0);  glVertex3f(8.5, 4.5, -40.0);
    glVertex3f(8.5, 9.6, -40.0);   glVertex3f(-8.5, 9.6, -40.0);

    // hood
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-8.5, 9.6, -40.0);  glVertex3f(8.5, 9.6, -40.0);
    glVertex3f(8.5, 11.8, -26.7);  glVertex3f(-8.5, 11.8, -26.7);

    // windshield
    glVertex3f(-8.5, 11.8, -26.7); glVertex3f(8.5, 11.8, -26.7);
    glVertex3f(8.5, 16.2, -20.0);  glVertex3f(-8.5, 16.2, -20.0);

    // ceiling
    glVertex3f(-8.5, 16.2, -20.0); glVertex3f(8.5, 16.2, -20.0);
    glVertex3f(8.5, 16.2, -10.0);  glVertex3f(-8.5, 16.2, -10.0);

    // back
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-8.5, 16.2, -10.0);  glVertex3f(8.5, 16.2, -10.0);
    glVertex3f(8.5, 11.6, 0.0);     glVertex3f(-8.5, 11.6, 0.0);

    glVertex3f(-8.5, 11.6, 0.0);  glVertex3f(8.5, 11.6, 0.0);
    glVertex3f(8.5, 5.4, 0.0);    glVertex3f(-8.5, 5.4, 0.0);
  glEnd();

  // glasses
  glColor3f(0, 0.1, 0.4);

  glBegin(GL_QUADS);
    // back
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-7.5, 12.45, -1.8); glVertex3f(7.5, 12.45, -1.8);
    glVertex3f(7.5, 15.8, -9.1);   glVertex3f(-7.5, 15.8, -9.1);
  glEnd();

  glBegin(GL_QUADS);
    // frontal
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-7.5, 12.7, -25.4);  glVertex3f(7.5, 12.7, -25.4);
    glVertex3f(7.5, 15.7, -20.8);   glVertex3f(-7.5, 15.7, -20.8);
  glEnd();

  glBegin(GL_POLYGON);
    // left glasses
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-8.51, 11.2, -1.6);  glVertex3f(-8.51, 11.2, -25.7);
    glVertex3f(-8.51, 15.2, -19.7); glVertex3f(-8.51, 15.2, -10.2);
  glEnd();
  glBegin(GL_POLYGON);
    // frontal glasses
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(8.51, 11.2, -1.6);  glVertex3f(8.51, 11.2, -25.7);
    glVertex3f(8.51, 15.2, -19.7); glVertex3f(8.51, 15.2, -10.2);
  glEnd();

  // doors
  glColor3f(0.0, 0.0, 0.0);

  // left
  glNormal3f(-1.0, 0.0, 0.0);
  glBegin(GL_LINES);
    glVertex3f(-8.51, 4.4, -13.0); glVertex3f(-8.51, 15.2, -13.0);
    glVertex3f(-8.51, 4.4, -13.0); glVertex3f(-8.51, 4.4, -25.7);
    glVertex3f(-8.51, 4.4, -25.7); glVertex3f(-8.51, 11.2, -25.7);
  glEnd();

  // right
  glNormal3f(1.0, 0.0, 0.0);
  glBegin(GL_LINES);
    glVertex3f(8.51, 4.4, -13.0); glVertex3f(8.51, 15.2, -13.0);
    glVertex3f(8.51, 4.4, -13.0); glVertex3f(8.51, 4.4, -25.7);
    glVertex3f(8.51, 4.4, -25.7); glVertex3f(8.51, 11.2, -25.7);
  glEnd();

  // lantern
  glColor3f(0.8, 0.0, 0.0);

  // back left
  glNormal3f(0.0, 0.0, 1.0);
  glBegin(GL_QUADS);
    glVertex3f(-6.5, 9.1, 0.1);  glVertex3f(-4.5, 9.1, 0.1);
    glVertex3f(-4.5, 10.6, 0.1); glVertex3f(-6.5, 10.6, 0.1);
  glEnd();

  // back right
  glNormal3f(0.0, 0.0, 1.0);
  glBegin(GL_QUADS);
    glVertex3f(6.5, 9.1, 0.1);  glVertex3f(4.5, 9.1, 0.1);
    glVertex3f(4.5, 10.6, 0.1); glVertex3f(6.5, 10.6, 0.1);
  glEnd();

  glColor3f(0.9, 0.9, 0.0);

  // back lights
  glNormal3f(0.0, 0.0, 1.0);
  glBegin(GL_QUADS);
    glVertex3f(-7.5, 9.1, 0.1);  glVertex3f(-6.5, 9.1, 0.1);
    glVertex3f(-6.5, 10.6, 0.1); glVertex3f(-7.5, 10.6, 0.1);
  glEnd();

  glNormal3f(0.0, 0.0, 1.0);
  glBegin(GL_QUADS);
    glVertex3f(6.5, 9.1, 0.1);  glVertex3f(7.5, 9.1, 0.1);
    glVertex3f(7.5, 10.6, 0.1); glVertex3f(6.5, 10.6, 0.1);
  glEnd();

  // exhaust
  glColor3f(0.5, 0.5, 0.5);
  glBegin(GL_LINES);
    glVertex3f(5.3, 3.9, 0.1); glVertex3f(5.7, 3.9, 0.1);
    glVertex3f(5.7, 3.9, 0.1); glVertex3f(6.0, 4.2, 0.1);
    glVertex3f(6.0, 4.2, 0.1); glVertex3f(6.0, 4.6, 0.1);
    glVertex3f(6.0, 4.6, 0.1); glVertex3f(5.7, 4.9, 0.1);
    glVertex3f(5.7, 4.9, 0.1); glVertex3f(5.3, 4.9, 0.1);
    glVertex3f(5.3, 4.9, 0.1); glVertex3f(5.1, 4.6, 0.1);
    glVertex3f(5.1, 4.6, 0.1); glVertex3f(5.1, 4.2, 0.1);
    glVertex3f(5.1, 4.2, 0.1); glVertex3f(5.3, 3.9, 0.1);
  glEnd();

  glBegin(GL_LINES);
    glVertex3f(6.3, 3.9, 0.1); glVertex3f(6.7, 3.9, 0.1);
    glVertex3f(6.7, 3.9, 0.1); glVertex3f(7.0, 4.2, 0.1);
    glVertex3f(7.0, 4.2, 0.1); glVertex3f(7.0, 4.6, 0.1);
    glVertex3f(7.0, 4.6, 0.1); glVertex3f(6.7, 4.9, 0.1);
    glVertex3f(6.7, 4.9, 0.1); glVertex3f(6.3, 4.9, 0.1);
    glVertex3f(6.3, 4.9, 0.1); glVertex3f(6.1, 4.6, 0.1);
    glVertex3f(6.1, 4.6, 0.1); glVertex3f(6.1, 4.2, 0.1);
    glVertex3f(6.1, 4.2, 0.1); glVertex3f(6.3, 3.9, 0.1);
  glEnd();

  glPopMatrix();
  glNormal3f(0.0, 1.0, 0.0);
}
