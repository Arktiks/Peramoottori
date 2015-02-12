#ifndef TRIANGLE_H

#define TRIANGLE_H

#include "graphics\Shape.h"

class Triangle : public Shape
{
public:

	Triangle(float positionX, float positionY, float radius);
	~Triangle();

private:
	float radius;
	
};
#endif