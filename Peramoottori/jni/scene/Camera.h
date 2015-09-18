#ifndef CAMERA_H
#define CAMERA_H


#include <glm\mat4x4.hpp>
#include <glm\vec2.hpp>


namespace pm
{
	class Camera
	{
	public:
		Camera();

		void SetCameraMatrix(glm::mat4 newCameraMatrix);
		
		void SetCameraPosition(float xPosition, float yPosition);
		void SetCameraPosition(glm::vec2 newPosition);
		
		void SetCameraRotation(float newRotation);
		
		void SetCameraZoom(float newZoom);
		
		glm::mat4 GetCameraMatrix();

	private:

		void CalculateMatrix();

		glm::mat4 cameraMatrix;
	
		glm::vec2 cameraPosition;
		float cameraRotation;
		float cameraZoom;

	};
}

#endif //CAMERA_H