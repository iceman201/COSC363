//  ========================================================================
//  COSC363: Computer Graphics (2014);  University of Canterbury.
//
//  FILE NAME: Teapot.cpp
//  See Lab01.pdf for details
//  ========================================================================

#include <iostream>
#include <cmath>
#include <GL/glut.h>
using namespace std;
float theta = 0.0;
int cam_hgt = 0;


void special(int key, int x, int y)
{
	if (key == GLUT_KEY_F1){
		glClear(GL_COLOR_BUFFER_BIT);
	}
	else if(key == GLUT_KEY_F2){
		glutFullScreen();
	}
	else if(key == GLUT_KEY_UP){
		cam_hgt++;
	}
	else if(key == GLUT_KEY_DOWN){
		cam_hgt--;
	}
	else if(key == GLUT_KEY_LEFT){
		theta--;
	}
	else if(key == GLUT_KEY_RIGHT){
		theta++;
	}
	
	glutPostRedisplay();
}


void myTimer(int value)
{
	glutPostRedisplay();
	theta ++;
	glutTimerFunc(50, myTimer, 0);
}

//--Draws a grid of lines on the floor plane -------------------------------
void drawFloor()
{
	glDisable(GL_LIGHTING);			//Disable lighting when drawing floor.

	glColor3f(0.1, 0.5, 0.1);			//Floor colour

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
void display(void) 
{ 
	float lpos[4]={0., 10., 10., 1.0};  //light's position

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//gluLookAt(1, 1, 1, 0.0, 0, 1, 0, 1, 0);
    gluLookAt(12*sin(theta*(2*M_PI*1/360)),cam_hgt,12*cos(theta*((2*M_PI)*(1/360))),0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  //Camera position and orientation

	glLightfv(GL_LIGHT0,GL_POSITION, lpos);   //Set light position

    drawFloor();

	glEnable(GL_LIGHTING);			//Enable lighting for the teapot
    glColor3f(0.0, 1.0, 1.0);
    glTranslated(0., 0.8, 0.0);		//Move the teapot up by 0.8 units
    
    //glScalef(1, 1, -1);
    
	//glutSolidCube(1.0);
	//glRotatef(30.0, 0.0, 1.0, 0.0);
    glutSolidTeapot(1.0);           // size of Teapot

	glFlush(); 
} 

//----------------------------------------------------------------------
void initialize(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_LIGHTING);		//Enable OpenGL states
	glEnable(GL_LIGHT0);
 	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 10.0, 1000.0);   //Camera Frustum
}


//  ------- Main: Initialize glut window and register call backs -------
int main(int argc, char **argv) 
{ 
	glutInit(&argc, argv);
	     
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);  
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Teapot");
	initialize();

	glutSpecialFunc(special);
	//glutTimerFunc(10, myTimer, 0);

	glutDisplayFunc(display);
	glutMainLoop();
	return 0; 
}

