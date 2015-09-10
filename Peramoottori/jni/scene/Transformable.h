#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include <scene\Component.h>
#include <glm\vec2.hpp>

namespace pm
{
	/// Component for GameEntity:s that strores data for translation, transformation and rotation.

	class Transformable : public Component
	{
	public:

		/// Constructor.
		Transformable() : position(glm::vec2(0.0f, 0.0f)),
			scale(glm::vec2(1.0f, 1.0f)),
			rotation(0.0f),
			depthBuffer(0) {};

		/// Constructor.
		Transformable(glm::vec2 position, glm::vec2 scale, float rotation) :
			position(position), scale(scale), rotation(rotation), depthBuffer(0) {};

		~Transformable() {};

		/// Sets the position.
		void SetPosition(glm::vec2 newPosition);

		/// Sets the position.
		void SetPosition(float newPositionX, float newPositionY);

		/// Sets the scale.
		void SetScale(glm::vec2 newScale);

		/// Sets the sclae.
		void SetScale(float newScaleX, float newScaleY);

		/// Sets the rotation.
		void SetRotation(float newRotation);

		/// Sets the depth.
		void SetDepth(int newDepthValue);

		/// Returns glm float vec2 position.
		glm::vec2 GetPosition();

		/// Returns glm float vec2 scale.
		glm::vec2 GetScale();

		/// Returns rotation value as float.
		float GetRotation();

		/// Returns depth value as int.
		int GetDepth();

	private:

		glm::vec2 position;
		glm::vec2 scale;

		int depthBuffer;
		
		float rotation;
	};
}

#endif