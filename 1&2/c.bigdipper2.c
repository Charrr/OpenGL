#include <GL/glut.h>

void myInit(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void mydisplay() {
	GLint vertices[7][2] = {{20,  10},
	                        {74,  74},
	                        {129, 83},
	                        {194, 101},
	                        {239, 67},
	                        {320, 128},
	                        {289, 190}
	};
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_STRIP);
	glVertex2iv(vertices[0]);
	glVertex2iv(vertices[1]);
	glVertex2iv(vertices[2]);
	glVertex2iv(vertices[3]);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2iv(vertices[3]);
	glVertex2iv(vertices[4]);
	glVertex2iv(vertices[5]);
	glVertex2iv(vertices[6]);
	glVertex2iv(vertices[3]);
	glEnd();

	glFlush();

}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("The Big Dipper");
	glutDisplayFunc(mydisplay);
	myInit();
	glutMainLoop();
}
