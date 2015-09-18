#include <scene\Camera.h>

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

pm::Camera::Camera()
{
	cameraPosition	= glm::vec2(0, 0);
	cameraRotation	= 0.0f;
	cameraZoom		= 0.0f;
	
	cameraMatrix	= glm::mat4(1);
}

void pm::Camera::SetCameraMatrix(glm::mat4 newCameraMatrix)
{
	cameraMatrix = newCameraMatrix;
}

void pm::Camera::SetCameraPosition(float xPosition, float yPosition)
{
	cameraPosition = glm::vec2(xPosition, yPosition);
	CalculateMatrix();
}

void pm::Camera::SetCameraPosition(glm::vec2 newPosition)
{
	cameraPosition = newPosition;
	CalculateMatrix();
}

void pm::Camera::SetCameraRotation(float newRotation)
{
	cameraRotation = newRotation;
	CalculateMatrix();
}

void pm::Camera::SetCameraZoom(float newZoom)
{
	cameraZoom = newZoom;
	CalculateMatrix();
}

void pm::Camera::CalculateMatrix()
{
	cameraMatrix = glm::scale(glm::vec3(cameraZoom, cameraZoom, 0.0f)) * cameraMatrix;
	cameraMatrix = glm::rotate(cameraRotation * 3.14f / 180.0f, glm::vec3(0, 0, 1)) * cameraMatrix;
	cameraMatrix = glm::translate(glm::vec3(cameraPosition, 0.0f)) * cameraMatrix;
}
glm::mat4 pm::Camera::GetCameraMatrix()
{
	return cameraMatrix;
}