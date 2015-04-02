#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include <scene\Component.h>
#include <glm\common.hpp>

namespace pm
{
	class Transformable : public Component
	{
	public:
		Transformable();
		Transformable(glm::vec2 position, glm::vec2 scale, float rotation);
		~Transformable();

		void SetPosition(glm::vec2 newPosition);
		void SetPosition(float newPositionX, float newPositionY);
		void SetScale(glm::vec2 newScale);
		void SetScale(float newScaleX, float newScaleY);
		void SetRotation(float newRotation);
		void SetDepth(float newDepthValue);
		
	private:
		glm::vec2 position;
		glm::vec2 scale;

		float depthBuffer;
		
		float rotation;
	};
}

#endif