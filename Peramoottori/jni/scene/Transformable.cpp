#include "Transformable.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

void pm::Transformable::SetPosition(glm::vec2 newPosition)
{
	position = newPosition;
	CalculateMatrix();
}

void pm::Transformable::SetPosition(float newPositionX, float newPositionY)
{
	position = { newPositionX, newPositionY };
	CalculateMatrix();
}

void pm::Transformable::SetScale(glm::vec2 newScale)
{
	scale = newScale;
	CalculateMatrix();
}

void pm::Transformable::SetScale(float newScaleX, float newScaleY)
{
	scale = { newScaleX, newScaleY };
	CalculateMatrix();
}

void pm::Transformable::SetRotation(float newRotation)
{
	rotation = newRotation;
	CalculateMatrix();
}

void pm::Transformable::SetDepth(float newDepthValue)
{
	depthBuffer = newDepthValue;
}

glm::vec2 pm::Transformable::GetPosition()
{
	return position;
}

glm::vec2 pm::Transformable::GetScale()
{
	return scale;
}

float pm::Transformable::GetRotation()
{
	return rotation;
}

float pm::Transformable::GetDepth()
{
	return depthBuffer;
}

void pm::Transformable::CalculateMatrix()
{
	transformMatrix = glm::mat4(1);

	transformMatrix = glm::scale(glm::vec3(scale, 0.0f)) * transformMatrix;
	transformMatrix = glm::rotate(rotation*3.14f / 180.0f, glm::vec3(0, 0, 1)) * transformMatrix;
	transformMatrix = glm::translate(glm::vec3(position, 0.0f)) * transformMatrix;
}