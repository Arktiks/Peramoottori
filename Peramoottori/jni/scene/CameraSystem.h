#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include <scene\Camera.h>

/** \internal Work in progress. */

namespace pm
{

	/** \brief Work in progress.
	*
	* Description.
	*/

	class CameraSystem
	{
		friend class Camera;

	public:
		static CameraSystem* GetInstance();

		void SetActiveCamera(Camera* camera);/// Set active camera.
		Camera* GetActiveCamera();///< Returns active camera.

	private:
		CameraSystem();
		~CameraSystem(){};
		static CameraSystem* instance;

		Camera* activeCamera;
		bool defaultCamera;

	};
}


#endif //CAMERASYSTEM_H