#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include <scene\Component.h>
#include <glm\vec2.hpp>
#include <glm\mat4x4.hpp>

namespace pm
{
	/** \brief Component that stores data for translation, transformation and rotation.
	*
	* Description.
	*
	* \ingroup Scene
	*/

	class Transformable : public Component
	{
	public:

		/** \brief
		*
		* Default values are set to position(0,0) | scale(1,1) | rotation(0) | depth(0).
		*/
		Transformable() : position(glm::vec2(0.0f, 0.0f)),
			scale(glm::vec2(1.0f, 1.0f)),
			rotation(0.0f),
			depthBuffer(0) {};

		/** \brief
		*
		* \param[in] position glm::vec2 [x,y].
		* \param[in] scale glm::vec2 [x,y].
		* \param[in] rotation as float.
		*/

		Transformable(glm::vec2 position, glm::vec2 scale, float rotation) :
			position(position), scale(scale), rotation(rotation), depthBuffer(0) 
		{
			CalculateMatrix();
		};

		

		~Transformable() {};

		/** \brief Set position of GameEntity.
		*
		* \param[in] newPosition glm::vec2 [x,y].
		*/
		void SetPosition(glm::vec2 newPosition);

		/** \brief Set position of GameEntity. */
		void SetPosition(float newPositionX, float newPositionY);

		/** \brief Set scale of GameEntity.
		*
		* \param[in] newScale glm::vec2 [x,y].
		*/
		void SetScale(glm::vec2 newScale);

		/** \brief Set scale of GameEntity. */
		void SetScale(float newScaleX, float newScaleY);

		/** \brief Set rotation of GameEntity.
		*
		* \param[in] newRotation as float.
		*/
		void SetRotation(float newRotation);

		/** \brief Set depth of GameEntity.
		*
		* Base depth of drawables is 0. As the you increase depth objects
		* will be drawn over objects with lesser depth.
		*
		* \param[in] newDepthValue as float.
		*/
		void SetDepth(float newDepthValue);

		/** \brief Get transformation applied to GameEntity.
		*
		* \return glm::mat4 transformation.
		*/
		glm::mat4 GetTransformMatrix() { return transformMatrix; }

		/** \brief Get position of GameEntity.
		*
		* \return glm::vec2 position [x,y].
		*/
		glm::vec2 GetPosition();

		/** \brief Get scale of GameEntity.
		*
		* \return glm::float2 scale [x,y].
		*/
		glm::vec2 GetScale();

		/** \brief Get rotation of GameEntity.
		*
		* \return float rotation.
		*/
		float GetRotation();

		/** \brief Get depth of GameEntity.
		*
		* \return float depth.
		*/
		float GetDepth();

	private:

		void CalculateMatrix();

		glm::mat4 transformMatrix;

		glm::vec2 position;
		glm::vec2 scale;

		float depthBuffer;
		
		float rotation;
	};
}

#endif