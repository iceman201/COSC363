#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <fstream>
#include "loadTGA.h"

GLUquadric *q;
using namespace std;
GLuint txId[2];   //Texture ids

int fire = 0;
int fly = 0;
int check = 0;
float theta = 0.0;
float angle_left_right = 0.0;
float angle_up_down = 1.0;
int cam_hgt = 150;

void special(int key, int x, int y)
{
	if(key == GLUT_KEY_UP){
		angle_up_down++;
	}
	else if(key == GLUT_KEY_DOWN){
		angle_up_down--;
	}
    else if(key == GLUT_KEY_RIGHT){
		angle_left_right--;
	}
	else if(key == GLUT_KEY_LEFT){
		angle_left_right++;
	}
	glutPostRedisplay();
}

void key(unsigned char key, int x, int y)
{
    if (key == 'c'){
        fire = 1;
    }
    else if (key == 's'){
        fly = 1;
    }
	else if (key == 'z'){
        cam_hgt--;
    }
    else if (key == 'x'){
        cam_hgt++;
    }
    glutPostRedisplay();
}

//--------------------------------------------------------------------------------
void loadTexture()				
{
	glGenTextures(2, txId); 	// Create 2 texture ids

	glBindTexture(GL_TEXTURE_2D, txId[0]);  //Use this texture
    loadTGA("Wall.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	

	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
}

//-- Ground Plane --------------------------------------------------------
void floor()
{
    glColor4f(0.5, 0.35, 0.05, 1.0);
    glNormal3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    for(int i = -200; i < 200; i++)
    {
        for(int j = -200;  j < 200; j++)
        {
            glVertex3f(i, 0.0, j);
            glVertex3f(i, 0.0, j+1);
            glVertex3f(i+1, 0.0, j+1);
            glVertex3f(i+1, 0.0, j);
            
        }
    }
    glEnd();
}
void cave()
{
    glPushMatrix();
        glColor4f(0.5, 0.5, 0.5, 1.0);
        glTranslatef(0,5,0);
        glScalef(5, 5, 5);
        glutSolidCube(1.1);
    glPopMatrix();
}
void wall()
{
    //glColor3f(0., 0. ,1.);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txId[0]);
    glPushMatrix();
	glBegin(GL_QUADS);
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 80; j++){
            glVertex3i(i, 50.0, j);      //Top
            glVertex3i(i, 50.0, j+1);
            glVertex3f(i+1, 50.0, j+1);
            glVertex3f(i+1, 50.0, j);
            
        }
    }
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 50; j++){
            glVertex3f(i, j, 0.0);      //front
            glVertex3f(i, j+1, 0.0);
            glVertex3f(i+1, j+1, 0.0);
            glVertex3f(i+1, j, 0.0);
            
            glVertex3f(i, j, 80.0);      //back
            glVertex3f(i, j+1, 80.0);
            glVertex3f(i+1, j+1, 80.0);
            glVertex3f(i+1, j, 80.0);
        }
    }
    for (int j = 0; j < 50; j++)
    {
         for (int o = 0; o < 80; o++){
             
            glTexCoord2f(0.0,0.0);
            glVertex3f(0.0, j, o);      //left side
            
            glTexCoord2f(0.0,1.0);
            glVertex3f(0.0, j, o+1);
            
            glTexCoord2f(1.0,0.0);
            glVertex3f(0.0,j+1, o+1);
            
            glTexCoord2f(1.0,1.0);
            glVertex3f(0.0,j+1, o);
            
            glVertex3f(20.0, j, o);     //right side
            glVertex3f(20.0, j, o+1);
            glVertex3f(20.0,j+1, o+1);
            glVertex3f(20.0,j+1, o);
        }
    }
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(17,48,25);
        cave();
        glTranslatef(-14.3,0,0);
        cave();
        glTranslatef(0,0,20);
        cave();
        glTranslatef(14.3,0,0);
        cave();
        glTranslatef(0,0,20);
        cave();
        glTranslatef(-14.3,0,0);
        cave();
    glPopMatrix();
}
void castle_strut()
{
    glPushMatrix();
        glColor3f(10., 0., 0.);
        glTranslatef(45,50,-115);
        glRotatef(90,1,0,0);
        GLUquadric *q = gluNewQuadric();
        gluCylinder(q,10,10,50.,30.,30);
        glColor4f(1., 1., 0., 0.);
        glRotatef(180,1,0,0);
        glScalef(5, 5, 20);
        glutSolidCone(2,1,50,5);
        gluQuadricDrawStyle(q, GLU_FILL);
    glPopMatrix();
}
//--- A castle ---------------------------------------------------
void castle()
{
	glPushMatrix();
        glColor3f(0., 0. ,1.);
        glTranslatef(-30, 25.5, 0);
        glRotatef(0, 1, 0, 0);//two post distance
        glScalef(20, 50, 20);
        glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
        glColor3f(0., 1. ,0.);
        glTranslatef(-30, 50, 0);    //left post heave
        glRotatef(-90,1,0,0);
        glScalef(5, 5, 20);
        glutSolidCone(1.7,1,50,5);
	glPopMatrix();

	glPushMatrix();
        glColor3f(0., 1. ,0.);
        glTranslatef(30, 50, 0);    //left post cave
        glRotatef(-90,1,0,0);
        glScalef(5, 5, 20);
        glutSolidCone(1.7,1,50,5);
	glPopMatrix();
        
	glPushMatrix();
       	glColor3f(0., 0. ,1.);
        glTranslatef(30, 25.5, 0);
        glRotatef(0, 1, 0, 0); //two post distance
        glScalef(20, 50, 20);
        glutSolidCube(1);
	glPopMatrix();

    glPushMatrix();
        glColor3f(0.,0.,1.);
        glTranslatef(0,38,0);
        glRotatef(0,1,0,0);  //two post distance
        glScalef(60, 15, 20);
        glutSolidCube(1);    
    glPopMatrix();
    
    glPushMatrix();  
        glTranslatef(40,0,10);
        glRotatef(135,0,1,0);
        wall(); //right_down
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(111,0,-61);
        glRotatef(-135,0,1,0);
        wall(); //right_up
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(41, 0, -125);
        glRotatef(270,0,1,0);
        wall();
    glPopMatrix();
    
    glPushMatrix();
        castle_strut();
        glTranslatef(-90,0,-1);
        castle_strut();
    glPopMatrix();
    
    glPushMatrix();  
        glTranslatef(-25,0,-5);
        glRotatef(-135,0,1,0);
        wall(); //left_down
    glPopMatrix();
    
    glPushMatrix();  
        glTranslatef(-53,0,-118);
        glRotatef(-45,0,1,0);
        wall(); //left_up
    glPopMatrix();    
    
}

void spaceship()
{
    GLdouble eqn [4]={0.0,1.0,0.0,0.0}; 

    glPushMatrix();             //engine
        glColor4f(1., 1., 1., 1.);
        glTranslatef(0,23,0);
        glClipPlane(GL_CLIP_PLANE0,eqn);
        glEnable(GL_CLIP_PLANE0);
        gluSphere(q, 5.3f, 32, 32);
        glDisable(GL_CLIP_PLANE0);
    glPopMatrix();
    
    glPushMatrix();         //body
        glColor4f(1., 1., 1., 1.);
        glTranslatef(0,15,0);
        glScalef(1,3.5,1);
        glutSolidCube(5.0);
    glPopMatrix();
    
    glPushMatrix();
        glColor4f(1., 0., 1., 1.);
        glTranslatef(0,15,3);
        glScalef(0.5,3.5,0.5);
        glutSolidCube(5.0);
    glPopMatrix();
    
    glPushMatrix();         //Right_wing
        glColor4f(1., 1., 1., 1.);
        glTranslatef(4.5,17,0);
        glRotatef(-45,0,0,1);
        glScalef(1.5,0.5,1);
        glutSolidCube(5.0);
    glPopMatrix();
    
    glPushMatrix();         //Right_wing
        glColor4f(1., 1., 1., 1.);
        glTranslatef(-4.5,17,0);
        glRotatef(45,0,0,1);
        glScalef(1.5,0.5,1);
        glutSolidCube(5.0);
    glPopMatrix();
    
    glPushMatrix();
        glColor4f(1., 0., 0., 0.);
        glTranslatef(0,7,0);
        glRotatef(90,1,0,0);
        GLUquadric *q = gluNewQuadric();
        gluCylinder(q,2.5,7.5,7.,30.,30);
        gluQuadricDrawStyle(q, GLU_FILL);
    glPopMatrix();
}

void robot(void)
{
   	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_LIGHTING);	

	glColor3f(1., 0.78 ,0.06);		//Head
	glPushMatrix();
	  glTranslatef(0, 7.7, 0);
	  glutSolidCube(1.4);
	glPopMatrix();
    
	glColor3f(1., 0.0 ,0.0);		//eye
	glPushMatrix();
	  glTranslatef(-0.3, 8, 1);
      glutSolidCube(.2);
	glPopMatrix();
    
	glPushMatrix();
      glTranslatef(0.3, 8, 1);
      glutSolidCube(.2);
	glPopMatrix();
    
    glPushMatrix();         //noise
      glTranslatef(0, 7.5, 1);
      glutSolidCube(.2);
	glPopMatrix();
    
    glPushMatrix();         //mouth
      glTranslatef(0, 7.2, 1);
      glScalef(3, .5, 1);
      glutSolidCube(.2);
	glPopMatrix();    
    
	glColor3f(1., 0. ,0.);			//Torso
	glPushMatrix();
	  glTranslatef(0, 5.5, 0);
	  glScalef(3, 3, 1.2);
	  glutSolidCube(1);
	glPopMatrix();
	
	glColor3f(0., 0. ,1.);			//Right leg
	glPushMatrix();
	  glTranslatef(0, 4.5, 0);
	  glRotatef(-theta, 1, 0, 0);
	  glTranslatef(-0.8, -2.5, 0);
	  glScalef(1, 4, 1);
	  glutSolidCube(1);
	glPopMatrix();
	
	glColor3f(0., 0. ,1.);          // Left leg
	glPushMatrix();
		glTranslatef(0, 4.5, 0);
		glRotatef(theta, 1, 0, 0);
		glTranslatef(0.8, -2.5, 0);
		glScalef(1, 4, 1);
		glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0. ,1.);			//Right arm
	glPushMatrix();
	  glTranslatef(-2, 5, 0);
	  glRotatef(-theta, 1, 0, 0);
      glScalef(1, 4, 1);
	  glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0. ,1.);			//Left arm
	glPushMatrix();
	  glTranslatef(2, 5, 0);
      glRotatef(-theta, 1, 0, 0);
	  glScalef(1, 4, 1);
	  glutSolidCube(1);
	glPopMatrix();

	glFlush();
}
void cannon(void)
{
    //Cab
    glColor4f(0., 0., 0.5, 0.0);
    glPushMatrix();
        glTranslatef(6.0, 3.0, 0.0);
        glScalef(8.0, 7.0, 10.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(6.0, 10.0, 0.0);
        glScalef(8.0, 8.0, 8.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor4f(1.5, 0., 1., 0.);
        glTranslatef(2.0, 10.0, 0.0);
        glRotatef(-90.0, 0., 1., 0.);
        gluCylinder(q, 5.0, 5.0, 14.0, 20, 5);
        glTranslatef(0.0, 0.0, 14.0);
        gluDisk(q, 0.0, 5.0, 20, 3);
    glPopMatrix();
    
}
//-- fire ball --------------------------------------------------------
void bullet(void){
    glPushMatrix();
        glColor4f(1.5, 0., 1., 0.);
        gluSphere(q, 1.3f, 32, 32);
    glPopMatrix();
}
//---------------------------------------------------------------------
void initialize(void) 
{
    float grey[4] = {0.2, 0.2, 0.2, 1.}; //light’s ambient color
    float white[4] = {1.0, 1.0, 1.0, 1.}; // diffuse and spec color
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    q = gluNewQuadric();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
    gluQuadricDrawStyle(q, GLU_FILL);
	glClearColor (0.0, 0.0, 0.0, 0.0);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60., 1.0, 10.0, 1000.0);   //Perspective projection
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, white); //Q5
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
	
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glColor4f(0., 0., 1., 1.);
    
}
int b_move = -5;

//-------------------------------------------------------------------
void display(void)
{

    float lgt_pos[4] = {0,50,0,1};
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt (0, 20, cam_hgt, .0, 1.0, 0.0, 0.0, 1.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);       //Light's position
    glRotatef(angle_left_right, 0.0, 1.0, 0.0);
    glRotatef(angle_up_down, 1.0, 0.0, 0.0);
    
    floor();
    castle();
    
    robot();
    glTranslatef(10, 0, 5);
    glRotatef(90,0,1,0);
    cannon();
    if (fire == 1){
        glPushMatrix();
            glTranslatef(b_move, 10.0, 0.0);
            bullet();
        glPopMatrix();
    }
    
    if (b_move == -10){
        fire = 0;
    }
    
    glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);
    glutSwapBuffers();
}

void timer(int time)
{
	glutPostRedisplay();
    b_move--;
	glutTimerFunc(10, timer, 0);
}

//~ void timer_robot(int time)
//~ {
	//~ glutPostRedisplay();
//~ 
	//~ if ((theta < 20) && (check == 0)){
		//~ theta ++;
	//~ }
	//~ if (theta == 20){
		//~ check = 1;
	//~ }
	//~ if (check == 1){
		//~ theta --;
	//~ }
	//~ if (theta == -20){
		//~ check = 0;
	//~ }
	//~ glutTimerFunc(20, timer, 0);
//~ }

//---------------------------------------------------------------------
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
    glutInitWindowSize (600, 600); 
    glutInitWindowPosition (50, 50);

    glutCreateWindow ("Made by Liguo Jiao");
    initialize ();

    glutTimerFunc(10, timer, 0);
//    glutTimerFunc(20, timer_robot, 0);
    
    glutSpecialFunc(special);
    glutKeyboardFunc(key);
    glutDisplayFunc(display); 

    glutMainLoop();
    return 0;
}
