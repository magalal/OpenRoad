#include <iostream>
#include <stdio.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glut.h>
#include <vector>
#include <cmath>

#include "Sleep.h"
#include "ObjLibrary/ObjModel.h"
#include "ObjLibrary/TextureManager.h"
#include "ObjLibrary/TextureBmp.h"
#include "GetGlut.h"

#define KEY_ESCAPE 27

using namespace std;

void init();
void initDisplay();
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);
void update();
void display();
void drawQuad(int x, int y);
void moveObject(ObjModel x, int xmin, int xmax, int z, int rate);

ObjModel mountain;
ObjModel building;
ObjModel charchater1;
ObjModel car1;

int main(int argc, char* argv[])
{
	glutInitWindowSize(700, 500);
	glutInitWindowPosition(0, 0);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutCreateWindow("Crossy Road");
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutIdleFunc(update);
	glutDisplayFunc(display);

	init();

	glutMainLoop();

	return 1;
}

void init()
{
	initDisplay();

	mountain.load("mountain/lowpolymountains.obj");
	building.load("Building1.obj");
	charchater1.load("chr_old.obj");
	car1.load("car1.obj");
}

void initDisplay()
{
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glColor3f(0.0, 0.0, 0.0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // on [ESC]
		exit(0); // normal exit
		break;
	}
}

void reshape(int w, int h)
{
	glViewport (0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLdouble)w / (GLdouble)h, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);

	glutPostRedisplay();
}

void update()
{
	//update your variables here

	sleep(1.0 / 60.0);
	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(5.0f, 10.0f, 30.0f,
	          0.0, 0.0, 0.0,
	          0.0, 1.0, 0.0);

   	glPushMatrix();
        glTranslatef(-20.0f, 0.0f, -12.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f,0.0f,0.0f);
        //glScalef(2.0f, 3.0f, 1.0f);
        mountain.draw();
    glPopMatrix();


	glPushMatrix();
        glTranslatef(-20.0f, 0.0f, 7.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f,0.0f,0.0f);
        //glScalef(2.0f, 3.0f, 1.0f);
        mountain.draw();
    glPopMatrix();

	glPushMatrix();
        glTranslatef(0.0f, 0.0f, 10.0f);
		//glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
		//glColor3f(0.0f,0.0f,0.0f);
        glScalef(0.05f, 0.05f, 0.05f);
        building.draw();
    glPopMatrix();

	glPushMatrix();
        glTranslatef(5.0f, 0.0f, 20.0f);
		//glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
		//glColor3f(0.0f,0.0f,0.0f);
        glScalef(0.05f, 0.05f, 0.05f);
        car1.draw();
    glPopMatrix();
	glPushMatrix();
        glTranslatef(-5.0f, 0.0f, 20.0f);
		//glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
		//glColor3f(0.0f,0.0f,0.0f);
        glScalef(0.09f, 0.09f, 0.09f);
        charchater1.draw();
    glPopMatrix();
	
	
	
	glutSwapBuffers();
}
void moveObject(ObjModel x, int xmin, int xmax, int z, int rate)
{

	
		// here i am setting the initial object z to put it into the proper street 
		glPushMatrix();
        glTranslatef(0.0f, 0.0f, (float)z);
		x.draw();
		glPopMatrix();
		// the formula xmax - xmin/ rate is  used such that the rate is the no. of steps taken by the object and this formula define 
		// each how much diffrence in x is taken in each object for example xmin = 10 xmax =20 and rate is 50 so 20-10/50=0.2 
		// that is the value of each step 
	for (int i=xmin;i<xmax;i+=((xmax-xmin)/rate))
	
	{
		glPushMatrix();
        glTranslatef(float (i), 0.0f, 0.0f);
		//glScalef(0.09f, 0.09f, 0.09f);
        x.draw();
		glPopMatrix();
	}
}