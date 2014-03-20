//  ========================================================================
//  COSC363: Computer Graphics (2013);  University of Canterbury.
//
//  FILE NAME: Rail.cpp
//  See Lab03.pdf for details.
//  ========================================================================

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

GLUquadric *q;

//-- Ground Plane --------------------------------------------------------
void floor()
{
  glColor4f(0.5, 0.5, 0.5, 1.0);
  glNormal3f(0.0, 1.0, 0.0);
  glBegin(GL_QUADS);
  for(int i = -200; i < 200; i++)
  {
	  for(int j = -200;  j < 200; j++)
	  {
		glVertex3i(i, 0.0, j);
		glVertex3i(i, 0.0, j+1);
		glNormal3f(i+1, 0.0, j+1);
        glVertex3f(i+1, 0.0, j+1);
		glNormal3f(i+1, 0.0, j);
        glVertex3f(i+1, 0.0, j);
	  }
  }
  glEnd();
}

//------- Rail Track ----------------------------------------------------
void track(float r)
{
	float ang1, ang2, ca1, sa1, ca2, sa2;
	float x1, z1, x2, z2, x3, z3, x4, z4;
    float radians = 3.141592/180.0;

    glBegin(GL_QUADS);
	for(int i = 0; i < 360; i += 5)
	{
		ang1=i*radians;
		ang2=(i+5)*radians;
		ca1=cos(ang1); ca2=cos(ang2);
		sa1=sin(ang1); sa2=sin(ang2);
		x1=(r-0.5)*sa1; z1=(r-0.5)*ca1; 
		x2=(r+0.5)*sa1; z2=(r+0.5)*ca1;
		x3=(r+0.5)*sa2; z3=(r+0.5)*ca2;
		x4=(r-0.5)*sa2; z4=(r-0.5)*ca2;
		glNormal3f(0.,1.,0.);
		glVertex3f(x1,1.0,z1);
		glVertex3f(x2,1.0,z2);
		glVertex3f(x3,1.0,z3);
		glVertex3f(x4,1.0,z4);
		glNormal3f(-sa1,0.0,-ca1);
		glVertex3f(x1,0.0,z1);
		glVertex3f(x1,1.0,z1);
		glNormal3f(-sa2,0.0,-ca2);
		glVertex3f(x4,1.0,z4);
		glVertex3f(x4,0.0,z4);
		glNormal3f(sa1,0.0,ca1);
		glVertex3f(x2,1.0,z2);
		glVertex3f(x2,0.0,z2);
		glNormal3f(sa2,0.0,ca2);
		glVertex3f(x3,0.0,z3);
		glVertex3f(x3,1.0,z3);
	}
	glEnd();
}
//-------- Tracks  ----------------------------------------------------
void tracks()
{
	glColor4f(0.0, 0.0, 0.3, 1.0);
	track(115.0);   //Inner track has radius 115
	track(125.0);   //Outer track has radius 125
}

//------- Base (including wheels) of engine, wagons  --------------------
void base()
{
    glColor4f(0.2, 0.2, 0.2, 1.0);
    glPushMatrix();
      glTranslatef(0.0, 4.0, 0.0);
      glScalef(20.0, 2.0, 10.0);
      glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(11.0, 4.0, 0.0);
      glutSolidCube(2.0);
    glPopMatrix();

    //Wheels
    glColor4f(0.5, 0., 0., 1.0);
    glPushMatrix();
      glTranslatef(-8.0, 2.0, 5.1);
      gluDisk(q, 0.0, 2.0, 20, 2);
    glPopMatrix();
    glPushMatrix();
      glTranslatef(8.0, 2.0, 5.1);
      gluDisk(q, 0.0, 2.0, 20, 2);
    glPopMatrix();
    glPushMatrix();
      glTranslatef(-8.0, 2.0, -5.1);
      glRotatef(180.0, 0., 1., 0.);
      gluDisk(q, 0.0, 2.0, 20, 2);
    glPopMatrix();
    glPushMatrix();
      glTranslatef(8.0, 2.0, -5.1);
      glRotatef(180.0, 0., 1., 0.);
      gluDisk(q, 0.0, 2.0, 20, 2);
    glPopMatrix();
}

//-- Locomotive ------------------------------------------------
void engine()
{
    base();

    //Cab
    glColor4f(0.8, 0.8, 0.0, 1.0);
    glPushMatrix();
      glTranslatef(7.0, 8.5, 0.0);
      glScalef(6.0, 7.0, 10.0);
      glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(6.0, 14.0, 0.0);
      glScalef(4.0, 4.0, 8.0);
      glutSolidCube(1.0);
    glPopMatrix();

    //Boiler
    glPushMatrix();
      glColor4f(0.5, 0., 0., 1.0);
      glTranslatef(4.0, 10.0, 0.0);
      glRotatef(-90.0, 0., 1., 0.);
      gluCylinder(q, 5.0, 5.0, 14.0, 20, 5);
      glTranslatef(0.0, 0.0, 14.0);
      gluDisk(q, 0.0, 5.0, 20, 3);
      glColor4f(1.0, 1.0, 0.0, 1.0);
      glTranslatef(0.0, 4.0, 0.2);
      gluDisk(q, 0.0, 1.0, 20,2);  //headlight!
    glPopMatrix();

}

//--- A rail wagon ---------------------------------------------------
void wagon()
{
    base();

    glColor4f(0.0, 1.0, 1.0, 1.0);
    glPushMatrix();
      glTranslatef(0.0, 10.0, 0.0);
      glScalef(18.0, 10.0, 10.0);
      glutSolidCube(1.0);
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

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glColor4f(0., 0., 1., 1.);
    
}
float lgt_pos[3] = {0,50,0};
float wagon_theta = 0;
//-------------------------------------------------------------------
void display(void)
{

    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
        
    gluLookAt (0, 100, 100, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);       //Light's position
    floor();
    tracks();  
    
    glPushMatrix();
    glRotatef(-wagon_theta,0,1,0);
    glTranslatef(0, 1.0, -120.0);
    engine();
    glPopMatrix();          
    
    glPushMatrix();
    glRotatef(-wagon_theta-10.5,0,1,0);
    glTranslatef(0, 1.0, -120.0);
    wagon();
    glPopMatrix();

    glPushMatrix();
    glRotatef(-wagon_theta-10.5*2,0,1,0);
    glTranslatef(0, 1.0, -120.0);
    wagon();
    glPopMatrix();

    glPushMatrix();
    glRotatef(-wagon_theta-10.5*3,0,1,0);
    glTranslatef(0, 1.0, -120.0);
    wagon();
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(-wagon_theta-10.5*4,0,1,0);
    glTranslatef(0, 1.0, -120.0);
    wagon();
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(-wagon_theta-10.5*5,0,1,0);
    glTranslatef(0, 1.0, -120.0);
    wagon();
    glPopMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);
    glutSwapBuffers();
}

void timer(int time)
{
	glutPostRedisplay();
    
    wagon_theta--;
    
	glutTimerFunc(20, timer, 0);
}
//---------------------------------------------------------------------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
   glutInitWindowSize (600, 600); 
   glutInitWindowPosition (50, 50);
   glutCreateWindow (argv[0]);
   initialize ();
   glutTimerFunc(20, timer, 0);
   glutDisplayFunc(display); 

   glutMainLoop();
   return 0;
}
