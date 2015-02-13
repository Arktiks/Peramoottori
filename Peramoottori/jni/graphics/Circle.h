#ifndef CIRCLE_H

#define CIRCLE_H

#include "graphics\Shape.h"

class Circle : public virtual Shape
{
public:

	Circle(float tempPositionX, float tempPositionY, float tempRadius, int smoothness);
	~Circle();

private:

	int smoothness;
	float radius;

};
#endif