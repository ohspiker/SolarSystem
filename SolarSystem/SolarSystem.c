/************************************************************************************
 File:
								main.c

 Description:
								A complete OpenGL program for the solar system

 Author:
								Olivia Handspiker
								handspiker@dal.ca
								B00799397

 Note:
								Some material in this project is adapted from course notes that have been
								posted to the course website. Everything else in this project is completely
								my own work, and falls in accordance with Dalhousie's Academic Integrity
								policy.
*************************************************************************************/
/* include the library header files */
#include <stdlib.h>
#include <stdio.h>
#include <freeglut.h>
#include <stdbool.h>
/*in order for pi to work we have to use this #define*/
#define _USE_MATH_DEFINES
#include <math.h>

#define _CRT_SECURE_NO_WARNINGS

/*values for star generation, the mininum and maximum coordinates that they will reach, and random locations and amount*/
#define MIN_STARCOORD (GLfloat) -200.0
#define MAX_STARCOORD (GLfloat) 200.0
#define RANDOM MIN_STARCOORD+((GLfloat)rand()/(GLfloat)RAND_MAX)*(MAX_STARCOORD-MIN_STARCOORD)
#define TOTAL_STARS 5000

/*this is the area of the solar system that will NOT have stars in it*/
#define SOLARSYSTEM_AREA 80.0 

/*how circle the orbit is (if it is low itll be a fun bunch of lines)*/
#define ORBIT_ACCURACY 100 

/*corona number and length*/
#define CORONA_NUMBER 200 
#define CORONA_LENGTH 2.5 

GLfloat upVector[3] = { 0.0, 1.0, 0.0 };  
GLfloat cameraView[3] = { 0.0, 0.0, 0.0 }; 
GLfloat cameraPosition[3] = { 0.0, 2.0, 20.0 }; 

GLUquadric* quad; //define quads
GLfloat delta = 0.0; 
GLfloat stars[TOTAL_STARS][3]; 

GLfloat cameraSpeedMul = 0.1; //if i dont include this, itll go way too far on a button press

GLfloat xOffset; 
GLfloat yOffset; 
GLfloat zOffset; 

GLfloat vertexes[10000][3] = {{0}};
GLint enterprisePolygon[10000][3] = {{0}};
GLint j = 0;

/*this is why i imported stdbool.h*/
bool moveLeft = false;
bool moveRight = false;
bool moveUp = false;
bool moveDown = false;
bool moveForward = false;
bool moveBackward = false;
bool starsOn = true;
bool ringOn = true;
bool coronaOn = true;
bool laserOn = false;
bool namesOn = false;

// sun/helios
GLfloat heliosRadius = 1.5;
// coronis 
GLfloat coronisDistance = 2.0;
GLfloat coronisRadius = 0.2;
GLfloat coronisSpeed = 6.0;
// kinmoku 
GLfloat kinmokuDistance = 4.0;
GLfloat kinmokuRadius = 0.4;
GLfloat kinmokuSpeed = 4.5;
// chu 
GLfloat chuDistance = 6.0; 
GLfloat chuRadius = 0.5; 
GLfloat chuSpeed = 4.0; 
// cocoon 
GLfloat cocoonDistance = 1.0; 
GLfloat cocoonRadius = 0.15; 
GLfloat cocoonSpeed = 3.0; 
// lethe 
GLfloat letheDistance = 8.0; 
GLfloat letheRadius = 0.3; 
GLfloat letheSpeed = 3.0; 
// mau 
GLfloat mauDistance = 10.0; 
GLfloat mauRadius = 0.9;
GLfloat mauSpeed = 2.5; 
// mermaid 
GLfloat mermaidDistance = 12.0; 
GLfloat mermaidRadius = 0.8; 
GLfloat mermaidSpeed = 1.5; 
// mnemosyne 
GLfloat mnemosyneDistance = 14.0; 
GLfloat mnemosyneRadius = 0.7; 
GLfloat mnemosyneSpeed = 1.0; 
// nemesis 
GLfloat nemesisDistance = 16.0; 
GLfloat nemesisRadius = 0.6; 
GLfloat nemesisSpeed = 0.5; 
// grimm 
GLfloat grimmDistance = 18.0; 
GLfloat grimmRadius = 0.1; 
GLfloat grimmSpeed = 0.25; 

/************************************************************************

Function:		
							drawRings

Description:	
							this function draws the rings around the planets. 
							i am calculating them using math.h that is imported
							cos and sin functions to draw the circles accurate
							to the planet's orbits. you have to use both cos and sin
							because if you use only one of those it will be very bad

*************************************************************************/
void drawRings()
{
	glColor3f(0.84f, 0.84f, 0.84f); //this sets the colour of every ring
	glLineWidth(0.1);

	// CHU (cocoons ring is inside of drawPlanets)
	glBegin(GL_LINE_LOOP);
	for (GLfloat angle = 0.0; angle <= 2 * M_PI; angle += 0.01) {
		glVertex3f(sin(angle) * (chuDistance + heliosRadius), 0.0, cos(angle) * (chuDistance + heliosRadius));
	}
	glEnd();

	// CORONIS
	glBegin(GL_LINE_LOOP);
	for (GLfloat angle = 0.0; angle <= 2 * M_PI; angle += 0.01) {
		glVertex3f(sin(angle) * (coronisDistance + heliosRadius), 0.0, cos(angle) * (coronisDistance + heliosRadius));
	}
	glEnd();

	// KINMOKU
	glBegin(GL_LINE_LOOP);
	for (GLfloat angle = 0.0; angle <= 2 * M_PI; angle += 0.01) {
		glVertex3f(sin(angle) * (kinmokuDistance + heliosRadius), 0.0, cos(angle) * (kinmokuDistance + heliosRadius));
	}
	glEnd();

	// LETHE
	glBegin(GL_LINE_LOOP);
	for (GLfloat angle = 0.0; angle <= 2 * M_PI; angle += 0.01) {
		glVertex3f(sin(angle) * (letheDistance + heliosRadius), 0.0, cos(angle) * (letheDistance + heliosRadius));
	}
	glEnd();

	// MAU
	glBegin(GL_LINE_LOOP);
	for (GLfloat angle = 0.0; angle <= 2 * M_PI; angle += 0.01) {
		glVertex3f(sin(angle) * (mauDistance + heliosRadius), 0.0, cos(angle) * (mauDistance + heliosRadius));
	}
	glEnd();

	// MERMAID
	glBegin(GL_LINE_LOOP);
	for (GLfloat angle = 0.0; angle <= 2 * M_PI; angle += 0.01) {
		glVertex3f(sin(angle) * (mermaidDistance + heliosRadius), 0.0, cos(angle) * (mermaidDistance + heliosRadius));
	}
	glEnd();

	// MNEMOSYNE
	glBegin(GL_LINE_LOOP);
	for (GLfloat angle = 0.0; angle <= 2 * M_PI; angle += 0.01) {
		glVertex3f(sin(angle) * (mnemosyneDistance + heliosRadius), 0.0, cos(angle) * (mnemosyneDistance + heliosRadius));
	}
	glEnd();

	// NEMESIS
	glBegin(GL_LINE_LOOP);
	for (GLfloat angle = 0.0; angle <= 2 * M_PI; angle += 0.01) {
		glVertex3f(sin(angle) * (nemesisDistance + heliosRadius), 0.0, cos(angle) * (nemesisDistance + heliosRadius));
	}
	glEnd();

	// GRIMM
	glBegin(GL_LINE_LOOP);
	for (GLfloat angle = 0.0; angle <= 2 * M_PI; angle += 0.01) {
		glVertex3f(sin(angle) * (grimmDistance + heliosRadius), 0.0, cos(angle) * (grimmDistance + heliosRadius));
	}
	glEnd();
}

/************************************************************************

Function:
							drawPlanets

Description:
							Draws all of my planets onto the screen in order.
							I use gluSphere to draw the planets.

							This also encapsulates the function which allows
							the planet name labels to be shown, because I draw
							them within the planet creation at the same time that
							the planets are built.

							My planets are named after Sailor Moon planets, if
							you are wondering where these names came from.


*************************************************************************/
void drawPlanets() {
	glPushMatrix();

	// HELIOS 
	quad = gluNewQuadric();
	glColor3f(1.0f, 1.0f, 0.0f); //a VERY yellow ~~Sun~~
	gluSphere(quad, heliosRadius, 20, 20);
	if (namesOn) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos3f(0.0, 1.6, 0.0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_12, "Helios");
	}

	// CORONIS
	glPushMatrix();
	glRotatef(delta * coronisSpeed, 0.0, 1.0, 0.0);
	glTranslatef(heliosRadius + coronisDistance, 0.0, 0);
	quad = gluNewQuadric();
	glColor3f(0.38f, 0.38f, 0.38f); //Coronis is mostly black but I want it to be visible
	gluSphere(quad, coronisRadius, 20, 20);
	if (namesOn) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos3f(0.0, 0.4, 0.0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_12, "Coronis");
	}
	glPopMatrix();

	// KINMOKU
	glPushMatrix();
	glRotatef(delta * kinmokuSpeed, 0.0, 1.0, 0.0);
	glTranslatef(heliosRadius + kinmokuDistance, 0.0, 0);
	quad = gluNewQuadric();
	glColor3f(0.49f, 0.65f, 0.85f); //sailor stars planet kinmoku is super neat!! looks blue to me :)
	gluSphere(quad, kinmokuRadius, 20, 20);
	if (namesOn) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos3f(0.0, 0.5, 0.0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_12, "Kinmoku");
	}
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	for (GLfloat angle = 0.0; angle <= 2 * M_PI; angle += 0.01) {
		glColor3f(0.49f, 0.65f, 0.85f);
		glVertex3f(sin(angle), 0.0, cos(angle));
	}
	glEnd();
	glPopMatrix();


	// CHU
	glPopMatrix();
	glPushMatrix();
	glRotatef(delta * chuSpeed, 0.0, 1.0, 0.0);
	glTranslatef(heliosRadius + chuDistance, 0.0, 0);
	quad = gluNewQuadric();
	glColor3f(0.88f, 0.88f, 0.88f); //Sailor Chu is kind of mostly white 
	gluSphere(quad, chuRadius, 20, 20);
	if (namesOn) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos3f(0.0, 0.6, 0.0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_12, "Chu");
	}

	//COCOON
	glColor3f(0.84f, 0.84f, 0.84f); // ring colour
	glLineWidth(0.1);
	if (ringOn) {
		glBegin(GL_LINE_LOOP);
		for (GLfloat angle = 0.0; angle <= 2 * M_PI; angle += 0.01) {
			glVertex3f(sin(angle) * cocoonDistance, 0.0, cos(angle) * cocoonDistance);
		}
		glEnd();
	}
	// moon rotations
	glRotatef(delta, 0.0, 1.0, 0.0);
	glTranslatef(cocoonDistance, 0, 0);
	quad = gluNewQuadric();
	glColor3f(0.55f, 0.77f, 0.24f); //green for Heavy Metal Papillon
	gluSphere(quad, cocoonRadius, 20, 20);
	if (namesOn) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos3f(0.0, 0.3, 0.0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_12, "Cocoon");
	}
	glPopMatrix();

	// LETHE
	glPushMatrix();
	glRotatef(delta * letheSpeed, 0.0, 1.0, 0.0);
	glTranslatef(heliosRadius + letheDistance, 0.0, 0);
	quad = gluNewQuadric();
	glColor3f(0.0f, 0.44f, 0.21f); //Lethe's got a dark green 
	gluSphere(quad, letheRadius, 20, 20);
	if (namesOn) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos3f(0.0, 0.4, 0.0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_12, "Lethe");
	}
	glPopMatrix();

	// MAU
	glPushMatrix();
	glRotatef(delta * mauSpeed, 0.0, 1.0, 0.0);
	glTranslatef(heliosRadius + mauDistance, 0.0, 0);
	quad = gluNewQuadric();
	glColor3f(0.58f, 0.58f, 0.58f); //grey for mid colour of the cats :)
	gluSphere(quad, mauRadius, 20, 20);
	if (namesOn) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos3f(0.0, 1.0, 0.0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_12, "Mau");
	}
	glPopMatrix();

	// MERMAID
	glPushMatrix();
	glRotatef(delta * mermaidSpeed, 0.0, 1.0, 0.0);
	glTranslatef(heliosRadius + mermaidDistance, 0.0, 0);
	quad = gluNewQuadric();
	glColor3f(0.26f, 0.54f, 0.79f); //cyan for this one 
	gluSphere(quad, mermaidRadius, 20, 20);
	if (namesOn) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos3f(0.0, 1.0, 0.0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_12, "Mermaid");
	}

	// MNEMOSYNE
	glPopMatrix();
	glPushMatrix();
	glRotatef(delta * mnemosyneSpeed, 0.0, 1.0, 0.0);
	glTranslatef(heliosRadius + mnemosyneDistance, 0.0, 0);
	quad = gluNewQuadric();
	glColor3f(0.96f, 0.58f, 0.47f); //pink for Mnemosyne
	gluSphere(quad, mnemosyneRadius, 20, 20);
	if (namesOn) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos3f(0.0, 1.0, 0.0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_12, "Mnemosyne");
	}

	// NEMESIS
	glPopMatrix();
	glPushMatrix();
	glRotatef(delta * nemesisSpeed, 0.0, 1.0, 0.0);
	glTranslatef(heliosRadius + nemesisDistance, 0.0, 0);
	quad = gluNewQuadric();
	glColor3f(0.61f, 0.04f, 0.05f); //dark red
	gluSphere(quad, nemesisRadius, 20, 20);
	if (namesOn) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos3f(0.0, 0.8, 0.0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_12, "Nemesis");
	}
	glPopMatrix();

	// GRIMM
	glPushMatrix();
	glRotatef(delta * grimmSpeed, 0.0, 1.0, 0.0);
	glTranslatef(heliosRadius + grimmDistance, 0.0, 0);
	quad = gluNewQuadric();
	glColor3f(0.29f, 0.0f, 0.28f); //a dark violet magenta
	gluSphere(quad, grimmRadius, 20, 20);
	if (namesOn) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos3f(0.0, 0.2, 0.0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_12, "Grimm");
	}
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	for (GLfloat angle = 0.0; angle <= 2 * M_PI; angle += 0.01) {
		glColor3f(0.29f, 0.0f, 0.28f);
		glVertex3f(sin(angle)*0.5, 0.0, cos(angle)*0.5);
	}
	glEnd();
	glPopMatrix();
}

/************************************************************************

Function:
							drawStars

Description:
							This draws the stars in random colours. 
							The stars array is defined at the top of this code, and
							they are drawn in the main function, because if I draw
							them here, they will be generating in random locations
							constantly.

*************************************************************************/
void drawStars() {
	if (starsOn) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_POINTS); //draws points
		for (int i = 0; i < TOTAL_STARS; i++) {
			glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
			glVertex3f(stars[i][0], stars[i][1], stars[i][2]);
		}
		glEnd();
	}
}

/************************************************************************

Function:
							drawCorona

Description:
							this function draws the corona of the sun (helios) by creating
							random lines that are yellow in the centre and transparent 
							orange at the outer points


*************************************************************************/
void drawCorona()
{
	glLineWidth(5.0);
	for (int i = 0; i < CORONA_NUMBER; i++) {
		GLfloat t = 2 * M_PI * rand() / (RAND_MAX + 1);
		glBegin(GL_LINES);
		glColor4f(0.8f, 0.8f, 0.0f, 1.0f); //yellow internal end
		glVertex3f(sin(t) * 1.25, cos(t) * 1.25, 0.0);
		glColor4f(0.96f, 0.58f, 0.11f, 0.1f); //transparent external end
		glVertex3f(sin(t) * CORONA_LENGTH, cos(t) * CORONA_LENGTH, 0.0);
		glEnd();
	}

}

/************************************************************************

Function:		
							crossMultiply

Description:	
							the crossMultiply function is necessary for calculation
							that i need when moving the camera left or right

*************************************************************************/
GLfloat* crossMultiply(GLfloat a[3], GLfloat b[3])
{
	// cross multiply between the three points in an array
	static GLfloat product[3];
	product[0] = (a[1] * b[2]) - (a[2] * b[1]);
	product[1] = (a[2] * b[0]) - (a[0] * b[2]);
	product[2] = (a[0] * b[1]) - (a[1] * b[0]);

	return product;
}

/************************************************************************

Function:		
							myDisplay

Description:
							display everything and buffer, includes movement 
							functions for camera display

*************************************************************************/
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// gets the forward vector through subtracting view and position
	GLfloat forwardVector[3] = { cameraView[0] - cameraPosition[0], cameraView[1] - cameraPosition[1] , cameraView[2] - cameraPosition[2] };

	if (moveForward) {
		cameraPosition[0] += forwardVector[0] * cameraSpeedMul;
		cameraPosition[1] += forwardVector[1] * cameraSpeedMul;
		cameraPosition[2] += forwardVector[2] * cameraSpeedMul;
		cameraView[0] += forwardVector[0] * cameraSpeedMul;
		cameraView[1] += forwardVector[1] * cameraSpeedMul;
		cameraView[2] += forwardVector[2] * cameraSpeedMul;
	}
	else if (moveBackward) {
		cameraPosition[0] -= forwardVector[0] * cameraSpeedMul;
		cameraPosition[1] -= forwardVector[1] * cameraSpeedMul;
		cameraPosition[2] -= forwardVector[2] * cameraSpeedMul;
		cameraView[0] -= forwardVector[0] * cameraSpeedMul;
		cameraView[1] -= forwardVector[1] * cameraSpeedMul;
		cameraView[2] -= forwardVector[2] * cameraSpeedMul;
	}

	if (moveLeft) {
		GLfloat* leftVector = crossMultiply(upVector, forwardVector);
		cameraPosition[0] += leftVector[0] * cameraSpeedMul;
		cameraPosition[1] += leftVector[1] * cameraSpeedMul;
		cameraPosition[2] += leftVector[2] * cameraSpeedMul;
		cameraView[0] += leftVector[0] * cameraSpeedMul;
		cameraView[1] += leftVector[1] * cameraSpeedMul;
		cameraView[2] += leftVector[2] * cameraSpeedMul;
	}
	else if (moveRight) {
		GLfloat* rightVector = crossMultiply(forwardVector, upVector);
		cameraPosition[0] += rightVector[0] * cameraSpeedMul;
		cameraPosition[1] += rightVector[1] * cameraSpeedMul;
		cameraPosition[2] += rightVector[2] * cameraSpeedMul;
		cameraView[0] += rightVector[0] * cameraSpeedMul;
		cameraView[1] += rightVector[1] * cameraSpeedMul;
		cameraView[2] += rightVector[2] * cameraSpeedMul;
	}

	if (moveUp) {
		cameraPosition[0] += upVector[0] * cameraSpeedMul * 2;
		cameraPosition[1] += upVector[1] * cameraSpeedMul * 2;
		cameraPosition[2] += upVector[2] * cameraSpeedMul * 2;
		cameraView[0] += upVector[0] * cameraSpeedMul * 2;
		cameraView[1] += upVector[1] * cameraSpeedMul * 2;
		cameraView[2] += upVector[2] * cameraSpeedMul * 2;
	}
	else if (moveDown) {
		cameraPosition[0] -= upVector[0] * cameraSpeedMul * 2;
		cameraPosition[1] -= upVector[1] * cameraSpeedMul * 2;
		cameraPosition[2] -= upVector[2] * cameraSpeedMul * 2;
		cameraView[0] -= upVector[0] * cameraSpeedMul * 2;
		cameraView[1] -= upVector[1] * cameraSpeedMul * 2;
		cameraView[2] -= upVector[2] * cameraSpeedMul * 2;
	}

	gluLookAt(cameraPosition[0], cameraPosition[1], cameraPosition[2], cameraView[0], cameraView[1], cameraView[2], 0.0, 1.0, 0.0);

	drawStars();
	drawPlanets();

	if (ringOn) {
		drawRings();
	}

	if (coronaOn) {
		drawCorona();
	}

	glColor4f(0.67f, 0.67f, 0.67f, 0.5f); //colour for the enterprise

	glPushMatrix();
	glLoadIdentity();
	glTranslatef(forwardVector[0], forwardVector[1] + 1.3, forwardVector[2] + 17); 
	for (int a = 0; a < j; a++) {
		glBegin(GL_POLYGON);
		glVertex3f(vertexes[enterprisePolygon[a][0] - 1][0], vertexes[enterprisePolygon[a][0] - 1][1], vertexes[enterprisePolygon[a][0] - 1][2]);
		glVertex3f(vertexes[enterprisePolygon[a][1] - 1][0], vertexes[enterprisePolygon[a][1] - 1][1], vertexes[enterprisePolygon[a][1] - 1][2]);
		glVertex3f(vertexes[enterprisePolygon[a][2] - 1][0], vertexes[enterprisePolygon[a][2] - 1][1], vertexes[enterprisePolygon[a][2] - 1][2]);
		glEnd();
	}

	// draw laser in front of enterprise
	
	if (laserOn) {
		glColor4f(0.96, 0.38, 0.38, 0.6);
		glTranslatef(0,0,-6);
		glutSolidCone(0.25,5,100,5);
	}
	
	glPopMatrix();
	glutSwapBuffers();

}

/************************************************************************

Function:		
							keyboardWriter

Description:	
							writes the controls onto the console screen

*************************************************************************/
void keyboardWriter()
{
	printf("Scene Controls\n");
	printf("-----------------\n");
	printf("r:	toggle rings\n");
	printf("s:	toggle stars\n");
	printf("c:	toggle the sun's corona\n");
	printf("l:	toggle lasers\n");
	printf("n:	toggle names\n\n");

	printf("Camera Controls\n");
	printf("-----------------\n");
	printf("Up	Arrow:	move up\n");
	printf("Down	Arrow:	move down\n");
	printf("Left	Arrow:	move left\n");
	printf("Right	Arrow:	move right\n");
	printf("Page	Up:	forward\n");
	printf("Page	Down:	backward\n");
}

/************************************************************************

Function:		
								myIdle

Description:	
								idle animation updates

*************************************************************************/
void myIdle()
{
	delta += 0.01f;

	if (moveUp) {
		yOffset += 0.2;
		moveUp = false;
	}
	if (moveDown) {
		yOffset -= 0.2;
		moveDown = false;
	}
	if (moveLeft) {
		xOffset -= 0.2;
		moveLeft = false;
	}
	if (moveRight) {
		xOffset += 0.2;
		moveRight = false;
	}
	if (moveForward) {
		zOffset -= 0.2;
		moveForward = false;
	}
	if (moveBackward) {
		zOffset += 0.2;
		moveBackward = false;
	}
	glutPostRedisplay();
}

/************************************************************************

Function:		
							specialKeys

Description:	
							this handles key input for the arrow and page buttons

*************************************************************************/
void specialKeys(unsigned char key)
{
	if (key == GLUT_KEY_LEFT)
		moveLeft = true;
	if (key == GLUT_KEY_RIGHT)
		moveRight = true;
	if (key == GLUT_KEY_UP)
		moveUp = true;
	if (key == GLUT_KEY_DOWN)
		moveDown = true;
	if (key == GLUT_KEY_PAGE_UP)
		moveForward = true;
	if (key == GLUT_KEY_PAGE_DOWN)
		moveBackward = true;
}

/************************************************************************

Function:		
							letterKeys

Description:
							this handles key inputs for the letter buttons

*************************************************************************/
void letterKeys(unsigned char key)
{
	if (key == 'r')
		ringOn = !ringOn;
	if (key == 's')
		starsOn = !starsOn;
	if (key == 'c')
		coronaOn = !coronaOn;
	if (key == 'l')
		laserOn = !laserOn;
	if (key == 'n')
		namesOn = !namesOn;
}

/************************************************************************

Function:		
								buildEnterprise

Description:	
								read the enterprise.txt file and build it. because of
								warnings with fopen and other functions, i had to
								go to my project settings and add to preprocessor,
								_CRT_SECURE_NO_WARNINGS

*************************************************************************/
void buildEnterprise()
{
	FILE* enterpriseFile;
	char buff[255];
	int i = 1;

	enterpriseFile = fopen("enterprise.txt", "r");

	fscanf(enterpriseFile, "%s", buff);
	fscanf(enterpriseFile, "%s", buff);
	sscanf(buff, "%f", &vertexes[0][0]);
	fscanf(enterpriseFile, "%s", buff);
	sscanf(buff, "%f", &vertexes[0][1]);
	fscanf(enterpriseFile, "%s", buff);
	sscanf(buff, "%f", &vertexes[0][2]);

	while (fscanf(enterpriseFile, "%s", buff) != EOF) {
		if (strcmp(buff, "v") == 0) {
			fscanf(enterpriseFile, "%s", buff); 
			sscanf(buff, "%f", &vertexes[i][0]);
			fscanf(enterpriseFile, "%s", buff);
			sscanf(buff, "%f", &vertexes[i][1]);
			fscanf(enterpriseFile, "%s", buff);
			sscanf(buff, "%f", &vertexes[i][2]);
			i++;
		}

		else {
			fscanf(enterpriseFile, "%s", buff);
			sscanf(buff, "%d", &enterprisePolygon[j][0]);
			fscanf(enterpriseFile, "%s", buff);
			sscanf(buff, "%d", &enterprisePolygon[j][1]);
			fscanf(enterpriseFile, "%s", buff);
			sscanf(buff, "%d", &enterprisePolygon[j][2]);
			j++;
		}
	}

	fclose(enterpriseFile);
}

/************************************************************************

Function:				
								initialiseGL

Description:	
								initialises openGL, and I am using a slightly blue
								background because I think it looks better than pure
								black does

*************************************************************************/
void initialiseGL(void)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0.05, 1.0); //background to be sliiiightly blue

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 0.01, 300);
	glMatrixMode(GL_MODELVIEW);
	glPointSize(1.0); //star size, i want them to be small because i have 5000 stars
}

/************************************************************************

Function:		
								main

Description:	
								rendering and window setup, and the main loop.
								i call buildEnterprise in here as well.

*************************************************************************/
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("The Hitch Hiker's Guide to the Planets | Olivia Handspiker");

	glutDisplayFunc(myDisplay);
	glutIdleFunc(myIdle);
	glutKeyboardFunc(letterKeys);
	glutSpecialFunc(specialKeys);

	initialiseGL();

	/*star generation, this makes them in random locations but static*/
	for (int i = 0; i < TOTAL_STARS; i++) {
		do {
			stars[i][0] = RANDOM;
			stars[i][1] = RANDOM;
			stars[i][2] = RANDOM;
		} while (sqrtf(pow(stars[i][0], 2) + pow(stars[i][1], 2) + pow(stars[i][2], 2)) <= SOLARSYSTEM_AREA);
	}

	buildEnterprise();
	keyboardWriter();
	glutMainLoop();
}