#ifndef SHAPE_H
#define SHAPE_H

#include <scene\Component.h>
#include <scene\Transformable.h>
#include <glm\vec2.hpp>
#include <vector>

static const double PI = 3.141;

namespace pm
{

	/** \brief Base class for all drawable shapes.
	*
	* Description.
	*
	* \ingroup Scene
	*/

	class Shape : public Component
	{
	public:

		Shape() : Component(), origin(glm::vec2(0.0, 0.0)) {};

		/** \brief Set origin from which transformations are applied to Shape.
		*
		* By default all transformations are applied from left-top corner.
		*
		* \param[in] newOrigin New point of transformation.
		*/
		virtual void SetOrigin(glm::vec2 newOrigin)	{ origin = newOrigin; }

		/** \brief Set origin from which transformations are applied to Shape.
		*
		* By default all transformations are applied from left-top corner.
		*/
		virtual void SetOrigin(float newOriginX, float newOriginY) { origin = { newOriginX, newOriginY }; }

		/** \brief Return vertices of Shape.
		*
		* \return vector<float> vertices of Shape.
		*/
		std::vector<float> GetVertices() { return vertices; }

		/** \brief Return indices of Shape.
		*
		* \return vector<unsigned short> indices of Shape.
		*/
		std::vector<unsigned short> GetIndices() { return indices; }

		/** \brief Return origin of Shape.
		*
		* \return glm::vec2 origin [x, y].
		*/
		glm::vec2 GetOrigin() { return origin; }

	protected:

		std::vector<float> vertices;
		std::vector<unsigned short> indices;
		glm::vec2 origin;
	};
}

#endif