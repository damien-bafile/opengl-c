#include "GL/glut.h"

typedef GLfloat point3[3];

void init();
void mydisplay();
void drawSquares();

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500); // define window
  glutInitWindowPosition(0, 0); // properties
  glutCreateWindow("simple");
  glutDisplayFunc(mydisplay); // display callback
  init();                     // set OpenGL state
  glutMainLoop();             // enter event loop
  return 0;
}

void init() {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor3f(1.0, 1.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  GLdouble left = -1;   // left clip plane
  GLdouble right = 1;   // right clip plane
  GLdouble bottom = -1; // bottom clip plane
  GLdouble top = 1;     // top clip plane
  GLdouble near = 0.1;  // near clip plane
  GLdouble far = 100;   // far clip plane

  glOrtho(left, right, bottom, top, near, far);
}

void mydisplay() {
  glClear(GL_COLOR_BUFFER_BIT);
  drawSquares();
  glFlush();
}

void drawSquares() {
  point3 vertices[8] = {{-.5, -.5, -.5}, {.5, -.5, -.5},   {.5, .5, -.5},
                        {-.5, .5, -.5},  {-.5, -.5, -1.5}, {.5, -.5, -1.5},
                        {.5, .5, -1.5},  {-.5, .5, -1.5}};
  glBegin(GL_LINE_LOOP);
  glVertex3fv(vertices[0]);
  glVertex3fv(vertices[1]);
  glVertex3fv(vertices[2]);
  glVertex3fv(vertices[3]);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3fv(vertices[5]);
  glVertex3fv(vertices[4]);
  glVertex3fv(vertices[7]);
  glVertex3fv(vertices[6]);
  glEnd();
}