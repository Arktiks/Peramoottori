#ifndef RECTANGLE_H

#define RECTANGLE_H

#include "graphics/Shape.h"

class Rectangle : public Shape
{
public:

	Rectangle(float yPosition, float xPosition, float widht, float height);
	~Rectangle();

private:

	float widht, height;

};
#endif
