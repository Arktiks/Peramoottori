#include "Application.h"
#include <core/Input.h>
#include <core/Log.h>
#include <core/Passert.h>
#include <resources/ResourceManager.h>
#include <android/input.h>
#include <graphics/SpriteBatch.h>

using namespace std;
using namespace pm;

vector<bool(*)()> Application::updateFunctions;
vector<void(*)()> Application::drawFunctions;
vector<bool(*)()> Application::contextFunctions;

Application::Application(android_app* application) : eventSource(nullptr), frameTime(0.0)
{
	Initialize(application);
}

void Application::Initialize(android_app* application)
{
	app_dummy(); // Ensures glue code isn't stripped.
	(this->androidApplication) = application; // Make note of application pointer.
	application->onAppCmd = ProcessCommand; // What function is referred on application calls.
	application->userData = static_cast<void*>(this); // Store our Application class to Native Glue.
	application->onInputEvent = HandleInput; // What function is referred on input calls.

	ResourceManager::GetInstance(application->activity->assetManager); // Initialize the ResourceManager with AAssetManager.

	//InitializeModules(application);
	DEBUG_INFO(("Application has been initialized."));
}

bool Application::Update()
{
	Input::Update();
	int ident;

	while (ALooper_pollAll(0, nullptr, nullptr, reinterpret_cast<void**>(&eventSource)) >= 0)
	{
		if (eventSource != nullptr)
			eventSource->process(androidApplication, eventSource);

		if (ident == LOOPER_ID_USER)
		{
			if (accelerometerSensor != NULL)
			{
				ASensorEvent event;
				while (ASensorEventQueue_getEvents(sensorEventQueue, &event, 1) > 0)
				{
					Input::InputEventAccelerometer(event.acceleration.x, event.acceleration.y, event.acceleration.z);
				}
			}
		}

		if(androidApplication->destroyRequested != 0)
			return false;

		if (window.context != EGL_NO_CONTEXT)
			return false;

		/*if (!contextFunctions.empty() && window.context != EGL_NO_CONTEXT)
		{
			for (vector<bool(*)()>::iterator it = contextFunctions.begin(); it != contextFunctions.end(); it++)
			{
				ASSERT(*it);
				it = contextFunctions.erase(it);
			}
		}*/
	}
	return true;
}

void Application::DrawFrame()
{
	if(window.display == EGL_NO_DISPLAY || window.context == EGL_NO_CONTEXT)
	{
		DEBUG_INFO(("Skipped DrawFrame()."));
		return;
	}
	
	for (const auto& tempFunction : drawFunctions) // Loop through our added functions.
		tempFunction();

	SpriteBatch::GetInstance()->Draw();

	eglSwapBuffers(window.display, window.surface);
}

void Application::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/*WindowHandler& Application::GetWindow()
{
	return window;
}*/

void Application::AddUpdateFunction(bool (*Update)())
{
	// Need to add checks and such that code won't explode.
	updateFunctions.push_back(Update);
}

void Application::AddDrawFunction(void (*Draw)())
{
	drawFunctions.push_back(Draw);
}

void Application::AddContextFunction(bool(*Context)())
{
	contextFunctions.push_back(Context);
}

int Application::HandleInput(android_app* application, AInputEvent* event)
{
	if (AInputEvent_getSource(event) == AINPUT_SOURCE_TOUCHSCREEN)
	{
		if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
		{
			Input::InputEventMovement(AMotionEvent_getX(event, 0), AMotionEvent_getY(event, 0));
		}

		if (AKeyEvent_getAction(event) == AKEY_EVENT_ACTION_DOWN)
		{
			Input::InputEventKeyDown();
		}

		if (AKeyEvent_getAction(event) == AKEY_EVENT_ACTION_UP)
		{
			Input::InputEventKeyUp();
		}
	}
	return 0;
}

void Application::ProcessCommand(android_app* application, int32_t command)
{
	// Get reference to our created Application class.
	Application* tempApplication = static_cast<Application*>(application->userData);

	switch (command)
	{
	case APP_CMD_RESUME:
		DEBUG_INFO(("RESUME"));
		break;

	case APP_CMD_PAUSE:
		DEBUG_INFO(("PAUSE"));
		break;

	case APP_CMD_INIT_WINDOW:
		DEBUG_INFO(("INIT_WINDOW"));
		if (application->window != nullptr) // The window is being shown, get it ready.
		{
			tempApplication->window.LoadDisplay(application);
			SpriteBatch::GetInstance()->Initialize();
		}
		break;

	case APP_CMD_TERM_WINDOW:
		DEBUG_INFO(("TERM_WINDOW"));
		tempApplication->window.CloseDisplay(); // The window is being hidden or closed, clean it up.
		break;

	case APP_CMD_GAINED_FOCUS:
		// When our app gains focus, we start monitoring the accelerometer.
		//if (tempApplication->accelerometerSensor != NULL)
		//{
		//	ASensorEventQueue_enableSensor(tempApplication->sensorEventQueue,
		//	tempApplication->accelerometerSensor);
		//	// We'd like to get 60 events per second (in us).
		//	ASensorEventQueue_setEventRate(tempApplication->sensorEventQueue,
		//		tempApplication->accelerometerSensor, (1000L / 60) * 1000);
		//}
		break;

	default:
		break;
	}
}