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
		//virtual void setPosition(glm::vec2 position)
		//{
		//	this->position = position;
		//};
		//virtual void setSize(glm::vec2 size)
		//{
		//	this->size = size;
		//};
		int drawDepht;

		bool draw; // Think about better name. Spritebatch uses this to determinate if sprite will be added to buffer.

	protected:


		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		
		float colorRed, colorGreen, colorBlue;

	};
}

#endif