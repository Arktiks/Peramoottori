#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include <scene\Camera.h>

/** \internal Work in progress. */

namespace pm
{

	/** \brief Work in progress.
	*
	*
	*/

	class CameraSystem
	{
		friend class Camera;

	public:
		static CameraSystem* GetInstance(); ///< Returns handle to CameraSystem singleton object.

		/** \brief Set active Camera.
		*
		* \param[in] camera Pointer to new Camera.
		* \note When called CameraSystems default camera will be deleted.
		*/
		void SetActiveCamera(Camera* camera);

		/** \brief Set active camera back to default.
		*
		*
		*/
		void CreateDefaultCamera();

		Camera* GetActiveCamera(); ///< Returns active camera.

	private:
		static CameraSystem* instance;
		CameraSystem();
		~CameraSystem(){};

		Camera* activeCamera;
		bool defaultCamera;

	};
}

#endif //CAMERASYSTEM_H