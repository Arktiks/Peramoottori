#ifndef RECTANGLE_H

#define RECTANGLE_H

#include "graphics/Shape.h"

class Rectangle : public virtual Shape
{
public:

	Rectangle(float yPosition, float xPosition, float widht, float height);
	Rectangle(glm::vec2 position, glm::vec2 size);
	~Rectangle();

private:

	float widht, height;

};
#endif
