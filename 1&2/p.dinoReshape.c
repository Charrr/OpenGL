#include <stdio.h>
#include <GL/glut.h>

void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(3.0);
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
	drawPolyLineFile("../1&2/dino.dat");
}

void myreshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		gluOrtho2D(0.0, 640.0, 0.0, 480.0 * (GLfloat) h / (GLfloat) w);
	else
		gluOrtho2D(0.0, 640.0 * (GLfloat) w / (GLfloat) h, 0.0, 480.0);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("dinoReshape");
	glutDisplayFunc(mydisplay);
	glutReshapeFunc(myreshape);
	myInit();
	glutMainLoop();
}
