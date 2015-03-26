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

		void SetOrigin(glm::vec2 newOrigin);
		void SetOrigin(float x, float y);
		~Rectangle();

	private:

		float width, height;

	};
}

#endif