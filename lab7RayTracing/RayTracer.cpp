// ========================================================================
// COSC 363  Computer Graphics  Lab07
// A simple ray tracer
// ========================================================================

#include <iostream>
#include <cmath>
#include "Plane.h"
#include <vector>
#include "Vector.h"
#include "Sphere.h"
#include "Color.h"
#include "Object.h"
#include <GL/glut.h>
using namespace std;

const float WIDTH = 20.0;  
const float HEIGHT = 20.0;
const float EDIST = 40.0;
const int PPU = 30;     //Total 600x600 pixels
const int MAX_STEPS = 5;
const float XMIN = -WIDTH * 0.5;
const float XMAX =  WIDTH * 0.5;
const float YMIN = -HEIGHT * 0.5;
const float YMAX =  HEIGHT * 0.5;

vector<Object*> sceneObjects;

Vector light = Vector(10.0, 40.0, -5.0);
Color backgroundCol = Color::GRAY;

//A useful struct
struct PointBundle   
{
	Vector point;
	int index;
	float dist;
};

/*
* This function compares the given ray with all objects in the scene
* and computes the closest point  of intersection.
*/
PointBundle closestPt(Vector pos, Vector dir)
{
    Vector  point(0, 0, 0);
	float min = 10000.0;

	PointBundle out = {point, -1, 0.0};

    for(int i = 0;  i < sceneObjects.size();  i++)
	{
        float t = sceneObjects[i]->intersect(pos, dir);
		if(t > 0)        //Intersects the object
		{
			point = pos + dir*t;
			if(t < min)
			{
				out.point = point;
				out.index = i;
				out.dist = t;
				min = t;
			}
		}
	}

	return out;
}

/*
* Computes the colour value obtained by tracing a ray.
* If reflections and refractions are to be included, then secondary rays will 
* have to be traced from the point, by converting this method to a recursive
* procedure.
*/

Color trace(Vector pos, Vector dir, int step)
{
    PointBundle q = closestPt(pos, dir);
    Color colorSum = Color(0.2f,0.2f,0.2f);
    if(q.index == -1) {
        return backgroundCol;        //no intersection
    }
    Vector n = sceneObjects[q.index]->normal(q.point);
    Vector l = light - q.point;
    l.normalise();
    float lDotn = l.dot(n);
    Color col = sceneObjects[q.index]->getColor(); //Object's colour
    
    if (l.dot(n) <= 0){
        colorSum = col.phongLight(backgroundCol,0.0,0.0);
    }
    else{
        Vector r = ((n * 2) * lDotn) - l; // r = 2(L.n)n – L. ‘l’ = el 
        r.normalise(); 
        Vector v(-dir.x, -dir.y, -dir.z); //View vector; 
        float rDotv = r.dot(v); 
        float spec; 
        float reflCoeff;
        if(rDotv < 0) spec = 0.0; 
        else spec = pow(rDotv, 10); //Phong exponent = 10
        
        PointBundle shadow = closestPt(q.point, l);
        Vector reflectionVector = ((n*2)*(n.dot(v)))-v;
        reflCoeff = 0.8;
        if (shadow.index == -1){
//            return col.phongLight(backgroundCol,lDotn,spec);
            colorSum = col.phongLight(backgroundCol,lDotn,spec);
            
        }
        if (q.index == 0 && step < MAX_STEPS){
                Color reflectionCol = trace(q.point,reflectionVector,step+1);
                colorSum.combineColor(reflectionCol,reflCoeff);
        }
        return colorSum;
    }
    //return col//
}

//---The main display module -----------------------------------------------------------
// In a ray tracing application, it just displays the ray traced image by drawing
// each pixel as quads.
//---------------------------------------------------------------------------------------
void display()
{
	int widthInPixels = (int)(WIDTH * PPU);
	int heightInPixels = (int)(HEIGHT * PPU);
	float pixelSize = 1.0/PPU;
	float halfPixelSize = pixelSize/2.0;
	float x1, y1, xc, yc;
	Vector eye(0., 0., 0.);

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);  //Each pixel is a quad.

	for(int i = 0; i < widthInPixels; i++)	//Scan every "pixel"
	{
		x1 = XMIN + i*pixelSize;
		xc = x1 + halfPixelSize;
		for(int j = 0; j < heightInPixels; j++)
		{
			y1 = YMIN + j*pixelSize;
			yc = y1 + halfPixelSize;

		    Vector dir(xc, yc, -EDIST);	//direction of the primary ray

		    dir.normalise();			//Normalise this direction

		    Color col = trace (eye, dir, 1); //Trace the primary ray and get the colour value
			glColor3f(col.r, col.g, col.b);
			glVertex2f(x1, y1);				//Draw each pixel with its color value
			glVertex2f(x1 + pixelSize, y1);
			glVertex2f(x1 + pixelSize, y1 + pixelSize);
			glVertex2f(x1, y1 + pixelSize);
        }
    }

    glEnd();
    glFlush();
}



void initialize()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(XMIN, XMAX, YMIN, YMAX);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0, 0, 0, 1);
    // New stuff adding down here //
    Sphere *sphere1 = new Sphere(Vector(7, -5, -70), 5.0, Color::RED);
    sceneObjects.push_back(sphere1);
    Sphere *sphere3 = new Sphere(Vector(0, 6, -170), 15.0, Color::BLUE);
    sceneObjects.push_back(sphere3);
    Sphere *sphere4 = new Sphere(Vector(8, 2, -50), 3.0, Color::GREEN);
    sceneObjects.push_back(sphere4);
    Sphere *sphere5 = new Sphere(Vector(9, 7, -50), 2.0, Color::BLACK);
    sceneObjects.push_back(sphere5);
    
    Plane *plane = new Plane(Vector(-10,-10,-40),Vector(10,-10,-40),Vector(10,-10,-80),Vector(-10,-10,-80), Color(0,1,1));
    sceneObjects.push_back(plane);
}

int main(int argc, char *argv[]) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Raytracing");

    glutDisplayFunc(display);
    initialize();

    glutMainLoop();
    return 0;
}
