#include <GL/glut.h>
#include <math.h>

#define DEGREES_TO_RADIANS 3.14159/180.0

static float spin = 0.0;
float a, b;

void square() {
	glBegin(GL_QUADS);
	glVertex2f(a, b);
	glVertex2f(-b, a);
	glVertex2f(-a, -b);
	glVertex2f(b, -a);
	glEnd();
}

void displayd() {
	glClear(GL_COLOR_BUFFER_BIT);
	square();
	glutSwapBuffers();
}

void spinDisplay(void) {
	spin = spin + 0.1;
	if (spin > 360) spin = spin - 360;
	a = 0.5 * cos(DEGREES_TO_RADIANS * spin);
	b = 0.5 * sin(DEGREES_TO_RADIANS * spin);
	glutPostRedisplay();
}

void myinit() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glShadeModel(GL_FLAT);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(500, 0);
	glutCreateWindow("double buffered");
	myinit();
	glutDisplayFunc(displayd);
	glutIdleFunc(spinDisplay);
	glutMainLoop();
}
