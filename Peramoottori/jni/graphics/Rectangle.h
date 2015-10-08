#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

namespace pm
{

	/** \brief Drawable rectangle shape derived from Shape class.
	*
	* Description.
	*
	* \ingroup Scene
	*/

	class Rectangle : public Shape
	{
	public:

		Rectangle() : width(0), height(0)
		{ 
			SetIndices();
			SetVertices();
		}

		/**
		* \param[in] width of Rectangle.
		* \param[in] height of Rectangle.
		*/
		Rectangle(float width, float height);

		/**
		* \param[in] size glm::vec2 [width, height].
		*/
		Rectangle(glm::vec2 size);

		/** \brief Set origin from which transformations are applied to Rectangle.
		*
		* By default all transformations are applied from left-top corner.
		*
		* \param[in] newOrigin New point of transformation.
		*/
		void SetOrigin(glm::vec2 newOrigin);

		/** \brief Set origin from which transformations are applied to Shape.
		*
		* By default all transformations are applied from left-top corner.
		*/
		void SetOrigin(float newOriginX, float newOriginY);

		/** \brief Set size for Rectangle.
		*
		* \param[in] newSize glm::vec2 [width, height].
		*/
		void SetSize(glm::vec2 newSize);

		/** \brief Set size for Rectangle. */
		void SetSize(float newSizeX, float newSizeY);

		/** \brief Return size of Rectangle.
		*
		* \return glm::vec size [width, height].
		*/
		glm::vec2 GetSize();
		
		/** \brief Return origin of Rectangle.
		*
		* \return glm::vec2 origin [width, height].
		*/
		glm::vec2 GetOrigin();

	private:
		
		/// Sets vertises of rectangle.
		void SetVertices();

		/// Sets indexes of rectangle.
		void SetIndices();

		float width, height;
	};
}

#endif