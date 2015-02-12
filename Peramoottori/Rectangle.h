#ifndef RECTANGLE_H

#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape
{
public:

	Rectangle();
	~Rectangle();

private:

	float height, widht;

};
#endif
