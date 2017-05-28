/* recursive subdivision of a tetrahedron to approximate a sphere */

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

/* initial tetrahedron */
GLfloat v[4][3] = {{0.0,       0.0,       1.0},
                   {0.0,       0.942809,  -0.33333},
                   {-0.816497, -0.471405, -0.333333},
                   {0.816497,  -0.471405, -0.333333}};

static GLfloat theta[] = {0.0, 0.0, 0.0};
static GLint axis = 1;

int n = 5;  /* number of subdivision steps */

void triangle(GLfloat *va, GLfloat *vb, GLfloat *vc) {
	glBegin(GL_LINE_LOOP);
	glVertex3fv(va);
	glVertex3fv(vb);
	glVertex3fv(vc);
	glEnd();
}

// vertex normalisation
void normalise(GLfloat *p) {
	double mod = sqrt(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
	p[0] /= mod;
	p[1] /= mod;
	p[2] /= mod;
}


void divide_triangle(GLfloat *a, GLfloat *b, GLfloat *c, int n) {
	GLfloat v1[3], v2[3], v3[3];
	int j;
	if (n > 0) {
		for (j = 0; j < 3; j++) v1[j] = a[j] + b[j];
		normalise(v1);
		for (j = 0; j < 3; j++) v2[j] = a[j] + c[j];
		normalise(v2);
		for (j = 0; j < 3; j++) v3[j] = c[j] + b[j];
		normalise(v3);
		divide_triangle(a, v2, v1, n - 1);
		divide_triangle(c, v3, v2, n - 1);
		divide_triangle(b, v1, v3, n - 1);
		divide_triangle(v1, v2, v3, n - 1);
	} else triangle(a, b, c);
}

void tetrahedron(int n) {
	divide_triangle(v[0], v[1], v[2], n);
	divide_triangle(v[3], v[2], v[1], n);
	divide_triangle(v[0], v[3], v[1], n);
	divide_triangle(v[0], v[2], v[3], n);
}

void spinBarn() {
	theta[axis] += 0.02;
	if (theta[axis] > 360.0) theta[axis] -= 360.0;
	glutPostRedisplay();
}

void specialKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT:
			axis = 0;
			break;
		case GLUT_KEY_UP:
			axis = 1;
			break;
		case GLUT_KEY_RIGHT:
			axis = 2;
			break;
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	tetrahedron(n);
	glFlush();
}

void myReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-1.0, 1.0, -1.0 * (GLfloat) h / (GLfloat) w, 1.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
	else
		glOrtho(-1.0 * (GLfloat) w / (GLfloat) h, 1.0 * (GLfloat) w / (GLfloat) h, -1.0, 1.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Approximated Sphere");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(spinBarn);
	glutSpecialFunc(specialKey);
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glutMainLoop();
}
