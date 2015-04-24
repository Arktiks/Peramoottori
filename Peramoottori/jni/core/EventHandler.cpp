#include "EventHandler.h"
#include <core\Input.h>
#include <core\Log.h>
#include <core\Application.h>
#include <core\Memory.h>
#include <core\Passert.h>

using namespace pm;

void EventHandler::Initialize(android_app* application)
{
	// ASensorManager is singleton class that handles device sensors.
	ASensorManager* sensorManager = ASensorManager_getInstance();
	ASSERT_NEQUAL(sensorManager, nullptr); // Something wrong with device perhaps.

	// Get handle to possible accelerometer, no danger on reassigning pointer.
	accelerometerSensor = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_ACCELEROMETER);
	if (accelerometerSensor != nullptr) // In case device doesn't have accelerometer.
		hasAccelerometer = true;
	else
		hasAccelerometer = false;

	// Create queue that handles sensor events as they come.
	if(sensorEventQueue == nullptr)
		sensorEventQueue = ASensorManager_createEventQueue(sensorManager, application->looper, LOOPER_ID_USER, nullptr, nullptr);

	application->onAppCmd = ProcessCommand; // What function is referred on application calls.
	application->onInputEvent = HandleInput; // What function is referred on input calls.
}

void EventHandler::EnableSensors()
{
	if (hasAccelerometer) // If device has accelerometer.
	{
		int tempStatus = ASensorEventQueue_enableSensor(sensorEventQueue, accelerometerSensor);

		if (tempStatus < 0)
			DEBUG_WARNING(("Enabling accelerometer failed!"));

		tempStatus = ASensorEventQueue_setEventRate(sensorEventQueue, accelerometerSensor, (1000L / 60) * 1000);

		if (tempStatus < 0)
			DEBUG_WARNING(("Setting accelerometer event rate failed!"));
	}

	// Add possible other sensor data.
}

void EventHandler::DisableSensors()
{
	if (hasAccelerometer) // Stop monitoring the accelerometer. This is to avoid consuming battery while not being used.
	{
		int tempStatus = ASensorEventQueue_disableSensor(sensorEventQueue, accelerometerSensor);

		if (tempStatus < 0)
			DEBUG_WARNING(("Disabling accelerometer failed!"));
	}
}

void EventHandler::Start()
{
}

void EventHandler::Resume()
{
}

void EventHandler::Pause()
{
}

void EventHandler::Stop()
{
}

void EventHandler::Destroy()
{
}

void EventHandler::ReadyWindow()
{
}

void EventHandler::TerminateWindow()
{
}

void EventHandler::GainedFocus()
{
}

void EventHandler::LostFocus()
{
}

EventHandler::~EventHandler()
{
	ASensorManager* sensorManager = ASensorManager_getInstance();
	ASensorManager_destroyEventQueue(sensorManager, sensorEventQueue); // Free all resources associated with event queue.
}

////////////////////////////////////////
//
//	Below static functions given to android_native_app_glue.
//
////////////////////////////////////////

int EventHandler::HandleInput(android_app* application, AInputEvent* event)
{
	if (AInputEvent_getSource(event) == AINPUT_SOURCE_TOUCHSCREEN) // AInputEvent contains properties of input events.
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
	bool testSucces = false;

	switch (command)
	{
		// When activity is becoming visible to user.
		// Followed by APP_CMD_RESUME if the activity comes to the foreground
	case APP_CMD_START:
		//Start();
		DEBUG_INFO(("ProcessCommand: START"));
		break;


		// When activity will start interacting with user.
		// At this point your activity is at the top of activity stack, with user input going to it.
	case APP_CMD_RESUME:
		DEBUG_INFO(("ProcessCommand: RESUME"));
		break;


		// Called when system is about to start resuming another activity.
		// This is typically used to commit unsaved changes to persistent data,
		// stop animations and other things that may be consuming CPU
	case APP_CMD_PAUSE:
		DEBUG_INFO(("ProcessCommand: PAUSE"));
		break;


		// Activity is no longer visible to user, because another activity has
		// been resumed and is covering this one. This may happen either because
		// new activity is being started, an existing one is being brought in front of this one, or this one is being destroyed.
	case APP_CMD_STOP:
		DEBUG_INFO(("ProcessCommand: STOP"));
		break;
		

		// Final call you receive before activity is destroyed.
		// This can happen either because the activity is finishing or because
		// system is temporarily destroying this instance of activity to save space.
	case APP_CMD_DESTROY:
		DEBUG_INFO(("ProcessCommand: APP_CMD_DESTROY"));
		Memory::WriteLeaks(); // Write memory leaks to LogCat.
		DEBUG_INFO(("APP_CMD_DESTROY has finished cleaning application.")); // For some reason destroy is not called when application closes.
		break;


		// Called when ANativeWindow is ready for use.
		// android_app->window will contain the new window surface.
	case APP_CMD_INIT_WINDOW:
		DEBUG_INFO(("ProcessCommand: INIT_WINDOW"));

		ASSERT_NEQUAL(application->window, nullptr); // Make sure INIT_WINDOW calls is legit.

		testSucces = tempApplication->window.LoadDisplay(application); // WindowHandler creates display, surface and context.
		ASSERT(testSucces);

		break;


		// ANativeWindow needs to be terminated. Upon receiving this command, android_app->window still
		// contains existing window; after calling android_app_exec_cmd it will be set to NULL.
	case APP_CMD_TERM_WINDOW:
		DEBUG_INFO(("ProcessCommand: TERM_WINDOW"));

		testSucces = tempApplication->window.CloseDisplay(); // The window is being hidden or closed, clean it up.
		ASSERT(testSucces);

		break;


	case APP_CMD_GAINED_FOCUS:
		DEBUG_INFO(("ProcessCommand: APP_CMD_GAINED_FOCUS"));
		tempApplication->events.EnableSensors(); // When application gains focus, start monitoring sensors.
		break;


	case APP_CMD_LOST_FOCUS:
		DEBUG_INFO(("ProcessCommand: APP_CMD_LOST_FOCUS"));
		tempApplication->events.DisableSensors();
		break;


	default:
		break;
	}
}