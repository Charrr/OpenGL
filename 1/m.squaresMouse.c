#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

GLdouble W = 640.0;
GLdouble H = 480.0;
GLint size = 30;

void myInit(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, W, 0, H);
}

void mydisplay() {
}

void drawSquare(int x, int y) { //  <----- Mouse's coordinate, left top (0,0)
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	y = viewport[3] - y; /* invert y position */
	glColor3ub((GLubyte) (rand() % 256), (GLubyte) (rand() % 256), (GLubyte) (rand() % 256));
	glBegin(GL_POLYGON); //  <----- GLUT's coordinate, left bottom (0,0)
	glVertex2i(x + size, y + size);
	glVertex2i(x - size, y + size);
	glVertex2i(x - size, y - size);
	glVertex2i(x + size, y - size);
	glEnd();
	glFlush();
}

void mymouse(int btn, int state, int x, int y) {
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		drawSquare(x, y);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(W, H);
	glutCreateWindow("simple");
	glutDisplayFunc(mydisplay);
	glutMouseFunc(mymouse);
	myInit();
	glutMainLoop();
}
