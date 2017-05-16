#include <stdio.h>
#include <GL/glut.h>

GLint menu_id = 0;
GLint submenu_id = 0;

void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(3.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
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

void mymenu(int id) {
	if (id == 1) {
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	}
}

void mysubmenu(int id) {
	if (id == 1) exit(0);
	if (id == 2) return;
}


int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("dinoSubMenu");
	glutDisplayFunc(mydisplay);
	myInit();
	submenu_id = glutCreateMenu(mysubmenu);
	glutAddMenuEntry("yes", 1);
	glutAddMenuEntry("no", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	menu_id = glutCreateMenu(mymenu);
	glutAddMenuEntry("clear screen", 1);
	glutAddSubMenu("exit", submenu_id);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}
