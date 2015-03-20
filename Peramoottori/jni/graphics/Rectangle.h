#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

namespace pm
{
	class Rectangle : public virtual Shape
	{
	public:

		Rectangle(float yPosition, float xPosition, float widht, float height);
		Rectangle(glm::vec2 position, glm::vec2 size);
		void setPosition(glm::vec2 position);
		void setSize(glm::vec2 size);


		~Rectangle();

	private:

		float widht, height;

	};
}

#endif