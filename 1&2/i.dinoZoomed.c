#include <stdio.h>
#include <GL/glut.h>

const int Width = 640;
const int Height = 480;

void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(3.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, Width / 5, 4 * Height / 5, Height);  //  <----  Only this different from dino.c
}

void drawPolyLineFile(char *filename) {
	FILE *fp;
	GLint numPoly, numLines, x, y;

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
	drawPolyLineFile("../1&2/dino.dat");
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Dino");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
}
