#include <GL/glut.h>

void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 130.0, 0.0, 150.0);
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	int peak[2] = {70, 120};
	int width = 60;
	int height = 80;
	glBegin(GL_LINE_LOOP);   // house
	glVertex2i(peak[0], peak[1]);
	glVertex2i(peak[0] + width / 2, peak[1] - (3 * height / 8));
	glVertex2i(peak[0] + width / 2, peak[1] - height);
	glVertex2i(peak[0] - width / 2, peak[1] - height);
	glVertex2i(peak[0] - width / 2, peak[1] - (3 * height / 8));
	glEnd();
	glBegin(GL_LINE_STRIP);    // chimney
	glVertex2i(peak[0] - (2 * width / 6), peak[1] - (2 * height / 8));
	glVertex2i(peak[0] - (2 * width / 6), peak[1]);
	glVertex2i(peak[0] - (width / 6), peak[1]);
	glVertex2i(peak[0] - (width / 6), peak[1] - (height / 8));
	glEnd();
	glBegin(GL_LINE_STRIP);    // door
	glVertex2i(peak[0] - (2 * width / 6), peak[1] - (height));
	glVertex2i(peak[0] - (2 * width / 6), peak[1] - (5 * height / 8));
	glVertex2i(peak[0] - (5 * width / 60), peak[1] - (5 * height / 8));
	glVertex2i(peak[0] - (5 * width / 60), peak[1] - (height));
	glEnd();
	glBegin(GL_LINE_LOOP);            // window
	glVertex2i(peak[0] + (5 * width / 60), peak[1] - (55 * height / 80));
	glVertex2i(peak[0] + (5 * width / 60), peak[1] - (4 * height / 8));
	glVertex2i(peak[0] + (2 * width / 6), peak[1] - (4 * height / 8));
	glVertex2i(peak[0] + (2 * width / 6), peak[1] - (55 * height / 80));
	glEnd();
	glFlush();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(130, 150);
	glutCreateWindow("House");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
}
