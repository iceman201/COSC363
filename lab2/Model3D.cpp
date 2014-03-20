//  ========================================================================
//  COSC363: Computer Graphics (2014);  University of Canterbury.
//
//  FILE NAME: Model3D.cpp
//  See Lab02.pdf for details
//
//  Program to load a model in OFF format.
//  Assumptions: 
//      1.  The model consists of triangles only.
//      2.  The OFF file does not contain comment lines.
//  ========================================================================
 
#include <iostream>
#include <fstream>
#include <climits>
#include <math.h> 
#include <GL/glut.h>
using namespace std;

//--Globals ---------------------------------------------------------------
float *x, *y, *z;  //vertex coordinate arrays
int *t1, *t2, *t3; //triangles
int nvrt, ntri;    //total number of vertices and triangles
float cam_hgt = 1; //Camera height
float angle = 10.0;  //Rotation angle for viewing
float xmin, xmax, ymin, ymax; //Min, max values of the object coordinates

//-- Loads mesh data in OFF format    -------------------------------------
void loadMeshFile(string fname)  
{
	ifstream fp_in;
	int num, ne;

	fp_in.open(fname.c_str(), ios::in);
	if(!fp_in.is_open())
	{
		cout << "Error opening mesh file" << endl;
		exit(1);
	}

	fp_in.ignore(INT_MAX, '\n');				//ignore first line
	fp_in >> nvrt >> ntri >> ne;			    // Read No. of vertices, polygons, edges

    x = new float[nvrt];                        //Create arrays
    y = new float[nvrt];
    z = new float[nvrt];

    t1 = new int[ntri];
    t2 = new int[ntri];
    t3 = new int[ntri];

	for(int i=0; i < nvrt; i++)                         //Read vertex list 
		fp_in >> x[i] >> y[i] >> z[i];

	for(int i=0; i < ntri; i++)                         //Read polygon list 
	{
		fp_in >> num >> t1[i] >> t2[i] >> t3[i];
		if(num != 3)
		{
			cout << "ERROR: Polygon with index " << i  << " is not a triangle." << endl;  //Not a triangle!!
			exit(1);
		}
	}

	fp_in.close();
	cout << " File successfully read." << endl;
}

//-- Computes the min, max values of coordinates  -----------------------
void computeMinMax()
{
	xmin = xmax = x[0];
	ymin = ymax = y[0];
	for(int i = 1; i < nvrt; i++)
	{
		if(x[i] < xmin) xmin = x[i];
		else if(x[i] > xmax) xmax = x[i];
		if(y[i] < ymin) ymin = y[i];
		else if(y[i] > ymax) ymax = y[i];
	}
}

//--Function to compute the normal vector of a triangle -------------------
void normal(float x, float y, float z)
{
	float nx, ny, nz;
	nx = x; 
	ny = y;
	nz = z;
	glNormal3f(nx, ny, nz);
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
	gluLookAt(0, cam_hgt, 10, 0, 0, 0, 0, 1, 0);
	glLightfv(GL_LIGHT0,GL_POSITION, lpos);   //Set light position

    glRotatef(angle, 0.0, 1.0, 0.0);  //Rotate the model about the y-axis

	glColor3f(0., 0. ,1.); 

    //Construct the object model using GL primitives
	glBegin(GL_TRIANGLES);
		for(int i=0; i<ntri; i++)
		{
		   normal(x[t1[i]], y[t1[i]], z[t1[i]]);
		   glVertex3d(x[t1[i]], y[t1[i]], z[t1[i]]);
		   glVertex3d(x[t2[i]], y[t2[i]], z[t2[i]]);
		   glVertex3d(x[t3[i]], y[t3[i]], z[t3[i]]);
		}
	glEnd();

	glFlush();
}

//------- Initialize OpenGL parameters -----------------------------------
void initialize()
{
	float model_wid, model_hgt;
    loadMeshFile("Octahedron.off");			//Specify mesh file name here
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	//Background colour

	glEnable(GL_LIGHTING);					//Enable OpenGL states
	glEnable(GL_LIGHT0);
 	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  //GL_LINE = Wireframe;   GL_FILL = Solid

	computeMinMax();						    //Compute min, max values of x, y coordinates for defining camera frustum
	model_wid = xmax-xmin;						//Model width and height
	model_hgt = ymax-ymin;
	xmin -= 0.2*model_wid;						//Extend minmax window further by 20% of its size.
	xmax += 0.2*model_wid;
	ymin -= 0.2*model_hgt;
	ymax += 0.2*model_hgt; 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xmin, xmax, ymin, ymax, 0, 1000);  //The orthogoraphic camera view volume  
}

//------------ Special key event callback ---------------------------------
// To enable the use of left and right arrow keys to rotate the object
void special(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT) angle--;
    else if(key == GLUT_KEY_RIGHT) angle++;
    glutPostRedisplay();
}

//  ------- Main: Initialize glut window and register call backs -----------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB| GLUT_DEPTH);
   glutInitWindowSize (600, 600); 
   glutInitWindowPosition (10, 10);
   glutCreateWindow ("Model3D");
   initialize();

   glutDisplayFunc(display);
   glutSpecialFunc(special); 
   glutMainLoop();
   return 0;
}
