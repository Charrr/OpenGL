#include <GL/glut.h>

void display() {
	glMatrixMode(GL_MODELVIEW); // position and aim the camera
	glLoadIdentity();
	gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT); // clear the screen

	glPushMatrix();
	glTranslated(0.5, 0.5, 0.5); // big cube at (0.5, 0.5, 0.5)
	glutWireCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.0, 1.0, 0.0);    // sphere at (1,1,0)
	glutWireSphere(0.25, 10, 8);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.0, 0.0, 1.0);    // cone at (1,0,1)
	glutWireCone(0.2, 0.5, 10, 8);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 0.0, 1.0);
	glutWireTeapot(0.2); // teapot at (1,1,1)
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 1.0, 0.0); // torus at (0,1,0)
	glRotated(90.0, 1, 0, 0);
	glutWireTorus(0.1, 0.3, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.0, 0.0, 0.0); // dodecahedron at (1,0,0)
	glScaled(0.15, 0.15, 0.15);
	glutWireDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 1.0, 1.0); // small cube at (0,1,1)
	glutWireCube(0.25);
	glPopMatrix();

	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION); // set the view volume shape
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 100.0);
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("wireframe");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	init();
	glutMainLoop();
}
