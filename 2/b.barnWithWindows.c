/* A rotating barn with 2 doors and a window */

#include <stdlib.h>
#include <GL/glut.h>

GLfloat X = 0.5;        /* A scaling factor */
static GLfloat theta[] = {0.0, 0.0, 0.0};
static GLint axis = 1;

GLfloat GlobalVertices[][3] = {{-1.0, -1.0, -1.5},
                               {1.0,  -1.0, -1.5},
                               {1.0,  1.0,  -1.5},
                               {0.0,  2.0,  -1.5},
                               {-1.0, 1.0,  -1.5},
                               {-1.0, -1.0, 1.5},
                               {1.0,  -1.0, 1.5},
                               {1.0,  1.0,  1.5},
                               {0.0,  2.0,  1.5},
                               {-1.0, 1.0,  1.5},
                               {-0.5, 1.0,  1.5},
                               {0.5,  1.0,  1.5},
                               {0.5,  0.2,  1.5},
                               {-0.5, 0.2,  1.5},
                               {-1.0, 0.2,  1.5},
                               {1.0,  0.2,  1.5},
                               {1.0,  0.2,  1.2},
                               {1.0,  0.2,  0.3},
                               {1.0,  -1.0, 0.3},
                               {1.0,  -1.0, 1.2},
                               {1.0,  0.2,  -0.3},
                               {1.0,  0.2,  -1.2},
                               {1.0,  -1.0, -1.2},
                               {1.0,  -1.0, -0.3},
                               {1.0,  0.2,  -1.5}};

GLfloat BarnVertices[][3] = {{-1.0, -1.0, -1.5}, //0
                             {1.0,  -1.0, -1.5},
                             {1.0,  1.0,  -1.5},
                             {0.0,  2.0,  -1.5},
                             {-1.0, 1.0,  -1.5},
                             {-1.0, -1.0, 1.5},  //5
                             {1.0,  -1.0, 1.5},
                             {1.0,  1.0,  1.5},
                             {0.0,  2.0,  1.5},
                             {-1.0, 1.0,  1.5},
                             {-0.5, 1.0,  1.5}, //10
                             {0.5,  1.0,  1.5},
                             {0.5,  0.2,  1.5},
                             {-0.5, 0.2,  1.5},
                             {-1.0, 0.2,  1.5},
                             {1.0,  0.2,  1.5}, //15
                             {1.0,  0.2,  1.2},
                             {1.0,  0.2,  0.3},
                             {1.0,  -1.0, 0.3},
                             {1.0,  -1.0, 1.2},
                             {1.0,  0.2,  -0.3}, //20
                             {1.0,  0.2,  -1.2},
                             {1.0,  -1.0, -1.2},
                             {1.0,  -1.0, -0.3},
                             {1.0,  0.2,  -1.5}}; //24


GLint BarnFaces[][6] = {{3,  4,  0,  1,  2, -1}, //0
                        {8,  7,  2,  3,  -1}, //1
                        {3,  8,  9,  4,  -1}, //2
                        {9,  5,  0,  4,  -1}, //3
                        {5,  6,  1,  0,  -1}, //4
                        {7,  8,  9,  -1}, //5
                        {9,  10, 13, 14, -1}, //6
                        {11, 12, 15, 7,  -1}, //7
                        {14, 15, 6,  5,  -1}, //8
                        {7,  2,  24, 15, -1}, //9
                        {15, 16, 19, 6,  -1}, //10
                        {17, 20, 23, 18, -1}, //11
                        {21, 24, 1,  22, -1}, //12
                        {10, 11, 12, 13, -1}, //13
                        {16, 17, 18, 19, -1}, //14
                        {20, 21, 22, 23, -1} //15
};

GLfloat colors[][3] = {{0.0, 0.0, 0.0},
                       {1.0, 0.0, 0.0},
                       {1.0, 1.0, 0.0},
                       {0.0, 1.0, 0.0},
                       {0.0, 0.0, 1.0},
                       {1.0, 0.0, 1.0}, //5
                       {0.5, 0.5, 0.5},
                       {0.0, 1.0, 1.0},
                       {1.0, 1.0, 1.0}}; //8


void a3dPolygon(GLfloat vertices[][3], GLint face[]) {
	/* draw a polygon via list of vertices */
	int id;
	glShadeModel(GL_FLAT);
	glBegin(GL_POLYGON);
	for (int i = 0; face[i] > -1; i++) {
		id = face[i];
		glVertex3fv(vertices[id]);
	}
	glEnd();
}

void barn() {
	/* map vertices to facets */
	glColor3fv(colors[0]);
	a3dPolygon(BarnVertices, BarnFaces[0]);
	glColor3fv(colors[1]);
	a3dPolygon(BarnVertices, BarnFaces[1]);
	glColor3fv(colors[2]);
	a3dPolygon(BarnVertices, BarnFaces[2]);
	glColor3fv(colors[4]);
	a3dPolygon(BarnVertices, BarnFaces[3]);
	glColor3fv(colors[6]);
	a3dPolygon(BarnVertices, BarnFaces[4]);
	glColor3fv(colors[3]);
	a3dPolygon(BarnVertices, BarnFaces[5]);
	a3dPolygon(BarnVertices, BarnFaces[6]);
	a3dPolygon(BarnVertices, BarnFaces[7]);
	a3dPolygon(BarnVertices, BarnFaces[8]);
	glColor3fv(colors[5]);
	a3dPolygon(BarnVertices, BarnFaces[9]);
	a3dPolygon(BarnVertices, BarnFaces[10]);
	a3dPolygon(BarnVertices, BarnFaces[11]);
	a3dPolygon(BarnVertices, BarnFaces[12]);
	glColor3fv(colors[8]);
	a3dPolygon(BarnVertices, BarnFaces[13]);
	a3dPolygon(BarnVertices, BarnFaces[14]);
	a3dPolygon(BarnVertices, BarnFaces[15]);
}


void myDisplay() {
	/* display callback, clear frame buffer and z buffer */

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	barn();
	glutSwapBuffers();
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

void init() {
	int i, j;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	for (i = 0; i < 25; i++) {
		for (j = 0; j < 3; j++) {
			BarnVertices[i][j] = GlobalVertices[i][j] * X;  // scaling
		}
	}
}

void myReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-1.5, 1.5, -1.5 * (GLfloat) h / (GLfloat) w, 1.5 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
	else
		glOrtho(-1.5 * (GLfloat) w / (GLfloat) h, 1.5 * (GLfloat) w / (GLfloat) h, -1.5, 1.5, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);

	/* need both double buffering and z buffer */

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("A Barn");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutIdleFunc(spinBarn);
	glutSpecialFunc(specialKey);
	glEnable(GL_DEPTH_TEST); /* Enable hidden-surface removal */
	init();
	glutMainLoop();
}
