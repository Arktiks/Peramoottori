#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include <scene\Camera.h>
#include <core\Log.h>

/** \internal Work in progress. */

namespace pm
{

	/** \brief System that handles the camera changes.
	* To switch views you can switch cameras with the CameraSystem.
	*/

	class CameraSystem
	{
		friend class Camera;

	public:
		
		/** \brief Gain acess to CameraSystem.
		* \return Returns handle to CameraSystem singleton object.
		*/
		static CameraSystem* GetInstance(); 

		/** \brief Set active Camera.
		*
		* \param[in] camera Pointer to new Camera.
		* \note When called CameraSystems default camera will be deleted.
		*/
		void SetActiveCamera(Camera* camera);

		/** \brief Set active camera back to default.
		* Creates a new default camera object.
		*/
		void CreateDefaultCamera();
		
		/** \brief Get pointer to active camera.
		* \return Pointer to active camera.
		*/
		Camera* GetActiveCamera();

	private:
		static CameraSystem* instance;
		CameraSystem();
		~CameraSystem() {};

		Camera* activeCamera;
		bool defaultCamera;

	};
}

#endif //CAMERASYSTEM_H