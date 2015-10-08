#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include <scene\Camera.h>

namespace pm
{
	class CameraSystem
	{
		friend class Camera;

	public:
		static CameraSystem* GetInstance();///< Returns handle to CameraSystem singleton object

		void SetActiveCamera(Camera* camera);/// Set active camera.
		Camera* GetActiveCamera();///< Returns active camera.
	

	private:
		static CameraSystem* instance;
		CameraSystem();
		~CameraSystem(){};

		Camera* activeCamera;
		bool defaultCamera;

	};
}


#endif //CAMERASYSTEM_H