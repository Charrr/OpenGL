#include <GL/glut.h>

void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(3.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 280.0);
}

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	float tween;
	int offset = 60;
	GLfloat A[9][2] = {{20.0, 20.0},
	                   {20.0, 60.0},
	                   {45.0, 80.0},
	                   {70.0, 60.0},
	                   {70.0, 20.0},
	                   {50.0, 20.0},
	                   {50.0, 35.0},
	                   {40.0, 35.0},
	                   {40.0, 20.0}};
	GLfloat B[9][2] = {{20.0, 60.0},
	                   {20.0, 80.0},
	                   {45.0, 80.0},
	                   {70.0, 80.0},
	                   {70.0, 60.0},
	                   {50.0, 60.0},
	                   {50.0, 20.0},
	                   {40.0, 20.0},
	                   {40.0, 60.0}};

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 9; ++i) {
		glVertex2f(A[i][0], A[i][1]);
	}
	glEnd();
	glFlush();


	for (int j = 0; j < 9; j++) {
		tween = j * 0.125;
		glBegin(GL_LINE_LOOP); // 9 lines to be completed
		for (int i = 0; i < 9; ++i) {
			glVertex2f(j * offset + (1 - tween) * A[i][0] + tween * B[i][0], (1 - tween) * A[i][1] + tween * B[i][1]);
		}
		glEnd();
	}
	glFlush();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 280);
	glutCreateWindow("Tween");
	glutDisplayFunc(mydisplay);
	myInit();
	glutMainLoop();
}
