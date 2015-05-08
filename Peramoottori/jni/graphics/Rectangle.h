#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

namespace pm
{
	/// Rectangle shape that is inherited from shape base class.
	class Rectangle : public Shape
	{
	public:

		/// default constructor.
		Rectangle() : width(0), height(0) { 
		SetIndices();
		SetVertices();
		};

		/// constructor.
		Rectangle(float width, float height);

		/// constructor.
		Rectangle(glm::vec2 size);

		/// Set the origin of the rectangle.
		void SetOrigin(glm::vec2 newOrigin);

		/// Set the origin of the rectangle.
		void SetOrigin(float newOriginX, float newOriginY);

		/// Set the size of the rectangle.
		void SetSize(glm::vec2 newSize);

		/// Set the size of the rectangle.
		void SetSize(float newSizeX, float newSizeY);

		/// returns glm vec2 that has the size of the rectangle.
		glm::vec2 GetSize();
		
	private:
		
		///sets vertises of rectangle
		void SetVertices();

		/// sets indexes of rectangle
		void SetIndices();

		float width, height;

	};
}

#endif