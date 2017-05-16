#include <GL/glut.h>
#include <stdlib.h>

GLint size = 30;
GLfloat moveX = 0.0;
GLfloat moveY = 0.0;
GLfloat xx = 0;
GLfloat yy = 0;

void myInit(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
}

void mydisplay() {
}

void drawSquare(int x, int y) {
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	y = viewport[3] - y; /* invert y position */
	xx = x;
	yy = y;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub((GLubyte) (rand() % 256), (GLubyte) (rand() % 256), (GLubyte) (rand() % 256));
	glBegin(GL_POLYGON);
	glVertex2f(xx + size, yy + size);
	glVertex2f(xx - size, yy + size);
	glVertex2f(xx - size, yy - size);
	glVertex2f(xx + size, yy - size);
	glEnd();
	glFlush();
}

void mymouse(int btn, int state, int x, int y) {
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		drawSquare(x, y);
}

void myspecialkey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT:
			moveX = -0.1;
			break;
		case GLUT_KEY_RIGHT:
			moveX = 0.1;
			break;
		case GLUT_KEY_DOWN:
			moveY = -0.1;
			break;
		case GLUT_KEY_UP:
			moveY = 0.1;
			break;
	}
}

void myspecialkeyup(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT)
		moveX = 0.0;
	if (key == GLUT_KEY_UP || key == GLUT_KEY_DOWN)
		moveY = 0.0;
}

void myidle() {
	if (moveX == 0 && moveY == 0) return;
	glClear(GL_COLOR_BUFFER_BIT);
	xx += moveX;
	yy += moveY;
	glBegin(GL_POLYGON);
	glVertex2f(xx + size, yy + size);
	glVertex2f(xx - size, yy + size);
	glVertex2f(xx - size, yy - size);
	glVertex2f(xx + size, yy - size);
	glEnd();
	glFlush();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutCreateWindow("squaresKeyMotionComplete");
	glutDisplayFunc(mydisplay);
	glutMouseFunc(mymouse);
	glutSpecialFunc(myspecialkey);
	glutSpecialUpFunc(myspecialkeyup);
	glutIdleFunc(myidle);
	myInit();
	glutMainLoop();
}
