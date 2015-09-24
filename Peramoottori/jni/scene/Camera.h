#ifndef CAMERA_H
#define CAMERA_H


#include <glm\mat4x4.hpp>
#include <glm\vec2.hpp>


namespace pm
{
	/// Class for controlling screen view.
	class Camera
	{
	public:
		/// Default constructor.
		/**
		* Creates a camera in position xy(0,0), with rotation of 0.0f degrees and 1.0x zoom.
		*/
		Camera();

		/**
		* Moves camera by given values in x and y directions.
		*/
		void MoveCamera(float x, float y);
		/**
		* Moves camera by given values in x and y directions.
		*/
		void MoveCamera(glm::vec2 moveXY);

		/**
		* Rotates camera by given value in degrees.
		*/
		void RotateCamera(float rotation);

		/**
		* Zooms camera by given value.
		*/
		void ZoomCamera(float zoom);

		/**
		* Set camera matrix directly.
		*/
		void SetCameraMatrix(glm::mat4 newCameraMatrix);
		
		/**
		* Set camera position to given coordinates.
		*/
		void SetCameraPosition(float xPosition, float yPosition);
		
		/**
		* Set camera position to given coordinates.
		*/
		void SetCameraPosition(glm::vec2 newPosition);
		
		/**
		* Set camera rotation.
		*/
		void SetCameraRotation(float newRotation);
		
		/**
		* Set camera Zoom.
		*/
		void SetCameraZoom(float newZoom);
		
		/**
		* Get camera matrix.
		*/
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