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
		Transformable(glm::vec2 position, glm::vec2 origin, glm::vec2 scale, float rotation);

		void SetPosition(glm::vec2 newPosition);
		void SetPosition(float positionX, float positionY);
		void SetOrigin(glm::vec2 newOrigin);
		void SetOrigin(float originX, float originY);
		void SetScale(glm::vec2 newScale);
		void SetScale(float scaleX, float scaleY);
		void SetRotation(float newRotation);
		
	private:
		glm::vec2 position;
		glm::vec2 origin;
		glm::vec2 scale;
		
		float rotation;
	};
}

#endif