#include "Application.h"
#include <core/Log.h>
#include <core/Passert.h>
#include <core/Memory.h>
#include <resources/ResourceManager.h>
#include <core/Input.h>
#include <GLES2/gl2.h> // Should be removed once there are no OpenGL-calls.

using namespace std;
using namespace pm;

void Application::Initialize(android_app* application)
{
	app_dummy(); // Ensures glue code isn't stripped.
	(this->androidApplication) = application; // Save application pointer for later use.

	ASSERT_NEQUAL(androidApplication, nullptr);

	application->userData = static_cast<void*>(this); // Store our Application class to native glue.

	events.Initialize(application);

	ResourceManager::GetInstance()->Initialize(application->activity->assetManager); // Initialize ResourceManager with AAssetManager.

	DEBUG_INFO(("Application has been initialized."));
}

bool Application::Update()
{
	Input::Update();

	int tempIdent = 0; // See what looper is calling.
	android_poll_source* tempEventSource = nullptr; // Contains reference to executable command.

	while ((tempIdent = ALooper_pollAll(0, nullptr, nullptr, reinterpret_cast<void**>(&tempEventSource))) >= 0)
	{
		if (tempEventSource != nullptr)
			tempEventSource->process(androidApplication, tempEventSource);

		if (tempIdent == LOOPER_ID_USER)
		{
			if (events.hasAccelerometer) // Update accelerometer paremeters.
			{
				ASensorEvent tempEvent; // Holds event details.
				while (ASensorEventQueue_getEvents(events.sensorEventQueue, &tempEvent, 1) > 0) // Loop through all accelerometer calls.
					Input::InputEventAccelerometer(tempEvent.acceleration.x, tempEvent.acceleration.y, tempEvent.acceleration.z);
			}
		}

		if (androidApplication->destroyRequested != 0) // When application is losing focus or being destroyed.
			return false;
	}

	return true;
}

void Application::SwapBuffers()
{
	// Could be moved elsewhere.
	bool testSucces = eglSwapBuffers(window.display, window.surface);
	ASSERT(testSucces);
}

void Application::Clear()
{
	// Could be moved elsewhere.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Application::~Application()
{
	androidApplication->userData = nullptr; // Remove reference to this class.
	DEBUG_INFO(("Application destructor called."));
}