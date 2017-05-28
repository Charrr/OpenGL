#include <GL/glut.h>
#include <math.h>

#define SIZE 15
#define LEFT -SIZE
#define RIGHT SIZE
#define BOTTOM -SIZE
#define TOP SIZE
#define NEAR -SIZE
#define FAR SIZE

#define ANTE_RADIUS 0.1
#define ANTE_LENGTH 4.0
#define ANTE_ANGLE_X 20.0
#define ANTE_ANGLE_Y 50.0
#define BODY_RADIUS 1.0
#define BODY_SCALE 5.0
#define TAIL_RADIUS 1.2
#define TAIL_SCALE 3.0
#define WING_LENGTH 6.0
#define WING_WIDTH 4.0
#define WING_GAPANGLE 45
#define BWIN_ANGLE 20.0
#define SWIN_ANGLE -30.0
#define THRX_RADIUS 1.0
#define LEGS_GAP 1.5
#define COXA_RADIUS 0.2
#define FEMR_RADIUS 0.1
#define TIBA_RADIUS 0.05

static GLUquadricObj *p;

static GLfloat thetaOfWing;

void body() {
	glColor3f(0.1f, 0.1f, 0.0f);
	glScalef(BODY_SCALE, 0.8, 0.8);
	gluSphere(p, BODY_RADIUS, 50, 50);
}

void tail() {
	glColor3f(1.0f, 0.9f, 0.0f);
	glScalef(TAIL_SCALE, 0.6, 0.6);
	gluSphere(p, TAIL_RADIUS, 30, 30);
}

void antenna() {
	glColor3f(0.9f, 0.3f, 0.6f);
	gluCylinder(p, ANTE_RADIUS, ANTE_RADIUS * 0.5, ANTE_LENGTH + BODY_RADIUS, 15, 15);
	glTranslatef(0.0, 0.0, ANTE_LENGTH + BODY_RADIUS);
	gluSphere(p, ANTE_RADIUS * 1.2, 50, 50);
}

void wing() {
	glColor3f(0.2f, 0.8f, 1.0f);
	glScalef(1.0, WING_LENGTH / WING_WIDTH, 1.0);
	gluDisk(p, 0.0, WING_WIDTH, 30, 30);
}

void fLeg(int i) {
	glColor3f(0.7, 0.2, 0.9);
	gluCylinder(p, COXA_RADIUS, COXA_RADIUS, 1.2 * THRX_RADIUS, 50, 50);
	glTranslatef(0.0, 0.0, 1.2 * THRX_RADIUS);
	glRotatef(-20, 0.0, 1.0 * i, 0.0);
	gluCylinder(p, FEMR_RADIUS, FEMR_RADIUS, 1.5 * THRX_RADIUS, 50, 50);
	glTranslatef(0.0, 0.0, 1.5 * THRX_RADIUS);
	glRotatef(-20, 0.0, 1.0 * i, 0.0);
	gluCylinder(p, TIBA_RADIUS, TIBA_RADIUS, THRX_RADIUS, 50, 50);
	glTranslatef(0.0, 0.0, THRX_RADIUS);
	glRotatef(-10, 0.0, 1.0 * i, 0.0);
	gluCylinder(p, TIBA_RADIUS, 0, 0.8 * THRX_RADIUS, 50, 50);
}

void mLeg(int i) {
	glColor3f(0.7, 0.2, 0.9);
	gluCylinder(p, COXA_RADIUS, COXA_RADIUS, 1.2 * THRX_RADIUS, 50, 50);
	glTranslatef(0.0, 0.0, 1.2 * THRX_RADIUS);
	glRotatef(-5, 0.0, 1.0 * i, 0.0);
	gluCylinder(p, FEMR_RADIUS, FEMR_RADIUS, 1.6 * THRX_RADIUS, 50, 50);
	glTranslatef(0.0, 0.0, 1.6 * THRX_RADIUS);
	glRotatef(-40, 0.0, 1.0 * i, 0.0);
	gluCylinder(p, TIBA_RADIUS, TIBA_RADIUS, 1.1 * THRX_RADIUS, 50, 50);
	glTranslatef(0.0, 0.0, 1.1 * THRX_RADIUS);
	glRotatef(-20, 0.0, 1.0 * i, 0.0);
	gluCylinder(p, TIBA_RADIUS, 0, 0.8 * THRX_RADIUS, 50, 50);
}

void rLeg(int i) {
	glColor3f(0.7, 0.2, 0.9);
	gluCylinder(p, COXA_RADIUS, COXA_RADIUS, 1.2 * THRX_RADIUS, 50, 50);
	glTranslatef(0.0, 0.0, 1.2 * THRX_RADIUS);
	glRotatef(10, 0.0, 1.0 * i, 1.0 * i);
	gluCylinder(p, FEMR_RADIUS, FEMR_RADIUS, 1.7 * THRX_RADIUS, 50, 50);
	glTranslatef(0.0, 0.0, 1.7 * THRX_RADIUS);
	glRotatef(-50, 0.0, 1.0 * i, 0.0);
	gluCylinder(p, TIBA_RADIUS, TIBA_RADIUS, 1.2 * THRX_RADIUS, 50, 50);
	glTranslatef(0.0, 0.0, 1.2 * THRX_RADIUS);
	glRotatef(-30, 0.0, 1.0 * i, 0.0);
	gluCylinder(p, TIBA_RADIUS, 0, 0.8 * THRX_RADIUS, 50, 50);
}

void butterfly() {
	//Body.
	glPushMatrix();
	body();
	glPopMatrix();

	//Tail.
	glPushMatrix();
	glTranslated(4.0, 0.0, 0.0);
	tail();
	glPopMatrix();

	//Left antenna.
	glPushMatrix();
	glTranslatef(-BODY_RADIUS - BODY_RADIUS - 1.5, 0.0, 0.0);
	glRotatef(-ANTE_ANGLE_Y, 0.0, 1.0, 0.0);
	glRotatef(-ANTE_ANGLE_X, 1.0, 0.0, 0.0);
	antenna();
	glPopMatrix();

	//Right antenna.
	glPushMatrix();
	glTranslatef(-BODY_RADIUS - BODY_RADIUS - 1.5, 0.0, 0.0);
	glRotatef(ANTE_ANGLE_Y, 0.0, 1.0, 0.0);
	glRotatef(ANTE_ANGLE_X - 180, 1.0, 0.0, 0.0);
	antenna();
	glPopMatrix();

	//Big wings.
	for (int i = -1; i <= 1; i += 2) {
		glPushMatrix();
		glTranslatef(0.0, cos(WING_GAPANGLE) - 0.2, (sin(WING_GAPANGLE) - 0.2) * i);
		glRotatef(i * thetaOfWing, 1.0, 0.0, 0.0);
		glTranslatef(0.0, -cos(WING_GAPANGLE) + 0.2, -(sin(WING_GAPANGLE) - 0.2) * i);
		glRotatef(BWIN_ANGLE, 0.0, -i * sin(WING_GAPANGLE), cos(WING_GAPANGLE));
		glRotatef(i * WING_GAPANGLE, 1.0, 0.0, 0.0);
		glTranslatef(0.0, BODY_RADIUS + WING_LENGTH - 0.2, 0.0);
		wing();
		glPopMatrix();
	}

	//Small wings.
	for (int i = -1; i <= 1; i += 2) {
		glPushMatrix();
		glTranslatef(2.0, cos(WING_GAPANGLE) - 0.2, (sin(WING_GAPANGLE) - 0.2) * i);
		glRotatef(i * thetaOfWing, 1.0, 0.0, 0.0);
		glTranslatef(0.0, -cos(WING_GAPANGLE) + 0.2, -(sin(WING_GAPANGLE) - 0.2) * i);
		glRotatef(SWIN_ANGLE, 0.0, -i * sin(WING_GAPANGLE), cos(WING_GAPANGLE));
		glRotatef(i * WING_GAPANGLE, 1.0, 0.0, 0.0);
		glTranslatef(0.0, BODY_RADIUS + WING_LENGTH * 0.7 + 0.2, 0.0);
		glScalef(0.85, 0.85, 0.85);
		wing();
		glPopMatrix();
	}

	//Front legs.
	for (int i = -1; i <= 1; i += 2) {
		glPushMatrix();
		glTranslatef(-LEGS_GAP, 0.0, 0.0);
		glRotatef(-90 + 60 * i, 0.0, 1.0, 0.0);
		glRotatef(50, 1.0, 0.0, 0.0);
		fLeg(i);
		glPopMatrix();
	}

	//Middle legs.
	for (int i = -1; i <= 1; i += 2) {
		glPushMatrix();
		glRotatef(-90 + 60 * i, 0.0, 1.0, 0.0);
		glRotatef(50, 1.0, 0.0, 0.0);
		mLeg(i);
		glPopMatrix();
	}

	//Rear legs.
	for (int i = -1; i <= 1; i += 2) {
		glPushMatrix();
		glTranslatef(LEGS_GAP, 0.0, 0.0);
		glRotatef(-90 + 60 * i, 0.0, 1.0, 0.0);
		glRotatef(50, 1.0, 0.0, 0.0);
		rLeg(i);
		glPopMatrix();
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-1, 1, 1, 0, 0, 0, 0, 1, 0);

	butterfly();

	glutSwapBuffers();
}

void init() {
	thetaOfWing = 0.0;

	glClearColor(1.0, 1.0, 1.0, 1.0);
	p = gluNewQuadric();
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width <= height)
		glOrtho(LEFT, RIGHT, BOTTOM * (GLfloat) height / (GLfloat) width,
		        TOP * (GLfloat) height / (GLfloat) width, NEAR, FAR);
	else
		glOrtho(LEFT * (GLfloat) width / (GLfloat) height, RIGHT * (GLfloat) width / (GLfloat) height,
		        BOTTOM, TOP, NEAR, FAR);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("butterfly");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glEnable(GL_DEPTH_TEST);
	init();
	glutMainLoop();
}
