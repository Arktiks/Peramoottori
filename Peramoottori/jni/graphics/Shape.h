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
		int drawDepht;
	bool draw; // Think about better name. Spritebatch uses this to determinate if sprite will be added to buffer.
	protected:


		std::vector<float> vertices;
		std::vector<unsigned int> indices;

		Transformable transformable;

		float colorRed, colorGreen, colorBlue;

	};
}

#endif