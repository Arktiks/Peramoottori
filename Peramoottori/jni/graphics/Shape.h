#ifndef SHAPE_H
#define SHAPE_H

#include <scene\Component.h>
#include <scene\Transformable.h>
#include <glm\common.hpp>
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


	protected:

		std::vector<float> vertices;
		std::vector<unsigned int> indices;

		glm::vec2 origin;
	};
}

#endif