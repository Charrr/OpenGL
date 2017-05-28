#include <stdlib.h>
#include <GL/glut.h>

#define HEAD_X_RADIUS 1.7
#define HEAD_Y_RADIUS 1.5
#define HEAD_Z_RADIUS 1.6
#define LOW_BODY_X_RADIUS 3.2
#define LOW_BODY_Y_RADIUS 2.0
#define LOW_BODY_Z_RADIUS 2.6
#define UP_BODY_RADIUS 2.7
#define EYE_RADIUS 0.5
#define AUX_LEG_LEN 1.5
#define AUX_FOOT_LEN 1.6
#define AUX_LEG_RADIUS 0.2
#define AUX_FOOT_RADIUS 0.1
#define KNEE_RADIUS 0.13
#define LOW_LEG_LEN 3.0
#define LOW_LEG_LOW_RADIUS 0.3
#define LOW_LEG_UP_RADIUS 0.2
#define MIDDLE_LEG_LEN 2.8
#define MIDDLE_LEG_LOW_RADIUS 0.2
#define MIDDLE_LEG_UP_RADIUS 0.1
#define UP_LEG_LEN 1.6
#define UP_LEG_LOW_RADIUS 0.1
#define UP_LEG_UP_RADIUS 0.07
#define FOOT_LEN 0.8
#define FOOT_RADIUS 0.07

GLfloat theta[20] = {0.0, 0.0, 0.0};
GLint menuID = 0;
GLint submenu_id1 = 0;
GLint submenu_id2 = 1;
GLint submenu_id3 = 2;
GLfloat transX = 0;
GLfloat transZ = 0;
GLfloat dir = 0;
GLint move1, move2, move3, move4, move5, move6, move7, move8, move9, move10, move11, move12, move13, move14, move15, move16, move17 = 1;
GLboolean isRound = GL_FALSE;
GLboolean trans = GL_FALSE;
GLboolean bend = GL_FALSE;
GLboolean relative = GL_TRUE;
GLboolean color = GL_FALSE;
GLboolean irony = GL_FALSE;
GLboolean wooden = GL_FALSE;
GLboolean plastic = GL_FALSE;

GLUquadricObj *obj;

//shading...
typedef struct materialStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
} materialStruct;

materialStruct smoothMaterials = {
		{0.0, 0.0, 0.0, 1.0},
		{0.0, 0.0, 0.0, 1.0},
		{1.0, 1.0, 1.0, 1.0},
		70
};
materialStruct roughMaterials = {
		{0.6, 0.0, 0.0, 0.6},
		{1.0, 0.0, 0.0, 1.0},
		{0.0, 0.0, 0.0, 1.0},
		0
};
materialStruct legMaterials = {
		{0.55, 0.15, 0.0, 0.6},
		{0.55, 0.15, 0.0, 1.0},
		{0.0, 0.0, 0.0, 1.0},
		0
};

materialStruct plasticMaterials = {
		{0.3, 0.3, 0.3, 0.2},
		{0.2, 0.2, 0.2, 1.0},
		{0.6, 0.6, 0.6, 1.0},
		80
};

materialStruct woodenMaterials = {
		{0.4, 0.4, 0.4, 0.6},
		{0.8, 0.7, 0.3, 1.0},
		{0.0, 0.0, 0.0, 1.0},
		0
};

materialStruct ironyMaterials = {
		{0.2, 0.2, 0.2, 0.3},
		{0.7, 0.7, 0.7, 1.0},
		{0.7, 0.7, 0.7, 0.4},
		20
};

typedef struct lightingStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
} lightingStruct;

lightingStruct whiteLighting = {
		{0.0, 0.0, 0.0, 1.0},
		{1.0, 1.0, 1.0, 1.0},
		{1.0, 1.0, 1.0, 1.0}
};

lightingStruct coloredLighting = {
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 1.0, 0.0, 1.0},
		{0.0, 0.0, 0.0, 0.6}
};

GLfloat light0_pos[4] = {-3.0, 0.0, .0, 0.0};
GLfloat light1_pos[4] = {-5.0, 1.0, -5.0, 0.0};

materialStruct *currentMaterials;
lightingStruct *currentLighting;

//individual parts of the spider

void head() {
	glPushMatrix();
	glScalef(HEAD_X_RADIUS, HEAD_Y_RADIUS, HEAD_Z_RADIUS);
	gluSphere(obj, 1, 30, 30);
	glPopMatrix();
}

void lowBody() {
	glPushMatrix();
	glScalef(LOW_BODY_X_RADIUS, LOW_BODY_Y_RADIUS, LOW_BODY_Z_RADIUS);
	gluSphere(obj, 1, 30, 30);
	glPopMatrix();
}

void upBody() {
	glPushMatrix();
	glScalef(UP_BODY_RADIUS, UP_BODY_RADIUS, UP_BODY_RADIUS);
	gluSphere(obj, 1, 30, 30);
	glPopMatrix();
}

void eye() {
	glPushMatrix();
	glScalef(EYE_RADIUS, EYE_RADIUS, EYE_RADIUS);
	gluSphere(obj, 1, 10, 10);
	glPopMatrix();
}

void auxLeftLeg() {
	glPushMatrix();
	glTranslatef(0.0, 0.5 * AUX_LEG_LEN, 0.0);
	glRotatef(-45.0, 1.0, 0.0, 0.0);
	glRotatef(-45.0, 0.0, 1.0, 0.0);
	glRotatef(45.0, 0.0, 0.0, 1.0);
	gluCylinder(obj, AUX_LEG_RADIUS, 0.5 * AUX_LEG_RADIUS, AUX_LEG_LEN, 30, 30);
	glPopMatrix();
}

void knee() {
	glPushMatrix();
	gluSphere(obj, KNEE_RADIUS, 20, 20);
	glPopMatrix();
}

void auxFoot() {
	glPushMatrix();
	glTranslatef(0.0, -0.45, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glutWireCone(AUX_FOOT_RADIUS, AUX_FOOT_LEN, 30, 30);
	glPopMatrix();
}

void auxRightLeg() {
	glPushMatrix();
	glTranslatef(0.0, 0.5 * AUX_LEG_LEN, 0.0);
	glRotatef(45.0, 1.0, 0.0, 0.0);
	glRotatef(-135.0, 0.0, 1.0, 0.0);
	glRotatef(-45.0, 0.0, 0.0, 1.0);
	gluCylinder(obj, AUX_LEG_RADIUS, 0.5 * AUX_LEG_RADIUS, AUX_LEG_LEN, 30, 30);
	glPopMatrix();
}

void leftLowLeg() {
	glPushMatrix();
	glRotatef(-30.0, 0.0, 1.0, 0.0);
	glRotatef(-50.0, 1.0, 0.0, 0.0);
	gluCylinder(obj, LOW_LEG_LOW_RADIUS, LOW_LEG_UP_RADIUS, LOW_LEG_LEN, 30, 30);
	glPopMatrix();
}

void leftMiddleLeg() {
	glPushMatrix();
	glRotatef(-35.0, 0.0, 1.0, 0.0);
	glRotatef(45.0, 1.0, 0.0, 0.0);
	gluCylinder(obj, MIDDLE_LEG_LOW_RADIUS, MIDDLE_LEG_UP_RADIUS, MIDDLE_LEG_LEN, 30, 30);
	glPopMatrix();
}

void leftUpLeg() {
	glPushMatrix();
	glRotatef(-40.0, 0.0, 1.0, 0.0);
	glRotatef(75.0, 1.0, 0.0, 0.0);
	gluCylinder(obj, UP_LEG_LOW_RADIUS, UP_LEG_UP_RADIUS, UP_LEG_LEN, 30, 30);
	glPopMatrix();
}

void leftFoot() {
	glPushMatrix();
	glRotatef(-50.0, 0.0, 1.0, 0.0);
	glRotatef(25.0, 1.0, 0.0, 0.0);
	glutWireCone(FOOT_RADIUS, FOOT_LEN, 30, 30);
	glPopMatrix();
}

void rightLowLeg() {
	glPushMatrix();
	glRotatef(30.0, 0.0, 1.0, 0.0);
	glRotatef(-130.0, 1.0, 0.0, 0.0);
	gluCylinder(obj, LOW_LEG_LOW_RADIUS, LOW_LEG_UP_RADIUS, LOW_LEG_LEN, 30, 30);
	glPopMatrix();
}

void rightMiddleLeg() {
	glPushMatrix();
	glRotatef(35.0, 0.0, 1.0, 0.0);
	glRotatef(135.0, 1.0, 0.0, 0.0);
	gluCylinder(obj, MIDDLE_LEG_LOW_RADIUS, MIDDLE_LEG_UP_RADIUS, MIDDLE_LEG_LEN, 30, 30);
	glPopMatrix();
}

void rightUpLeg() {
	glPushMatrix();
	glRotatef(40.0, 0.0, 1.0, 0.0);
	glRotatef(105.0, 1.0, 0.0, 0.0);
	gluCylinder(obj, UP_LEG_LOW_RADIUS, UP_LEG_UP_RADIUS, UP_LEG_LEN, 30, 30);
	glPopMatrix();
}

void rightFoot() {
	glPushMatrix();
	glRotatef(50.0, 0.0, 1.0, 0.0);
	glRotatef(155.0, 1.0, 0.0, 0.0);
	glutWireCone(FOOT_RADIUS, FOOT_LEN, 30, 30);
	glPopMatrix();
}

//the whole spider

void spider() {
	glTranslatef(transX, 0.0, transZ);
	glRotatef(theta[4], 0.0, 1.0, 0.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &smoothMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	head();
	glPushMatrix();
	glTranslatef(3.5, 0.5, 0.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &smoothMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	lowBody();
//   
	glTranslatef(0.6, 0.7, 0.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &smoothMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	upBody();
//   
	//left eye
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.4, 0.0, 0.5);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &roughMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	eye();

	//right eye
	glTranslatef(0.0, 0.0, -1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &roughMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	eye();
//   
	//left aux leg+foot
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.0, -1.3, 0.8);
	glRotatef(theta[1], 0.0, 0.0, 1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &smoothMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	auxLeftLeg();

	glTranslatef(-1.0, 1.95, 0.7);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &smoothMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	auxFoot();

	glTranslatef(0.0, -0.5, 0.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &smoothMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	knee();

	//right aux leg+foot
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.0, -1.3, -0.8);
	glRotatef(-theta[1], 0.0, 0.0, 1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &smoothMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	auxRightLeg();

	glTranslatef(-1.0, 1.95, -0.7);
	glRotatef(-theta[2], 0.0, 0.0, 1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &smoothMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	auxFoot();

	glTranslatef(0.0, -0.5, 0.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &smoothMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	knee();


	//left first leg
	glPopMatrix();
	glPushMatrix();
	glRotatef(theta[3], 1.0, 0.0, 0.0);
	//leftLeg();
	glTranslatef(-0.7, 0.0, 1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	leftLowLeg();

	glTranslatef(-0.9, 2.25, 1.5);
	glRotatef(theta[5], 0.0, 1.0, 1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	leftMiddleLeg();

	glTranslatef(-1.1, -1.9, 1.58);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	leftUpLeg();

	glTranslatef(-0.22, -1.45, 0.27);
	glRotatef(-theta[6], 0.0, 0.0, 1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	leftFoot();

	//right first leg
	glPopMatrix();
	glPushMatrix();
	glRotatef(theta[3], 1.0, 0.0, 0.0);
	//rightLeg();
	glTranslatef(-0.7, 0.0, -1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	rightLowLeg();

	glTranslatef(-0.9, 2.25, -1.5);
	glRotatef(-theta[5], 0.0, 1.0, 1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	rightMiddleLeg();

	glTranslatef(-1.1, -1.9, -1.58);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	rightUpLeg();

	glTranslatef(-0.22, -1.45, -0.27);
	glRotatef(-theta[6], 0.0, 0.0, 1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	rightFoot();

	//left second leg
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.3, -0.3);
	glScalef(1.2, 1.3, 1.0);
	glRotatef(30.0, 0.0, 1.0, 0.0);
	glRotatef(theta[8], 1.0, 0.0, 0.0);
	//leftLeg();
	glTranslatef(-0.7, 0.0, 1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	leftLowLeg();

	glTranslatef(-0.9, 2.25, 1.5);
	glRotatef(theta[9], 0.0, 1.0, 1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	leftMiddleLeg();

	glTranslatef(-1.1, -1.9, 1.58);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	leftUpLeg();

	glTranslatef(-0.22, -1.45, 0.27);
	glRotatef(-theta[10], 0.0, 0.0, 1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	leftFoot();

	//right second leg
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.3, 0.3);
	glScalef(1.2, 1.3, 1.0);
	glRotatef(-30.0, 0.0, 1.0, 0.0);
	glRotatef(theta[7], 1.0, 0.0, 0.0);
	//rightLeg();
	glTranslatef(-0.7, 0.0, -1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	rightLowLeg();

	glTranslatef(-0.9, 2.25, -1.5);
	glRotatef(-theta[9], 0.0, 1.0, 1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	rightMiddleLeg();

	glTranslatef(-1.1, -1.9, -1.58);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	rightUpLeg();

	glTranslatef(-0.22, -1.45, -0.27);
	glRotatef(-theta[10], 0.0, 0.0, 1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	rightFoot();

	//left Third leg
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, -0.6, -0.3);
	glScalef(1.4, 1.9, 0.9);
	glRotatef(-10, 1.0, 0.0, 0.0);
	glRotatef(50.0, 0.0, 1.0, 0.0);
	glRotatef(theta[12], 1.0, 0.0, 0.0);
	//leftLeg();
	glTranslatef(-0.7, 0.0, 1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	leftLowLeg();

	glTranslatef(-0.9, 2.25, 1.5);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	leftMiddleLeg();

	glTranslatef(-1.1, -1.9, 1.58);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	leftUpLeg();

	glTranslatef(-0.22, -1.45, 0.27);
	glRotatef(-theta[13], 0.0, 0.0, 1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	leftFoot();

	//right Third leg
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, -0.6, 0.3);
	glScalef(1.4, 1.9, 0.9);
	glRotatef(10, 1.0, 0.0, 0.0);
	glRotatef(-50.0, 0.0, 1.0, 0.0);
	glRotatef(theta[11], 1.0, 0.0, 0.0);
	//rightLeg();
	glTranslatef(-0.7, 0.0, -1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	rightLowLeg();

	glTranslatef(-0.9, 2.25, -1.5);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	rightMiddleLeg();

	glTranslatef(-1.1, -1.9, -1.58);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	rightUpLeg();

	glTranslatef(-0.22, -1.45, -0.27);
	glRotatef(-theta[13], 0.0, 0.0, 1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	rightFoot();

	//left Fourth leg
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.6, 0.7, -0.3);
	glScalef(1.8, 1.6, 1.6);
	glRotatef(10, 1.0, 0.0, 0.0);
	glRotatef(80.0, 0.0, 1.0, 0.0);
	glRotatef(-theta[14], 1.0, 0.0, 0.0);
	//leftLeg();
	glTranslatef(-0.7, 0.0, 1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	leftLowLeg();

	glTranslatef(-0.9, 2.25, 1.5);
	glRotatef(theta[16], 1.0, 1.0, 0.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	leftMiddleLeg();

	glTranslatef(-1.1, -1.9, 1.58);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	leftUpLeg();

	glTranslatef(-0.22, -1.45, 0.27);
	glRotatef(theta[18], 0.0, 0.0, 1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	leftFoot();

	//right Fourth leg
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.6, 0.7, 0.3);
	glScalef(1.8, 1.6, 1.6);
	glRotatef(-10, 1.0, 0.0, 0.0);
	glRotatef(-80.0, 0.0, 1.0, 0.0);
	glRotatef(-theta[15], 1.0, 0.0, 0.0);
	//rightLeg();
	glTranslatef(-0.7, 0.0, -1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	rightLowLeg();

	glTranslatef(-0.9, 2.25, -1.5);
	glRotatef(theta[17], 1.0, 1.0, 0.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	rightMiddleLeg();

	glTranslatef(-1.1, -1.9, -1.58);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	rightUpLeg();

	glTranslatef(-0.22, -1.45, -0.27);
	glRotatef(theta[18], 0.0, 0.0, 1.0);

	if (irony) currentMaterials = &ironyMaterials;
	else if (wooden) currentMaterials = &woodenMaterials;
	else if (plastic) currentMaterials = &plasticMaterials;
	else currentMaterials = &legMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	rightFoot();

	glPopMatrix();
}

//display function

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(-1, 1, 1, 0, 0, 0, 0.0, 1.0, 0.0);
	//gluQuadricDrawStyle(obj, GLU_LINE);

	glRotatef(theta[0], 0.0, 1.0, 0.0);
	//glColor3f (0.0, 0.0, 1.0);
	if (relative) {
		if (color) glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
		else glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	}

	spider();

	glutSwapBuffers();
}

//click mouse

void mymouse(GLint button, GLint state, GLint x, GLint y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		isRound = !isRound;
		bend = !bend;
	}
}

//init function

void init() {
	int viewpoint = 0;

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, viewpoint);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*currentMaterials = &smoothMaterials;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials -> ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials -> diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials -> specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials -> shininess);
	if(color){
	currentLighting = &coloredLighting;

	glLightfv(GL_LIGHT1, GL_AMBIENT, currentLighting -> ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, currentLighting -> diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, currentLighting -> specular);

	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	obj = gluNewQuadric();
	}else{*/
	currentLighting = &whiteLighting;

	glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);

	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	obj = gluNewQuadric();
}

//reshape function

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15.0, 15.0, -15.0, 15.0, -15.0, 15.0);
}

//animation

void idle() {
	if (isRound) {
		theta[0] += 0.2;
		if (theta[0] > 360) theta[0] -= 360;
	}
	//rotate aux legs
	if (bend) {
		if (move1 > 0) {
			theta[1] += 0.5;
			if (theta[1] > 10) {
				move1 = -1;
				theta[1] -= 0.5;
			}
		} else {
			theta[1] -= 0.5;
			if (theta[1] < -20) {
				move1 = 1;
				theta[1] += 0.5;
			}
		}
	}
	if (bend) {
		if (move2 > 0) {
			theta[2] += 0.1;
			if (theta[2] > 5) {
				move2 = -1;
				theta[2] -= 0.1;
			}
		} else {
			theta[2] -= 0.1;
			if (theta[2] < -5) {
				move2 = 1;
				theta[2] += 0.1;
			}
		}
	}
	//rotate first legs
	if (bend) {//lower leg
		if (move3 > 0) {
			theta[3] += 0.1;
			if (theta[3] > 7) {
				move3 = -1;
				theta[3] -= 0.1;
			}
		} else {
			theta[3] -= 0.1;
			if (theta[3] < -4) {
				move3 = 1;
				theta[3] += 0.1;
			}
		}
	}
	if (bend) {//middle leg
		if (move4 > 0) {
			theta[5] += 0.25;
			if (theta[5] > 12.5) {
				move4 = -1;
				theta[5] -= 0.25;
			}
		} else {
			theta[5] -= 0.25;
			if (theta[5] < -12.5) {
				move4 = 1;
				theta[5] += 0.25;
			}
		}
	}
	if (bend) {//foot
		if (move5 > 0) {
			theta[6] += 0.5;
			if (theta[6] > 0) {
				move5 = -1;
				theta[6] -= 0.5;
			}
		} else {
			theta[6] -= 0.5;
			if (theta[6] < -50) {
				move5 = 1;
				theta[6] += 0.5;
			}
		}
	}
	//rotate second legs
	if (bend) {//lower leg
		if (move6 > 0) {
			theta[7] += 0.1;
			if (theta[7] > 20) {
				move6 = -1;
				theta[7] -= 0.1;
			}
		} else {
			theta[7] -= 0.1;
			if (theta[7] < -6) {
				move6 = 1;
				theta[7] += 0.1;
			}
		}
	}
	if (bend) {
		if (move7 > 0) {
			theta[8] += 0.15;
			if (theta[8] > 10) {
				move7 = -1;
				theta[8] -= 0.1;
			}
		} else {
			theta[8] -= 0.1;
			if (theta[8] < -20) {
				move7 = 1;
				theta[8] += 0.15;
			}
		}
	}
	if (bend) {//middle legs
		if (move8 > 0) {
			theta[9] += 0.2;
			if (theta[9] > 20) {
				move8 = -1;
				theta[9] -= 0.2;
			}
		} else {
			theta[9] -= 0.2;
			if (theta[9] < -35) {
				move8 = 1;
				theta[9] += 0.2;
			}
		}
	}
	if (bend) {//foot
		if (move9 > 0) {
			theta[10] += 0.5;
			if (theta[10] > 0) {
				move9 = -1;
				theta[10] -= 0.5;
			}
		} else {
			theta[10] -= 0.5;
			if (theta[10] < -50) {
				move9 = 1;
				theta[10] += 0.5;
			}
		}
	}
	//rotate third legs
	if (bend) {//lower leg
		if (move10 > 0) {
			theta[11] += 0.15;
			if (theta[11] > 25) {
				move10 = -1;
				theta[11] -= 0.25;
			}
		} else {
			theta[11] -= 0.25;
			if (theta[11] < -3) {
				move10 = 1;
				theta[11] += 0.15;
			}
		}
	}
	if (bend) {
		if (move11 > 0) {
			theta[12] += 0.2;
			if (theta[12] > 4.75) {
				move11 = -1;
				theta[12] -= 0.4;
			}
		} else {
			theta[12] -= 0.4;
			if (theta[12] < -25) {
				move11 = 1;
				theta[12] += 0.2;
			}
		}
	}
	if (bend) {//foot
		if (move12 > 0) {
			theta[13] += 0.5;
			if (theta[13] > 0) {
				move12 = -1;
				theta[13] -= 0.5;
			}
		} else {
			theta[13] -= 0.5;
			if (theta[13] < -50) {
				move12 = 1;
				theta[13] += 0.5;
			}
		}
	}
	//rotate forth legs
	if (bend) {//lower leg
		if (move13 > 0) {
			theta[14] += 0.2;
			if (theta[14] > 45) {
				move13 = -1;
				theta[14] -= 0.3;
			}
		} else {
			theta[14] -= 0.3;
			if (theta[14] < -1) {
				move13 = 1;
				theta[14] += 0.2;
			}
		}
	}
	if (bend) {
		if (move14 > 0) {
			theta[15] += 0.2;
			if (theta[15] > 2) {
				move14 = -1;
				theta[15] -= 0.4;
			}
		} else {
			theta[15] -= 0.4;
			if (theta[15] < -45) {
				move14 = 1;
				theta[15] += 0.2;
			}
		}
	}
	if (bend) {
		if (move15 > 0) {
			theta[16] += 0.35;
			if (theta[16] > 50) {
				move15 = -1;
				theta[16] -= 0.35;
			}
		} else {
			theta[16] -= 0.35;
			if (theta[16] < 0) {
				move15 = 1;
				theta[16] += 0.35;
			}
		}
	}
	if (bend) {
		if (move16 > 0) {
			theta[17] -= 0.35;
			if (theta[17] < -50) {
				move16 = -1;
				theta[17] += 0.35;
			}
		} else {
			theta[17] += 0.35;
			if (theta[17] > 0) {
				move16 = 1;
				theta[17] -= 0.35;
			}
		}
	}
	if (bend) {//foot
		if (move17 > 0) {
			theta[18] += 0.5;
			if (theta[18] > 0) {
				move17 = -1;
				theta[18] -= 0.5;
			}
		} else {
			theta[18] -= 0.5;
			if (theta[18] < -50) {
				move17 = 1;
				theta[18] += 0.5;
			}
		}
	}
	glutPostRedisplay();
}

//menu function
void myMenu(int id) {
	if (id == 1) {
		irony = GL_TRUE;
		wooden = GL_FALSE;
		plastic = GL_FALSE;
	}
	if (id == 2) {
		wooden = GL_TRUE;
		irony = GL_FALSE;
		plastic = GL_FALSE;
	}
	if (id == 3) {
		plastic = GL_TRUE;
		irony = GL_FALSE;
		wooden = GL_FALSE;
	}
}

void mysubmenu1(int id) {
	if (id == 1) relative = GL_FALSE;
	if (id == 2) relative = GL_TRUE;
}

void mysubmenu2(int id) {
	if (id == 1) {
		float a = 0.8;
		float model_ambient[] = {a, a, a, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
		glDisable(GL_LIGHT0);
	}
	if (id == 2) {
		float a = 0.0;
		float model_ambient[] = {a, a, a, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
		glEnable(GL_LIGHT0);
	}

}

void mysubmenu3(int id) {
	if (id == 1) {
		currentLighting = &whiteLighting;

		glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);
		glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);

		glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT0);
	}
	if (id == 2) {
		currentLighting = &coloredLighting;

		glLightfv(GL_LIGHT1, GL_AMBIENT, currentLighting->ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, currentLighting->diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, currentLighting->specular);
		glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);

		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
	}
}


//main function

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("spider");
	glutIdleFunc(idle);
	glutMouseFunc(mymouse);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glEnable(GL_DEPTH_TEST); /* Enable hidden-surface removal */
	init();
	submenu_id1 = glutCreateMenu(mysubmenu1);
	glutAddMenuEntry("fixed", 1);
	glutAddMenuEntry("relative", 2);
	submenu_id2 = glutCreateMenu(mysubmenu2);
	glutAddMenuEntry("ambient", 1);
	glutAddMenuEntry("distant", 2);
	submenu_id3 = glutCreateMenu(mysubmenu3);
	glutAddMenuEntry("white", 1);
	glutAddMenuEntry("colored", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	menuID = glutCreateMenu(myMenu);
	glutAddSubMenu("Light position", submenu_id1);
	glutAddSubMenu("Light type", submenu_id2);
	glutAddSubMenu("Light properties", submenu_id3);
	glutAddMenuEntry("Irony", 1);
	glutAddMenuEntry("Wooden", 2);
	glutAddMenuEntry("Plastic Light", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}
