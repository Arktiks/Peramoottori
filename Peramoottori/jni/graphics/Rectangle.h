#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

namespace pm
{
	class Rectangle : public virtual Shape
	{
	public:

		Rectangle(float newWidth, float newHeight);
		Rectangle(glm::vec2 size);
		void setSize(glm::vec2 size);


		~Rectangle();

	private:

		float widht, height;

	};
}

#endif