#ifndef H_BOX
#define H_BOX

#include "Object.h"

/**
 * Defines a simple Sphere located at 'center' 
 * with the specified radius
 */
class Box : public Object
{

private:
    Vector center;
    float radius;
    float height;
public:	
	Box()
		: center(Vector()), radius(1), height(1)  //Default constructor creates a unit sphere
	{
		color = Color::WHITE;
	};
	
    Box(Vector c, float r, float h, Color col)
		: center(c), radius(r), height(h)
	{
		color = col;
	};

	float intersect(Vector pos, Vector dir);

	Vector normal(Vector p);

};

#endif //!H_BOX
