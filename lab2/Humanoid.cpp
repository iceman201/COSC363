//  ========================================================================
//  COSC363: Computer Graphics (2014);  University of Canterbury.
//
//  FILE NAME: Humanoid.cpp
//  See Lab02.pdf for details
//  ========================================================================
 
#include <iostream>
#include <fstream>
#include <math.h> 
#include <GL/glut.h>
using namespace std;

//--Globals ---------------------------------------------------------------
float cam_hgt = 4; //Camera height
float angle = 10.0;  //Rotation angle for viewing
float theta = 0.0;
int check = 0;

//--Draws a grid of lines on the floor plane -------------------------------
void drawFloor()
{
	glDisable(GL_LIGHTING);			//Disable lighting when drawing floor.

	glColor3f(0., 0.5, 0.);			//Floor colour

	for(float i = -50; i <= 50; i ++)
	{
		glBegin(GL_LINES);			//A set of grid lines on the xz-plane
			glVertex3f(-50, 0, i);
			glVertex3f(50, 0, i);
			glVertex3f(i, 0, -50);
			glVertex3f(i, 0, 50);
		glEnd();
	}
}
//--Display: ---------------------------------------------------------------
//--This is the main display module containing function calls for generating
//--the scene.
void display()  
{
	float lpos[4]={10., 10., 10., 1.0};  //light's position

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, cam_hgt, 10, 0, 4, 0, 0, 1, 0);
	glLightfv(GL_LIGHT0,GL_POSITION, lpos);   //Set light position

    glRotatef(angle, 0.0, 1.0, 0.0);  //Rotate the model about the y-axis

    drawFloor();

	glEnable(GL_LIGHTING);	

	glColor3f(1., 0.78 ,0.06);		//Head
	glPushMatrix();
	  glTranslatef(0, 7.7, 0);
	  glutSolidCube(1.4);
	glPopMatrix();

	glColor3f(1., 0. ,0.);			//Torso
	glPushMatrix();
	  glTranslatef(0, 5.5, 0);
	  glScalef(3, 3, 1.2);
	  glutSolidCube(1);
	glPopMatrix();

//	glColor3f(0., 0. ,1.);			//Right leg
//	glPushMatrix();
//	  glTranslatef(-0.8, 2, 0);
//	  glScalef(1, 4, 1);
//	  glutSolidCube(1);
//	glPopMatrix();
	
	glColor3f(0., 0. ,1.);			//Right leg
	glPushMatrix();
	  glTranslatef(0, 4.5, 0);
	  glRotatef(-theta, 1, 0, 0);
	  glTranslatef(0, -4.5, 0);
	  glTranslatef(-0.8, 2, 0);
	  glScalef(1, 4, 1);
	  glutSolidCube(1);
	glPopMatrix();
	
	glColor3f(0., 0. ,1.);
	glPushMatrix();
		glTranslatef(0, 4.5, 0);
		glRotatef(theta, 1, 0, 0);
		glTranslatef(0, -4.5, 0);
		glTranslatef(0.8, 2, 0);
		glScalef(1, 4, 1);
		glutSolidCube(1);
	glPopMatrix();


//	glColor3f(0., 0. ,1.);			//Left leg
//	glPushMatrix();
//	  glTranslatef(0.8, 2, 0);
//	  glScalef(1, 4, 1);
//	  glutSolidCube(1);
//	glPopMatrix();

	glColor3f(0., 0. ,1.);			//Right arm
	glPushMatrix();
	  glTranslatef(-2, 5, 0);
	  glScalef(1, 4, 1);
	  glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0. ,1.);			//Left arm
	glPushMatrix();
	  glTranslatef(2, 5, 0);
	  glScalef(1, 4, 1);
	  glutSolidCube(1);
	glPopMatrix();

	glFlush();
}

//------- Initialize OpenGL parameters -----------------------------------
void initialize()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	//Background colour

	glEnable(GL_LIGHTING);					//Enable OpenGL states
	glEnable(GL_LIGHT0);
 	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 1000.0);   //Camera Frustum
}

//------------ Special key event callback ---------------------------------
// To enable the use of left and right arrow keys to rotate the object
void special(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT) angle--;
    else if(key == GLUT_KEY_RIGHT) angle++;
    glutPostRedisplay();
}

void timer(int time)
{
	glutPostRedisplay();

	if ((theta < 20) && (check == 0)){
		theta ++;
	}
	if (theta == 20){
		check = 1;
	}
	if (check == 1){
		theta --;
	}
	if (theta == -20){
		check = 0;
	}
	glutTimerFunc(20, timer, 0);
}

//  ------- Main: Initialize glut window and register call backs -----------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB| GLUT_DEPTH);
   glutInitWindowSize (600, 600); 
   glutInitWindowPosition (10, 10);
   glutCreateWindow ("Humanoid");
   initialize();
   glutTimerFunc(20, timer, 0);
   
   glutDisplayFunc(display);
   glutSpecialFunc(special); 
   glutMainLoop();
   return 0;
}
