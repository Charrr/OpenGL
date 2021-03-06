#include <GL/glut.h>
#include <math.h>

#define SIZE 20
#define WINDOW_SIZE 500
#define LEFT - SIZE
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
#define THRX_RADIUS 1.0 //radius of thorax
#define LEGS_GAP 1.5
#define COXA_RADIUS 0.2
#define FEMR_RADIUS 0.1
#define TIBA_RADIUS 0.05

#define JUMP_SPEED 0.1
#define ROTATE_SPEED 0.5
#define FLIP 1.0

#define MATERIAL_BODY 0
#define MATERIAL_TAIL 1
#define MATERIAL_ANTE 2
#define MATERIAL_WING 3
#define MATERIAL_LEGS 4

static GLUquadricObj *p;

static GLfloat theta[] = {0, 0, 0};
static GLint axis;
static GLfloat posX, posY, posZ;
static GLboolean jumpState;
static GLboolean rotateState;
static GLboolean flyState;

static GLfloat thetaOfWing;
static GLint directionOfFlip;
static GLint directionOfJumpX;
static GLint directionOfJumpY;

GLboolean relative = GL_TRUE;
GLboolean irony = GL_FALSE;
GLboolean wooden = GL_FALSE;
GLboolean plastic = GL_FALSE;

typedef struct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
} materialStruct;

materialStruct bodyMaterials = {
		{0.1f, 0.1f, 0.0f, 1.0f},
		{0.1f, 0.1f, 0.0f, 1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f},
		70
};

materialStruct tailMaterials = {
		{1.0f, 0.9f, 0.0f, 1.0f},
		{1.0f, 0.9f, 0.0f, 1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f},
		70
};

materialStruct anteMaterials = {
		{0.9f, 0.3f, 0.6f, 1.0f},
		{0.9f, 0.3f, 0.6f, 1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f},
		70
};

materialStruct wingMaterials = {
		{0.2f, 0.8f, 1.0f, 1.0f},
		{0.2f, 0.8f, 1.0f, 1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f},
		70
};

materialStruct legMaterialsFront = {
		{0.7f, 0.2f, 0.9f, 1.0f},
		{0.7f, 0.2f, 0.9f, 1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f},
		70
};

materialStruct plasticMaterials = {
		{0.3f, 0.3f, 0.3f, 0.2f},
		{0.2f, 0.2f, 0.2f, 1.0f},
		{0.6f, 0.6f, 0.6f, 1.0f},
		80
};

materialStruct woodenMaterials = {
		{0.4f, 0.4f, 0.4f, 0.6f},
		{0.8f, 0.7f, 0.3f, 1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f},
		0
};

materialStruct ironyMaterials = {
		{0.2f, 0.2f, 0.2f, 0.3f},
		{0.7f, 0.7f, 0.7f, 1.0f},
		{0.7f, 0.7f, 0.7f, 0.4f},
		20
};

typedef struct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat position[4];
} lightingStruct;

lightingStruct noonLighting = {
		{0.5f, 0.5f, 0.5f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 0.0f, 0.0f}
};

lightingStruct earlyLighting = {
		{0.4f,  0.4f,  0.4f,  1.0f},
		{0.99f, 0.67f, 0.13f, 1.0f},
		{0.99f, 0.67f, 0.13f, 1.0f},
		{-1.0f, 0.2f,  -1.0f, 0.0}
};

lightingStruct lateLighting = {
		{0.05f, 0.05f, 0.05f, 1.0f},
		{0.0f,  0.0f,  0.0f,  1.0f},
		{0.0f,  0.0f,  0.0f,  1.0f},
		{0.0f,  0.01f, 0.0f,  0.0f}
};

materialStruct *currentMaterial;
lightingStruct *currentLighting;

void material(int id) {
	if (irony) currentMaterial = &ironyMaterials;
	else if (wooden) currentMaterial = &woodenMaterials;
	else if (plastic) currentMaterial = &plasticMaterials;
	else if (id == MATERIAL_BODY) currentMaterial = &bodyMaterials;
	else if (id == MATERIAL_TAIL) currentMaterial = &tailMaterials;
	else if (id == MATERIAL_ANTE) currentMaterial = &anteMaterials;
	else if (id == MATERIAL_WING) currentMaterial = &wingMaterials;
	else if (id == MATERIAL_LEGS) currentMaterial = &legMaterialsFront;

	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterial->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterial->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterial->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterial->shininess);
	glMaterialfv(GL_BACK, GL_AMBIENT, currentMaterial->ambient);
	glMaterialfv(GL_BACK, GL_DIFFUSE, currentMaterial->diffuse);
	glMaterialfv(GL_BACK, GL_SPECULAR, currentMaterial->specular);
	glMaterialfv(GL_BACK, GL_SHININESS, &currentMaterial->shininess);
}

void body() {
	material(MATERIAL_BODY);
	glScalef(BODY_SCALE, 0.8, 0.8);
	gluSphere(p, BODY_RADIUS, 50, 50);
}

void tail() {
	material(MATERIAL_TAIL);
	glScalef(TAIL_SCALE, 0.6, 0.6);
	gluSphere(p, TAIL_RADIUS, 30, 30);
}

void antenna() {
	material(MATERIAL_ANTE);
	gluCylinder(p, ANTE_RADIUS, ANTE_RADIUS * 0.5, ANTE_LENGTH + BODY_RADIUS, 15, 15);
	glTranslatef(0.0, 0.0, ANTE_LENGTH + BODY_RADIUS);
	gluSphere(p, ANTE_RADIUS * 1.2, 50, 50);
}

void wing() {
	material(MATERIAL_WING);
	glScalef(1.0, WING_LENGTH / WING_WIDTH, 1.0);
	gluDisk(p, 0.0, WING_WIDTH, 30, 30);
}

void fLeg(int i) {
	material(MATERIAL_LEGS);
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
	material(MATERIAL_LEGS);
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
	material(MATERIAL_LEGS);
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

	/*For jumping*/
	glTranslatef(posX, posY, posZ);

	/*For rotation*/
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	if (relative)
		glLightfv(GL_LIGHT0, GL_POSITION, earlyLighting.position);

	butterfly();

	glutSwapBuffers();
}

void init() {
	theta[0] = theta[1] = theta[2] = 0.0;
	posX = posY = posZ = 0;
	axis = 1;
	jumpState = GL_FALSE;
	rotateState = GL_FALSE;
	flyState = GL_FALSE;
	thetaOfWing = 0.0;
	directionOfFlip = 1;
	directionOfJumpX = 1;
	directionOfJumpY = 1;

	relative = GL_TRUE;
	irony = GL_FALSE;
	wooden = GL_FALSE;
	plastic = GL_FALSE;

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	currentLighting = &noonLighting;
	glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);
	glLightfv(GL_LIGHT0, GL_POSITION, currentLighting->position);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	p = gluNewQuadric();
}

void myMouse(GLint button, GLint state, GLint x, GLint y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		jumpState = !jumpState;
		rotateState = !rotateState;
		flyState = !flyState;
	}
}

void specialKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT:
			axis = 0;   // x-axis
			rotateState = GL_TRUE;
			break;
		case GLUT_KEY_UP:
			axis = 1;   // y-axis
			rotateState = GL_TRUE;
			break;
		case GLUT_KEY_RIGHT:
			axis = 2;   // z-axis
			rotateState = GL_TRUE;
			break;
	}

}

void specialKeyUp(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT || key == GLUT_KEY_UP || key == GLUT_KEY_DOWN)
		rotateState = GL_FALSE;
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

void idle() {
	if (jumpState) {
		if (directionOfJumpX == 1) {
			posX += JUMP_SPEED;
			if (posX >= SIZE) directionOfJumpX = -1;
		}
		if (directionOfJumpX == -1) {
			posX -= JUMP_SPEED;
			if (posX <= -SIZE) directionOfJumpX = 1;
		}
		if (directionOfJumpY == 1) {
			posY += 2 * JUMP_SPEED;
			if (posY >= SIZE) directionOfJumpY = -1;
		}
		if (directionOfJumpY == -1) {
			posY -= 2 * JUMP_SPEED;
			if (posY <= -SIZE) directionOfJumpY = 1;
		}
	}
	if (rotateState) {
		theta[axis] += ROTATE_SPEED;
		if (theta[axis] > 360) theta[axis] -= 360;
	}
	if (flyState) {
		if (directionOfFlip == 1) {
			thetaOfWing += FLIP;
			if (thetaOfWing >= 90.0) directionOfFlip = -1;
		}
		if (directionOfFlip == -1) {
			thetaOfWing -= FLIP;
			if (thetaOfWing <= -10.0) directionOfFlip = 1;
		}
	}
	glutPostRedisplay();
}

void myMenu(int id) { //Main menu
	if (id == 1) {
		jumpState = !jumpState;
	}
	if (id == 2) {
		rotateState = !rotateState;
	}
	if (id == 3) {
		flyState = !flyState;
	}
	if (id == 4) {
		init();
	}
	if (id == 5) exit(0);
}

void subMenu0(int id) { //Material
	if (id == 1) {
		irony = GL_TRUE;
		wooden = GL_FALSE;
		plastic = GL_FALSE;
	}
	if (id == 2) {
		irony = GL_FALSE;
		wooden = GL_TRUE;
		plastic = GL_FALSE;
	}
	if (id == 3) {
		irony = GL_FALSE;
		wooden = GL_FALSE;
		plastic = GL_TRUE;
	}
}

void subMenu1(int id) { //Light position
	if (id == 1) relative = GL_FALSE;
	if (id == 2) relative = GL_TRUE;
}

void subMenu2(int id) { //Light type
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

void subMenu3(int id) { //Light properties
	if (id == 1) {
		currentLighting = &noonLighting;
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	if (id == 2) {
		currentLighting = &earlyLighting;
		glClearColor(0.66f, 0.54f, 0.00f, 0.5f);
	}
	if (id == 3) {
		currentLighting = &lateLighting;
		glClearColor(0.05f, 0.05f, 0.07f, 1.0f);
	}

	glLightfv(GL_LIGHT1, GL_AMBIENT, currentLighting->ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, currentLighting->diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, currentLighting->specular);
	glLightfv(GL_LIGHT1, GL_POSITION, currentLighting->position);

	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

void createMenu() {
	int subMenuID0 = glutCreateMenu(subMenu0);
	glutAddMenuEntry("Irony", 1);
	glutAddMenuEntry("Wooden", 2);
	glutAddMenuEntry("Plastic Light", 3);
	int subMenuID1 = glutCreateMenu(subMenu1);
	glutAddMenuEntry("Fixed", 1);
	glutAddMenuEntry("Relative", 2);
	int subMenuID2 = glutCreateMenu(subMenu2);
	glutAddMenuEntry("Ambient", 1);
	glutAddMenuEntry("Distant", 2);
	int subMenuID3 = glutCreateMenu(subMenu3);
	glutAddMenuEntry("Noon", 1);
	glutAddMenuEntry("Early evening", 2);
	glutAddMenuEntry("Late evening", 3);
	glutCreateMenu(myMenu);
	glutAddMenuEntry("Jump", 1);
	glutAddMenuEntry("Rotate", 2);
	glutAddMenuEntry("Fly", 3);
	glutAddSubMenu("Material", subMenuID0);
	glutAddSubMenu("Light position", subMenuID1);
	glutAddSubMenu("Light type", subMenuID2);
	glutAddSubMenu("Light properties", subMenuID3);
	glutAddMenuEntry("RESET ALL", 4);
	glutAddMenuEntry("Exit", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
	glutCreateWindow("butterfly");
	glutIdleFunc(idle);
	glutMouseFunc(myMouse);
	glutSpecialFunc(specialKey);
	glutSpecialUpFunc(specialKeyUp);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glEnable(GL_DEPTH_TEST);
	init();
	createMenu();
	glutMainLoop();
}
