#include <stdlib.h>
#include <GL/glut.h>

GLUquadricObj *quadric;

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	quadric = gluNewQuadric();

	float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
	float mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
	float mat_ambient_color[] = {0.8f, 0.8f, 0.2f, 1.0f};
	float mat_diffuse[] = {0.1f, 0.5f, 0.8f, 1.0f};
	float mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	float no_shininess = 0.0f;
	float low_shininess = 5.0f;
	float high_shininess = 100.0f;
	float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};

/* draw sphere in first row, first column
* diffuse reflection only; no ambient or specular */
	glPushMatrix();
	glTranslatef(-3.75f, 3.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	gluSphere(quadric, 1.0f, 16, 16);
	glPopMatrix();

/* draw sphere in first row, second column
* diffuse and specular reflection; low shininess; no ambient */
	glPushMatrix();
	glTranslatef(-1.25f, 3.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	gluSphere(quadric, 1.0f, 16, 16);
	glPopMatrix();

/* draw sphere in first row, third column
* diffuse and specular reflection; high shininess; no ambient */
	glPushMatrix();
	glTranslatef(1.25f, 3.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	gluSphere(quadric, 1.0f, 16, 16);
	glPopMatrix();

/* draw sphere in first row, fourth column
* diffuse reflection; emission; no ambient or specular reflection */
	glPushMatrix();
	glTranslatef(3.75f, 3.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	gluSphere(quadric, 1.0f, 16, 16);
	glPopMatrix();

/* draw sphere in second row, first column
* ambient and diffuse reflection; no specular */
	glPushMatrix();
	glTranslatef(-3.75f, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	gluSphere(quadric, 1.0f, 16, 16);
	glPopMatrix();

/* draw sphere in second row, second column
* ambient, diffuse and specular reflection; low shininess */
	glPushMatrix();
	glTranslatef(-1.25f, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	gluSphere(quadric, 1.0f, 16, 16);
	glPopMatrix();

/* draw sphere in second row, third column
* ambient, diffuse and specular reflection; high shininess */
	glPushMatrix();
	glTranslatef(1.25f, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	gluSphere(quadric, 1.0f, 16, 16);
	glPopMatrix();

/* draw sphere in second row, fourth column
* ambient and diffuse reflection; emission; no specular */
	glPushMatrix();
	glTranslatef(3.75f, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	gluSphere(quadric, 1.0f, 16, 16);
	glPopMatrix();

/* draw sphere in third row, first column
* colored ambient and diffuse reflection; no specular */
	glPushMatrix();
	glTranslatef(-3.75f, -3.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	gluSphere(quadric, 1.0f, 16, 16);
	glPopMatrix();

/* draw sphere in third row, second column
* colored ambient, diffuse and specular reflection; low shininess */
	glPushMatrix();
	glTranslatef(-1.25f, -3.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	gluSphere(quadric, 1.0f, 16, 16);
	glPopMatrix();

/* draw sphere in third row, third column
* colored ambient, diffuse and specular reflection; high shininess */
	glPushMatrix();
	glTranslatef(1.25f, -3.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	gluSphere(quadric, 1.0f, 16, 16);
	glPopMatrix();


/* draw sphere in third row, fourth column
 * colored ambient and diffuse reflection; emission; no specular */
	glPushMatrix();
	glTranslatef(3.75f, -3.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	gluSphere(quadric, 1.0f, 16, 16);
	glPopMatrix();

	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, -5, 5);
}

void init() {
	//light properties
	float ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
	float diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	float specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	float position[] = {1.0f, 1.0f, 0.3f, 0.0f};

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	//light model properties
	float model_ambient[] = {0.4f, 0.4f, 0.4f, 1.0f};
	int model_two_side = 1; //0=2sided, 1=1sided
	int viewpoint = 0;      //0=infiniteViewpoint, 1=localViewpoint

	/******************************
	 * Global ambient light *
	 * We can add an ambient light for the whole scene with
	 *  GL_LIGHT_MODEL_AMBIENT.
	 * The particularity of this ambient light is that it comes from any
	 * source. In addition, this light is activated by GL_LIGHTING so
	 * we don't have to enable any GL_LIGHTi to use it.
	 **********/

/* small white ambient light */
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);


	/******************************************
	   * Local and infinite viewpoint
	   * The GL_LIGHT_MODEL_LOCAL_VIEWER property determines the
	   * calculation of the specular highlight (the reflection).
	   * The reflection depends on the direction of two vectors :
	   *   -> vector from a vertex to the viewpoint
	   *   -> vector from the vertex to the light source
	   * Hence the reflection depends on the eye posiion.
	   * Two different calculations :
	   *   - with an infinite viewpoint : the direction between a vertex
	   * and the viewpoint is always the same.
	   *   - with a local viewpoint : the directions change.
	   * A local viewpoint is more realistic but an infinite viewpoint
	   * is a good approximation in many cases (e.g. if objects are fixed)
	   *********/

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, viewpoint);

	/*********************************************************
	* We can choose if we want that light affects the two sides of our
	* shapes or only one face (outside face defined by the normal
	* vector).
	* We can define this with GL_LIGHT_MODEL_TWO_SIDE.
	*********/

	//Only outside face because we don't see the inside of the spheres
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("shaded spheres");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glEnable(GL_DEPTH_TEST); /* Enable hidden-surface removal */
	init();
	glutMainLoop();
}
