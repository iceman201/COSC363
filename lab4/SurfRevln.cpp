//  ========================================================================
//  COSC363: Computer Graphics (2014);  University of Canterbury.
//
//  FILE NAME: SurfRevln.cpp
//  See Lab04.pdf for details.
//  ========================================================================
 
#include <iostream>
#include <fstream>
#include <cmath> 
#include <GL/glut.h>
using namespace std;

float vx[35], vy[35], vz[35];   //Vertex list
float wx[35], wy[35], wz[35];   //Array for storing transformed vertices

int nvrt;
float rot_x = 0.0,  rot_y = 0.0;  //Rotation angles;

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
//-------------------------------------------------------------------
void initialise(void) 
{
	ifstream file_in;
	file_in.open("Wineglass.dat", ios::in);      //Specify mesh file name here
	if(!file_in.is_open())
	{
		cout << "Error opening data file" << endl;
		exit(1);
	}

	file_in >> nvrt ;			    // Number of vertices on the base polygon

	for(int i=0; i < nvrt; i++)
    {
        file_in >> vx[i] >> vy[i] ;    //Read Vertex List
        vz[i] = 0.0;
    }

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
}

//-------------------------------------------------------------------
void display(void)
{
	float lgt_pos[4] = {0,50,0,1};
	glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 0., 5.0, 0., 0., 0., 0., 1., 0.);
	glLightfv(GL_LIGHT1,GL_POSITION, lgt_pos); 
	glColor3f (.0, 1.0,1.0);  
	glRotatef(rot_x,1,0,0);
	glRotatef(rot_y,0,1,0);
	double degree_radian = 0.174532925;

	//--A--
	for (int o=0; o<36; o++){
		
		for (int i = 0; i <=35; i++){
			wx[i] = vx[i]*cos(degree_radian) + vz[i]*sin(degree_radian);
			wy[i] = vy[i];
			wz[i] = -vx[i]*sin(degree_radian) + vz[i]*cos(degree_radian);
		}
		glBegin(GL_QUADS);
		for(int i = 0; i < 34; i++)
		{	
			//normal(vx[i],vy[i],vx[i],vx[i+1],vy[i+1],vz[i+1],wx[i+1],wy[i+1],wz[i+1]);
			glNormal3f(vx[i], vy[i], vz[i]);
			glVertex3f(vx[i], vy[i], vz[i]);
			glNormal3f(vx[i+1], vy[i+1], vz[i+1]);
			glVertex3f(vx[i+1], vy[i+1], vz[i+1]);
			glNormal3f(wx[i+1],wy[i+1],wz[i+1]);
			glVertex3f(wx[i+1],wy[i+1],wz[i+1]);
			glNormal3f(wx[i],wy[i],wz[i]);
			glVertex3f(wx[i],wy[i],wz[i]);
		}
		glEnd();
		for(int i= 0; i < 35; i++){
			vx[i] = wx[i];
			vy[i] = wy[i];
			vz[i] = wz[i];
		}
	}
	//-----
   glFlush();
}


//------------------------------------------------------------------
void special(int key, int x, int y)
{
	if(key == GLUT_KEY_DOWN) rot_x += 5;
	else if(key == GLUT_KEY_UP) rot_x -= 5;
	else if(key == GLUT_KEY_LEFT) rot_y -= 5;
	else if(key == GLUT_KEY_RIGHT) rot_y += 5;
	glutPostRedisplay();
}

//-------------------------------------------------------------------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE| GLUT_RGB |GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Surface of Revolution");
   initialise ();
   glutDisplayFunc(display); 
   glutSpecialFunc(special);
   glutMainLoop();
   return 0;
}
