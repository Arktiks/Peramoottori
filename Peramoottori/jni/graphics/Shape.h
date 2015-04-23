#ifndef SHAPE_H
#define SHAPE_H

#include <scene\Component.h>
#include <scene\Transformable.h>
#include <glm\vec2.hpp>
#include <vector>

static const double PI = 3.141;

namespace pm
{
	class Shape : public Component
	{
	public:

		Shape() : Component()
		{
			origin = glm::vec2(0.0, 0.0);
		};

		virtual void SetOrigin(glm::vec2 newOrigin)
		{
			origin = newOrigin;
		}

		virtual void SetOrigin(float newOriginX, float newOriginY)
		{
			origin = { newOriginX, newOriginY };
		}

		std::vector<float> GetVertices()
		{
			return vertices;
		}

		std::vector<unsigned short> GetIndices()
		{
			return indices;
		}

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