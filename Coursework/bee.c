//
//  THIS IS LAB.
//  Created by 陈子谦 on 25/04/2017.
//  Copyright © 2017 Charrr. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

//set boundary
#define WIN_LEFT -10
#define WIN_RIGHT 10
#define WIN_BOTTOM -10
#define WIN_TOP 10
#define WIN_NEAR -10
#define WIN_FAR 10

#define BODY_RADIUS 1.0
#define HEAD_RADIUS 1.2
#define ABDOMEN_RADIUS 1.5
#define ABDOMEN_SCALE 1.3
#define STING_RADIUS 0.4
#define STING_LENGTH 0.8
#define ATENNA_RADIUS 0.1
#define ATENNA_LENGTH 1.8
#define ATENNA_ANGLE 15.0   // with respect to y-axis
#define UPPERLEG_RADIUS 0.2
#define UPPERLEG_LENGTH 0.3
#define LOWERLEG_RADIUS 0.1
#define LOWERLEG_LENGTH 0.5
#define LEG_ANGLE 40.0      // with respect to y-axis
#define LEG_GAPANGLE 60.0
#define LEG_GAP 0.4
#define WING_WIDTH 1.0
#define WING_LENGTH 2.5
#define WING_GAPANGLE 45.0      // how distant for two wings of a pair (the angle with respect to y-axis)
#define FOREWING_ANGLE 20.0     // the angle at which the forewings tilt forwards
#define BACKWING_ANGLE -30.0     // the angle at which the backwings tilt backwards
#define FLIP 20.0            // the frequency of flipping wings

GLUquadricObj *p;

static GLfloat theta[] = {0, 0, 0};         // for rotation
static GLint axis = 1;                      // for rotation, the initial
static GLboolean rotate_state = GL_FALSE;   // for rotation
static GLfloat posX = 0, posY = 0, posZ = 0;      // for jumping
static GLboolean fly_state = GL_FALSE;      // for flying
static GLfloat theta_wing = 0.0;            // for flying
static GLint flip_direction = 1;            // for flying



/* >>>>>>>>>>   MODELLING   <<<<<<<<<< */
/* >>>>>>>>>>   MODELLING   <<<<<<<<<< */
/* >>>>>>>>>>   MODELLING   <<<<<<<<<< */

void body() {
	glColor3f(1.0, 0.9, 0.0); // yellow-ish
	glPushMatrix();
	gluSphere(p, BODY_RADIUS, 50, 50);
	glPopMatrix();
}

void head() {
	glColor3f(0.1, 0.1, 0.0); // dark dark brown
	glPushMatrix();
	gluSphere(p, HEAD_RADIUS, 50, 50);
	glPopMatrix();
}

void abdomen() {
	glColor3f(0.1, 0.1, 0.0); // dark dark brown
	glPushMatrix();
	glScalef(ABDOMEN_SCALE, 1.0, 1.0);
	gluSphere(p, ABDOMEN_RADIUS, 50, 50);
	glPopMatrix();
}

void sting() {
	glColor3f(0.9, 0.3, 0.6); // hot pink
	glPushMatrix();
	gluCylinder(p, STING_RADIUS, 0.0, HEAD_RADIUS + STING_LENGTH, 15, 15);
	glPopMatrix();
}

void atenna() {
	glPushMatrix();
	glColor3f(0.9, 0.3, 0.6); // hot pink
	gluCylinder(p, ATENNA_RADIUS, ATENNA_RADIUS * 0.5, ATENNA_LENGTH + HEAD_RADIUS, 15, 15);
	glColor3f(0.3, 0.8, 0.8); // weird cyan
	glTranslatef(0.0, 0.0, ATENNA_LENGTH + HEAD_RADIUS);
	gluSphere(p, ATENNA_RADIUS * 1.2, 50, 50);
	glPopMatrix();
}

void leg(GLfloat upper_leng, GLfloat lower_leng) {
	glPushMatrix();
	glColor3f(0.7, 0.2, 0.9); // purple-ish
	gluCylinder(p, UPPERLEG_RADIUS, LOWERLEG_RADIUS, HEAD_RADIUS + upper_leng, 15, 15);  // the upper leg
	glColor3f(0.9, 0.5, 1.0); // lighter purple
	glTranslatef(0.0, 0.0, HEAD_RADIUS + upper_leng);
	glRotatef(LEG_GAPANGLE, 1.0, 0.0, 0.0);
	gluCylinder(p, LOWERLEG_RADIUS, 0.0, lower_leng, 15, 15);
	glPopMatrix();
}

void wing() {
	glColor4f(0.2, 0.8, 1.0, 0.2);
	glPushMatrix();
	glScalef(1.0, WING_LENGTH / WING_WIDTH, 1.0);
	gluDisk(p, 0.0, WING_WIDTH, 30, 30);
	glPopMatrix();
}

void object() {
	// Draw the body.
	glPushMatrix();
	body();
	glPopMatrix();

	// Draw the head.
	glPushMatrix();
	glTranslatef(-HEAD_RADIUS - BODY_RADIUS + 0.1, 0.0, 0.0);
	head();
	glPopMatrix();

	// Draw the abdomen.
	glPushMatrix();
	glColor3f(0.1, 0.1, 0.0); // dark abdomen
	glTranslatef(BODY_RADIUS + ABDOMEN_RADIUS * ABDOMEN_SCALE - 0.1, 0.0, 0.0);
	abdomen();
	glPopMatrix();

	// Draw the sting.
	glPushMatrix();
	glTranslatef(BODY_RADIUS + ABDOMEN_RADIUS * ABDOMEN_SCALE * 2 - 0.5, 0.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	sting();
	glPopMatrix();

	// Draw the left atenna.
	glPushMatrix();
	glTranslatef(-HEAD_RADIUS - BODY_RADIUS - 0.2, 0.0, 0.0);
	glRotatef(ATENNA_ANGLE, 0.0, 0.0, 1.0);
	glRotatef(-75.0, 1.0, 0.0, 0.0);
	atenna();
	glPopMatrix();

	// Draw the right atenna.
	glPushMatrix();
	glTranslatef(-HEAD_RADIUS - BODY_RADIUS - 0.2, 0.0, 0.0);
	glRotatef(ATENNA_ANGLE, 0.0, 0.0, 1.0);
	glRotatef(-105.0, 1.0, 0.0, 0.0);
	atenna();
	glPopMatrix();

	// Draw the legs on the left.
	for (int i = -1; i <= 1; i++) {
		glPushMatrix();
		glTranslatef(i * LEG_GAP, 0.0, 0.0);
		glRotatef(5.0, 0.0, 0.0, 1.0);          // additional flying angle
		glRotatef(90.0 - LEG_ANGLE, 1.0, 0.0, 0.0);
		leg(UPPERLEG_LENGTH * (1 + i * 0.1), LOWERLEG_LENGTH * (1 + i * 0.1));
		glPopMatrix();
	}

	// Draw the legs on the right.
	for (int i = -1; i <= 1; i++) {
		glPushMatrix();
		glTranslatef(i * LEG_GAP, 0.0, 0.0);
		glRotatef(5.0, 0.0, 0.0, 1.0);          // additional flying angle
		glRotatef(90.0 + LEG_ANGLE, 1.0, 0.0, 0.0);
		glRotatef(180, 0.0, 0.0, 1.0);
		leg(UPPERLEG_LENGTH * (1 + i * 0.1), LOWERLEG_LENGTH * (1 + i * 0.1));
		glPopMatrix();
	}

	// Draw the forewings.
	for (int i = -1; i <= 1; i += 2) {
		glPushMatrix();
		glTranslatef(0.0, cos(WING_GAPANGLE) - 0.2, (sin(WING_GAPANGLE) - 0.2) * i);
		glRotatef(i * theta_wing, 1.0, 0.0, 0.0);
		glTranslatef(0.0, -cos(WING_GAPANGLE) + 0.2, -(sin(WING_GAPANGLE) - 0.2) * i);
		glRotatef(FOREWING_ANGLE, 0.0, -i * sin(WING_GAPANGLE), cos(WING_GAPANGLE));
		glRotatef(i * WING_GAPANGLE, 1.0, 0.0, 0.0);
		glTranslatef(0.0, BODY_RADIUS + WING_LENGTH - 0.2, 0.0);
		wing();
		glPopMatrix();
	}

	// Draw the backwings.
	for (int i = -1; i <= 1; i += 2) {
		glPushMatrix();
		glTranslatef(0.0, cos(WING_GAPANGLE) - 0.2, (sin(WING_GAPANGLE) - 0.2) * i);
		glRotatef(i * theta_wing, 1.0, 0.0, 0.0);
		glTranslatef(0.0, -cos(WING_GAPANGLE) + 0.2, -(sin(WING_GAPANGLE) - 0.2) * i);
		glRotatef(BACKWING_ANGLE, 0.0, -i * sin(WING_GAPANGLE), cos(WING_GAPANGLE));
		glRotatef(i * WING_GAPANGLE, 1.0, 0.0, 0.0);
		glTranslatef(0.0, BODY_RADIUS + WING_LENGTH * 0.7 - 0.2, 0.0);
		glScalef(0.7, 0.7, 0.7);                // make backwings smaller than forewings
		wing();
		glPopMatrix();
	}
}



/* >>>>>>>>>>   INTERACTIONS   <<<<<<<<<< */
/* >>>>>>>>>>   INTERACTIONS   <<<<<<<<<< */
/* >>>>>>>>>>   INTERACTIONS   <<<<<<<<<< */

void display() {
	// clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(-1.0, 0.5, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // isometric view

	/* JUMPING */
	glTranslatef(posX, posY, posZ);

	/* ROTATION */
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	object();
	glutSwapBuffers();
	glFlush();
}

void specialkey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT:
			axis = 0;   // x-axis
			break;
		case GLUT_KEY_UP:
			axis = 1;   // y-axis
			break;
		case GLUT_KEY_RIGHT:
			axis = 2;   // z-axis
			break;
		case GLUT_KEY_DOWN:
			rotate_state = !rotate_state;   // stop/start rotating
			break;
	}
}

void idle() {
	/* FLYING */
	if (fly_state == GL_TRUE) {
		if (flip_direction == 1) {      // flip downwards
			theta_wing += FLIP;
			if (theta_wing >= 90.0) {
				flip_direction = -1;    // then flip upwards
			}
		}
		if (flip_direction == -1) {     // flip upwards
			theta_wing -= FLIP;
			if (theta_wing <= -10.0) {
				flip_direction = 1;     // then flip downwards
			}
		}
	}
	/* ROTATION */
	if (rotate_state == GL_TRUE) {
		theta[axis] += 1;
		if (theta[axis] > 360.0) theta[axis] -= 360.0;
	}

	glutPostRedisplay();
}

// set up the menu
void mymenu(int id) {
	if (id == 1) {
		srand((unsigned) time(NULL));       // generate a random position
		posX = rand() % 12 - 6;
		posY = rand() % 12 - 6;
		//        posZ = rand()%12 - 6;
	} else if (id == 2) {
		fly_state = !fly_state;
	} else if (id == 3) {
		rotate_state = !rotate_state;
	} else if (id == 4) {                      // reset all as just launched
		theta[0] = theta[1] = theta[2] = 0.0;
		axis = 1;
		rotate_state = GL_FALSE;
		posX = 0, posY = 0, posZ = 0;
		fly_state = GL_FALSE;
		theta_wing = 0.0;
		flip_direction = 1;
	} else return;
}

void createMenu() {
	int id;
	id = glutCreateMenu(mymenu);
	glutAddMenuEntry("Jump", 1);
	glutAddMenuEntry("Fly", 2);
	glutAddMenuEntry("Rotate", 3);
	glutAddMenuEntry("RESET ALL", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	return;
}

void init() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	p = gluNewQuadric();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(WIN_LEFT, WIN_RIGHT, WIN_BOTTOM * (GLfloat) h / (GLfloat) w, WIN_TOP * (GLfloat) h / (GLfloat) w,
		        WIN_NEAR, WIN_FAR);
	else
		glOrtho(WIN_LEFT * (GLfloat) w / (GLfloat) h, WIN_RIGHT * (GLfloat) w / (GLfloat) h, WIN_BOTTOM, WIN_TOP,
		        WIN_NEAR, WIN_FAR);
}

/* >>>>>>>>>>   MAIN   <<<<<<<<<< */
/* >>>>>>>>>>   MAIN   <<<<<<<<<< */
/* >>>>>>>>>>   MAIN   <<<<<<<<<< */

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("QueenBee");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutSpecialFunc(specialkey);
	glEnable(GL_DEPTH_TEST);
	init();
	createMenu();
	glutMainLoop();
}
