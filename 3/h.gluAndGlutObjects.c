/* This program displays a number of GLUT objects.
 * Use the N and P keys to move to Next or Previous object.
 * Click the right mouse button to start or stop the spin of the object.
 * Click the left mouse button to change the viewpoint on the object (gluLookAt function parameters).
 **/

#include <GL/glut.h>

#define MAX 14
#define MIN 1

int next = MIN;
GLUquadricObj *obj;
float eyex, eyey, eyez;
float atx, aty, atz;
int count = 0;
GLint eye[3] = {1, 0, 0};
GLboolean pause = GL_TRUE;

void myInit(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	eyex = eyey = eyez = 1.0;
	atx = aty = atz = 0.0;
	glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5, 1.5, -1.5, 1.5, -10.0, 10.0);
}


void mykey(unsigned char key, int x, int y) {
	if (key == 'N' | key == 'n')
		next++;
	if (key == 'P' | key == 'p')
		next--;
	if (next > MAX) next = MIN;
	if (next < MIN) next = MAX;
	if (next <= 5) glColor3f(1.0, 1.0, 1.0);
	if (next > 5 && next <= 9) glColor3f(1.0, 1.0, 0.0);
	if (next > 9 && next <= 13) glColor3f(1.0, 0.0, 0.0);
	if (next == 14) glColor3f(0.0, 0.0, 1.0);
	glutPostRedisplay();
}

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, atx, aty, atz, 0.0, 1.0, 0.0);
	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_LINE);
	switch (next) {
		case 1:
			gluSphere(obj, 0.5, 20, 20);
			break;
		case 2:
			gluCylinder(obj, 0.5, 0.3, 1, 10, 10);
			break;
		case 3:
			gluDisk(obj, 0.2, 0.5, 10, 10);
			break;
		case 4:
			gluDisk(obj, 0.2, 0.5, 30, 30);
			break;
		case 5:
			gluPartialDisk(obj, 0.2, 0.5, 30, 30, 0, 45);
			break;
		case 6:
			glutWireSphere(0.5, 20, 20);
			break;
		case 7:
			glutSolidSphere(0.5, 20, 20);
			break;
		case 8:
			glutWireCone(0.5, 1, 10, 10);
			break;
		case 9:
			glutWireTorus(0.2, 0.5, 20, 20);
			break;
		case 10:
			glutWireCube(1);
			break;
		case 11:
			glutWireTetrahedron();
			break;
		case 12:
			glutWireOctahedron();
			break;
		case 13:
			glutWireIcosahedron();
			break;
		case 14:
			glutWireTeapot(0.5);
			break;
	}
	glutSwapBuffers();
}

void mymouse(GLint button, GLint state, GLint x, GLint y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (eye[0] == 1) {
			eye[0] = 0;
			eye[1] = 1;
			return;
		}
		if (eye[1] == 1) {
			eye[1] = 0;
			eye[2] = 1;
			return;
		}
		if (eye[2] == 1) {
			eye[2] = 0;
			eye[0] = 1;
			return;
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		pause = !pause;
	}
}

void idle() {
	if (pause) return;
	if (eye[0] == 1) {
		eyex += 0.001;
		if (eyex > 1.0) eyex = -1.0;
	}
	if (eye[1] == 1) {
		eyey += 0.001;
		if (eyey > 1.0) eyey = -1.0;
	}
	if (eye[2] == 1) {
		eyez += 0.001;
		if (eyez > 1.0) eyez = -1.0;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutCreateWindow("GluAndGlutObjects");
	glutKeyboardFunc(mykey);
	glutMouseFunc(mymouse);
	glutDisplayFunc(mydisplay);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	myInit();
	glutMainLoop();
}
