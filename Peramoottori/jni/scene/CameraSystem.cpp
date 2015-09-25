#include <scene\CameraSystem.h>
#include <core\Memory.h>


pm::CameraSystem* pm::CameraSystem::instance = nullptr;

pm::CameraSystem* pm::CameraSystem::GetInstance()
{
	if (instance == nullptr)
		instance = NEW CameraSystem();
	return instance;
}

void pm::CameraSystem::SetActiveCamera(Camera* camera)/// Set active camera.
{
	defaultCamera = false;
	activeCamera = camera;
}

pm::Camera* pm::CameraSystem::GetActiveCamera()///< Returns active camera.
{
	return activeCamera;
}

pm::CameraSystem::CameraSystem()
{
	defaultCamera = NEW Camera();
	defaultCamera = true; 
}
