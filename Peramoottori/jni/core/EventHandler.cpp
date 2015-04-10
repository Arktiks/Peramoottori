#include "EventHandler.h"
#include <core\Input.h>
#include <core\Log.h>
#include <core\Application.h>
#include <core\Memory.h>

using namespace pm;

void EventHandler::Initialize(android_app* application)
{
	// ASensorManager is singleton class that handles device sensors.
	ASensorManager* sensorManager = ASensorManager_getInstance();

	// Get handle to possible accelerometer.
	accelerometerSensor = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_ACCELEROMETER);
	if (accelerometerSensor != nullptr) // In case device doesn't have accelerometer.
		hasAccelerometer = true;

	// Create queue that handles sensor events as they come.
	sensorEventQueue = ASensorManager_createEventQueue(sensorManager, application->looper, LOOPER_ID_USER, nullptr, nullptr);

	application->onAppCmd = ProcessCommand; // What function is referred on application calls.
	application->onInputEvent = HandleInput; // What function is referred on input calls.
}

EventHandler::~EventHandler()
{
	ASensorManager* sensorManager = ASensorManager_getInstance();
	ASensorManager_destroyEventQueue(sensorManager, sensorEventQueue); // Free all resources associated with event queue.
}

int EventHandler::HandleInput(android_app* application, AInputEvent* event)
{
	// AInputEvent contains properties of input events.
	if (AInputEvent_getSource(event) == AINPUT_SOURCE_TOUCHSCREEN)
	{
		if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) // Input event is motion.
			Input::InputEventMovement(AMotionEvent_getX(event, 0), AMotionEvent_getY(event, 0));

		if (AKeyEvent_getAction(event) == AKEY_EVENT_ACTION_DOWN) // Key has been pressed down.
			Input::InputEventKeyDown();

		if (AKeyEvent_getAction(event) == AKEY_EVENT_ACTION_UP) // Key has been released.
			Input::InputEventKeyUp();
	}

	// Return 1 if you have handled the event.
	return 0; // Return 0 for any default dispatching.
}

void EventHandler::ProcessCommand(android_app* application, int32_t command)
{
	// Get reference to our Application class.
	Application* tempApplication = static_cast<Application*>(application->userData);

	switch (command)
	{
	case APP_CMD_RESUME:
		DEBUG_INFO(("ProcessCommand: RESUME"));
		break;

	case APP_CMD_PAUSE:
		DEBUG_INFO(("ProcessCommand: PAUSE"));
		break;

	case APP_CMD_INIT_WINDOW:
		DEBUG_INFO(("ProcessCommand: INIT_WINDOW"));
		if (application->window != nullptr) // The window is being shown, get it ready.
		{
			tempApplication->window.LoadDisplay(application); // WindowHandler creates display, surface and context.
			// Other functions neccessary for drawing should be initialized here.
		}
		break;

	case APP_CMD_TERM_WINDOW:
		DEBUG_INFO(("ProcessCommand: TERM_WINDOW"));
		tempApplication->window.CloseDisplay(); // The window is being hidden or closed, clean it up.
		break;

	case APP_CMD_GAINED_FOCUS:
		DEBUG_INFO(("ProcessCommand: APP_CMD_GAINED_FOCUS"));
		/// When our app gains focus, we start monitoring the accelerometer.
		if (tempApplication->events.hasAccelerometer) // If device has accelerometer.
		{
			int tempStatus = ASensorEventQueue_enableSensor
				(tempApplication->events.sensorEventQueue,
				tempApplication->events.accelerometerSensor);

			if (tempStatus < 0)
				DEBUG_WARNING(("Enabling accelerometer failed!"));

			tempStatus = ASensorEventQueue_setEventRate
				(tempApplication->events.sensorEventQueue,
				tempApplication->events.accelerometerSensor, (1000L / 60) * 1000);

			if (tempStatus < 0)
				DEBUG_WARNING(("Setting accelerometer event rate failed!"));
		}
		break;

	case APP_CMD_LOST_FOCUS:
		DEBUG_INFO(("ProcessCommand: APP_CMD_LOST_FOCUS"));
		// When app loses focus, stop monitoring the accelerometer. This is to avoid consuming battery while not being used.
		if (tempApplication->events.hasAccelerometer)
		{
			int tempStatus = ASensorEventQueue_disableSensor
				(tempApplication->events.sensorEventQueue,
				tempApplication->events.accelerometerSensor);

			if (tempStatus < 0)
				DEBUG_WARNING(("Disabling accelerometer failed!"));
		}
		break;

	case APP_CMD_DESTROY:
		DEBUG_INFO(("ProcessCommand: APP_CMD_DESTROY"));
		Memory::WriteLeaks(); // Write memory leaks to LogCat.
		DEBUG_INFO(("APP_CMD_DESTROY has finished cleaning application.")); // For some reason destroy is not called when application closes.

	default:
		break;
	}
}