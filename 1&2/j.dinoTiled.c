#include <stdio.h>
#include <GL/glut.h>

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

void mydisplay() {
	setWindow(0, 640.0, 0, 440.0);

	glClear(GL_COLOR_BUFFER_BIT);

	for (int k = 0; k < 10; k++) {
		for (int l = 0; l < 10; l++) {
			glViewport(k * 64, l * 44, 64, 44);
			drawPolyLineFile("../1&2/dino.dat");
		}
	}
	glFlush();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 440);
	glutCreateWindow("Dino");
	glutDisplayFunc(mydisplay);
	myInit();
	glutMainLoop();
}
