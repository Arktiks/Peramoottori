#include "Application.h"

#include <jni.h>
#include <errno.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/input.h>

#include <core/Input.h>
#include <core/Log.h>

//#include <MemoryManager.h>
//#include <system/PMassert.h>
//#include <system/PMdebug.h>
//#include <System\Time.h>
//#include <resources/ResourceManager.h>
//#include <system\Input.h>

using namespace pm;

void ProcessCommand(android_app* application, int32_t command);
int HandleInput(android_app* application, AInputEvent* event);



void Application::Initialize(android_app* application)
{
	//app_dummy(); // Ensures glue code isn't stripped.
	app = application;
	engine.app->onAppCmd = ProcessCommand;
	engine.app->userData = &engine;
	engine.app->onInputEvent = HandleInput;
	engine.assetManager = application->activity->assetManager;
	//pm::ResourceManager::GetInstance(application->activity->assetManager); // Initialize the ResourceManager with AAssetManager.


	//LOGI("Application has been initialized.");
}


bool Application::Update()
{
	Input::Update();
	while (ALooper_pollAll(0, nullptr, nullptr, reinterpret_cast<void**>(&eventSource)) >= 0)
	{
		if (eventSource != nullptr)
			eventSource->process(engine.app, eventSource);

		if (engine.app->destroyRequested != 0)
		{
			TerminateDisplay();
			return false;
		}
	}
	return true;
}


void Application::DrawFrame()
{
	if(engine.display == EGL_NO_DISPLAY)
	{
		return;
		// No display.
		//LOGW("No EGL_DISPLAY present while DrawFrame() was called.");
	}
	
	eglSwapBuffers(engine.display, engine.surface);
}


int HandleInput(android_app* application, AInputEvent* event)
{
	struct Application::Engine* engine = (struct Application::Engine*)application->userData;

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

	return 0;
}


void ProcessCommand(android_app* application, int32_t command)
{
	switch (command)
	{
	case APP_CMD_RESUME:
		DEBUG_INFO(("RESUME"));
		break;

	case APP_CMD_PAUSE:
		DEBUG_INFO(("PAUSE"));
		break;

	case APP_CMD_INIT_WINDOW:
		if (application->window != nullptr) // The window is being shown, get it ready.
			window.LoadDisplay();
		break;

	case APP_CMD_TERM_WINDOW:
		engine->applicationPointer->TerminateDisplay(); // The window is being hidden or closed, clean it up.
		break;

	default:
		break;
	}
}