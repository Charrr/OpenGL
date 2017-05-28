#include <math.h>
#include <GL/glut.h>

/* initial triangle */
GLfloat v[3][2] = {{-1.0, -0.58},
                   {1.0,  -0.58},
                   {0.0,  1.15}};

int n = 4; /* number of recursive steps */

GLfloat twist = 1.5;

void triangle(GLfloat *a, GLfloat *b, GLfloat *c) {
/* display one triangle  */

	GLfloat vn[2];
	double d;

	glBegin(GL_POLYGON);
	d = sqrt(a[0] * a[0] + a[1] * a[1]);
	vn[0] = a[0] * cos(d) + a[1] * sin(d);  // <----- Rotation matrix
	vn[1] = -a[0] * sin(d) + a[1] * cos(d);
	glVertex2fv(vn);
	d = sqrt(b[0] * b[0] + b[1] * b[1]);
	vn[0] = b[0] * cos(d) + b[1] * sin(d);
	vn[1] = -b[0] * sin(d) + b[1] * cos(d);
	glVertex2fv(vn);
	d = sqrt(c[0] * c[0] + c[1] * c[1]);
	vn[0] = c[0] * cos(d) + c[1] * sin(d);
	vn[1] = -c[0] * sin(d) + c[1] * cos(d);
	glVertex2fv(vn);
	glEnd();
}

void divide_triangle(GLfloat *a, GLfloat *b, GLfloat *c, int m) {
/* triangle subdivision using vertex numbers */
	GLfloat v[3][2];
	int j;

	if (m > 0) {
		for (j = 0; j < 2; j++) v[0][j] = (a[j] + b[j]) / 2;
		for (j = 0; j < 2; j++) v[1][j] = (a[j] + c[j]) / 2;
		for (j = 0; j < 2; j++) v[2][j] = (b[j] + c[j]) / 2;
		divide_triangle(a, v[0], v[1], m - 1);
		divide_triangle(v[0], b, v[2], m - 1);
		divide_triangle(v[1], v[2], c, m - 1);
		divide_triangle(v[0], v[1], v[2], m - 1);
	} else(triangle(a, b, c));
	/* draw triangle at end of recursion */
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	divide_triangle(v[0], v[1], v[2], n);
	glFlush();
}

void myinit() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT, GL_LINE);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("tessalation");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}
