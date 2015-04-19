#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include <scene\Component.h>
#include <glm\vec2.hpp>

namespace pm
{
	class Transformable : public Component
	{
	public:
		Transformable() : position(glm::vec2(0.0f, 0.0f)),
			scale(glm::vec2(1.0f, 1.0f)),
			rotation(0.0f),
			depthBuffer(0) {};

		Transformable(glm::vec2 position, glm::vec2 scale, float rotation) :
			position(position), scale(scale), rotation(rotation), depthBuffer(0) {};

		~Transformable() {};

		void SetPosition(glm::vec2 newPosition);
		void SetPosition(float newPositionX, float newPositionY);
		void SetScale(glm::vec2 newScale);
		void SetScale(float newScaleX, float newScaleY);
		void SetRotation(float newRotation);
		void SetDepth(int newDepthValue);

		glm::vec2 GetPosition();
		glm::vec2 GetScale();
		float GetRotation();
		int GetDepth();

	private:
		glm::vec2 position;
		glm::vec2 scale;

		int depthBuffer;
		
		float rotation;
	};
}

#endif