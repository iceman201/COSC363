/*******************************************
 * COSC 363
 * Cylinder mode
 * Liguo Jiao
 * Student ID : 91734390
/----------------------------------------*/

#include "Box.h"

#include <math.h>

float Box::intersect(Vector pos, Vector dir)
{
//    Vector n = normal(pos); 
    //Vector vdif = Vector(pos.x, 0, pos.y) - Vector(center.x, 0, center.y);
    
    float a = (dir.x * dir.x) + (dir.z * dir.z);
    float b = 2*(dir.x*(pos.x-center.x) + dir.z*(pos.z-center.z));
    float c = (pos.x - center.x) * (pos.x - center.x) + (pos.z - center.z) * (pos.z - center.z);
    
    float delta = b*b - 4*(a*c);
      
	if(fabs(delta) < 0.001) return -1.0; 
    if(delta < 0.0) return -1.0;
    
    float t1 = (-b - sqrt(delta))/(2*a);
    float t2 = (-b + sqrt(delta))/(2*a);
    
    float t;
    
    if (t1 > t2) t = t2;
    else t = t1;
    float r = pos.y + t*dir.y;
    
    if ((r > center.y - height) and (r < height)){
        return t;
    }
    else return -1;
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
