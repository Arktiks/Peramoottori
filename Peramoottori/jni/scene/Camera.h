#ifndef CAMERA_H
#define CAMERA_H

#include <glm\mat4x4.hpp>
#include <glm\vec2.hpp>

namespace pm
{

	/** \brief Class for controlling screen view.
	*
	* Default camera is created if none is in use.
	* Camera can be used to zoom, move and/or rotate view.
	*
	* \ingroup Scene
	*/

	class Camera
	{
		friend class CameraSystem;

	public:

		/** \brief Creates a Camera in position (0,0), with rotation of 0 degrees and 1.0 zoom.
		*
		*/
		Camera();

		/** \brief Moves Camera by given values in x and y directions.
		* \param[in] x ammount camera should be moved horizontally
		* \param[in] y ammount camera should be moved vertically
		*/
		void MoveCamera(float x, float y);

		/** \brief Moves Camera by given values in x and y directions.
		*
		* \param[in] moveXY glm::vec2 [x,y].
		*/
		void MoveCamera(glm::vec2 moveXY);

		/** \brief Rotates Camera by given value in degrees.
		* \param[in] rotation how many degrees camera should be rotated
		*/
		void RotateCamera(float rotation);

		/** \brief Zooms Camera by given value.
		* \param[in] zoom how much to zoom
		*/
		void ZoomCamera(float zoom);

		/** \brief Set Camera matrix directly.
		*
		* \param[in] newCameraMatrix New matrix as glm::mat4.
		*/
		void SetCameraMatrix(glm::mat4 newCameraMatrix);
		
		/** \brief Set Camera position to given coordinates.
		* \param[in] xPosition x coordinate
		* \param[in] yPosition y coordinate
		*/
		void SetCameraPosition(float xPosition, float yPosition);
		
		/** \brief Set Camera position to given coordinates.
		*
		* \param[in] newPosition glm::vec2 [x,y].
		*/
		void SetCameraPosition(glm::vec2 newPosition);
		
		/** \brief Set Camera rotation.
		*  \param[in] newRotation angle in degrees
		*/
		void SetCameraRotation(float newRotation);
		
		/** \brief Set Camera Zoom.
		* zoom is a multiplier
		* 1.0 will show the original size
		* 2.0 will show everything twice the size of the original
		* 0.5 will show everything half the size of the original
		* \param[in] newZoom 
		*/
		void SetCameraZoom(float newZoom);
		
		/** \brief Get Camera matrix.
		* 
		* \return glm::mat4 transformation of Camera.
		*/
		glm::mat4 GetCameraMatrix();
		
		/** \brief Get inverse Camera matrix.
		* 
		* \return glm::mat4 inverse transformation of Camera.
		*/
		glm::mat4 GetInverseCameraMatrix();

		/** \brief Get camera location coordinates.
		*
		* \return glm::vec2 camera xy coordinates.
		*/
		glm::vec2 GetCameraLocation();

		/** \brief Get camera rotation angle.
		*
		* \return float camera rotation angle.
		*/
		float GetCameraRotation();

		/** \brief Get camera zoom value.
		*
		* \return float camer zoom value.
		*/
		float GetCameraZoom();

	private:

		glm::vec2 origin;

		void CalculateMatrix();

		glm::mat4 cameraMatrix;
	
		glm::vec2 cameraPosition;
		float cameraRotation;
		float cameraZoom;

	};
}

#endif // CAMERA_H