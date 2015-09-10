#ifndef SHAPE_H
#define SHAPE_H

#include <scene\Component.h>
#include <scene\Transformable.h>
#include <glm\vec2.hpp>
#include <vector>

static const double PI = 3.141;

namespace pm
{
	/// Shape Component that is the base class for other shapes.

	class Shape : public Component
	{
	public:

		/// Constructor.
		Shape() : Component()
		{
			origin = glm::vec2(0.0, 0.0);
		}

		/// Sets origin.
		virtual void SetOrigin(glm::vec2 newOrigin)
		{
			origin = newOrigin;
		}

		/// Sets origin.
		virtual void SetOrigin(float newOriginX, float newOriginY)
		{
			origin = { newOriginX, newOriginY };
		}

		/// Returns vertices float vector.
		std::vector<float> GetVertices()
		{
			return vertices;
		}

		/// Returns indices unsigned short vector.
		std::vector<unsigned short> GetIndices()
		{
			return indices;
		}

		/// Returns glm vec2 origin.
		glm::vec2 GetOrigin()
		{
			return origin;
		}

	protected:

		std::vector<float> vertices;
		std::vector<unsigned short> indices;
		glm::vec2 origin;
	};
}

#endif