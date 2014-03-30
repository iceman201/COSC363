//===================================================================
//  COSC363 Computer Graphics (2014). University of Canterbury.
//
//  Tower.cpp
//  See Lab04.pdf for details
//===================================================================

#include <cmath>
#include <GL/glut.h>
using namespace std;

float viewAngle = 0.0;
const float CDR = 3.14159265/180.0;  //Degrees to radians
const int N = 18;   //Number of vertices of the base polygon

//-------------------------------------------------------------------
void normal(float x1, float y1, float z1,
            float x2, float y2, float z2,
            float x3, float y3, float z3 )
{
    float nx, ny, nz;
    nx = y1*(z2-z3)+ y2*(z3-z1)+ y3*(z1-z2);
    ny = z1*(x2-x3)+ z2*(x3-x1)+ z3*(x1-x2);
    nz = x1*(y2-y3)+ x2*(y3-y1)+ x3*(y1-y2);
    glNormal3f(nx, ny, nz);
}

//------------------------------------------------------------------ 
void display(void) 
{ 
	float lpos[4]={-100.,100., 0., 1.};
	float ex, ez;
    float vx[N] = {0., 8., 11., 11., 10.4, 9.5, 8., 6., 3., 0., -3., -6., -8., -9.5, -10.4, -11., -11., -8.};
    float vy[N] = {0};
    float vz[N] = {19.4, 8., 5., 0., -4., -8., -11., -12., -12.4, -12.5, -12.4, -12., -11., -8., -4., 0., 5., 8.};
    float wx[N], wy[N], wz[N];
	
    
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	ex = 150.0*sin(viewAngle*CDR);   //Camera position
	ez = 150.0*cos(viewAngle*CDR);

	gluLookAt(ex, 100.0, ez, 0.0, 100.0, 0.0, 0.0, 1.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	
    glColor3f(0., 1., 1.);
    
// ==== Remove the following 5 lines of code and replace with a 3D model! ====
	glNormal3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
		for(int i = 0; i < N; i++)
		     glVertex3f(vx[i], vy[i], vz[i]);
	glEnd();
// =================================================================

	glFlush(); 
} 

//-------------------------------------------------------------------
void special(int key, int xp, int yp)
{
	if(key==GLUT_KEY_LEFT)
		viewAngle += 5.0;
	else if(key==GLUT_KEY_RIGHT)
		viewAngle -= 5.0;
	glutPostRedisplay();
}

//-------------------------------------------------------------------
void initialise(void)
{
	float white[4] = {1., 1., 1., 1.};

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(0.,0.,0.);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, 1.0, 40.0, 1000.);;

}

//------------------------------------------------------------------- 
int main(int argc, char **argv) 
{ 
	glutInit(&argc, argv);            
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);  
	glutInitWindowSize(600,600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("The Turning Torso");
	initialise();
	glutDisplayFunc(display); 
	glutSpecialFunc(special);
	glutMainLoop();
	return 0;
}

