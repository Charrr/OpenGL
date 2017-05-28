#include <stdio.h>
#include <GL/glut.h>

GLboolean animated = GL_FALSE;

GLdouble W = 640.0;
GLdouble H = 480.0;
GLdouble zoom = 1.0;

void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(3.0);
}

void setWindow(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

void myIdle() {
	if (!animated) return;
	if (zoom > 0.2) zoom -= 0.0005;
	glutPostRedisplay();
}

void drawPolyLineFile(char *filename) {
	FILE *fp;
	int numPoly, numLines, x, y;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Error: can't open file for reading.\n");
		return;
	}

	glClear(GL_COLOR_BUFFER_BIT);

	fscanf(fp, "%d", &numPoly);
	for (int i = 0; i < numPoly; i++) {
		fscanf(fp, "%d", &numLines);
		glBegin(GL_LINE_STRIP);
		for (int j = 0; j < numLines; j++) {
			fscanf(fp, "%d %d", &x, &y);
			glVertex2i(x, y);
		}
		glEnd();
	}

	glFlush();
	fclose(fp);
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	setWindow(0, W * zoom, H * (1 - zoom), H);
	drawPolyLineFile("../1&2/dino.dat");
	glutSwapBuffers();
}

void myMouse(GLint button, GLint state, GLint x, GLint y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		animated = !animated;
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		exit(0);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(W, H);
	glutCreateWindow("Dino");
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myIdle);
	glutMouseFunc(myMouse);
	myInit();
	glutMainLoop();
}
