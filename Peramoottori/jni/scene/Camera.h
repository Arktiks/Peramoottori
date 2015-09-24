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

		void MoveCamera(float x, float y);
		void MoveCamera(glm::vec2 moveXY);

		void RotateCamera(float rotation);

		void ZoomCamera(float zoom);

		void SetCameraMatrix(glm::mat4 newCameraMatrix);
		
		void SetCameraPosition(float xPosition, float yPosition);
		void SetCameraPosition(glm::vec2 newPosition);
		
		void SetCameraRotation(float newRotation);
		
		void SetCameraZoom(float newZoom);
		
		glm::mat4 GetCameraMatrix();

	private:

		glm::vec2 origin;

		void CalculateMatrix();

		glm::mat4 cameraMatrix;
	
		glm::vec2 cameraPosition;
		float cameraRotation;
		float cameraZoom;

	};
}

#endif //CAMERA_H