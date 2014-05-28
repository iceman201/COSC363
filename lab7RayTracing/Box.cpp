/*******************************************
 * COSC 363
 * Cylinder mode
 * Liguo Jiao
 * Student ID : 91734390
/----------------------------------------*/

#include "Box.h"
#include "Vector.h"
#include <math.h>

float Box::intersect(Vector pos, Vector dir)
{

    if (((pos.y - center.y) >= 0) && ((pos.y - center.y) <= height)){
        Vector vdif = (pos.x - center.x) * (pos.x - center.x) + (pos.z - center.z) * (pos.z - center.z);
    }
    
    Vector n = normal(pos);    
    
    float len = vdif.length();
    float b = dir.x*(pos.x-center.x) + dir.z*(pos.z-center.z);
    
    float c = len*len - radius*radius;

   
	if(fabs(delta) < 0.001) return -1.0; 
    if(delta < 0.0) return -1.0;

    float t1 = -b - sqrt(delta);
    float t2 = -b + sqrt(delta);
    ////////////////////////////////
    if(fabs(t1) < 0.001)
    {
        if (t2 > 0) return t2;
        else t1 = -1.0;
    }
    if(fabs(t2) < 0.001 ) t2 = -1.0;
	return (t1 < t2)? t1: t2;
}

/**
* Returns the unit normal vector at a given point.
* Assumption: The input point p lies on the sphere.
*/
Vector Box::normal(Vector p)
{
    Vector n = p - center;
    n.normalise();
    return n;
}
