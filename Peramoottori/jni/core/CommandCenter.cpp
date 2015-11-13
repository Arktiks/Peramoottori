#include "CommandCenter.h"
#include <core\Log.h>
#include <core\Passert.h>
#include <core\Memory.h>

#include <core\Input.h>
#include <core\Application.h>
#include <resources\TextureFactory.h>
#include <graphics\RenderSystem.h>

using namespace pm;
using namespace std;

const ASensor* CommandCenter::accelerometerSensor = nullptr;
ASensorEventQueue* CommandCenter::sensorEventQueue = nullptr;
android_app* CommandCenter::android_application = nullptr;
bool CommandCenter::focus = false;

void CommandCenter::Initialize(android_app* application)
{
	ASSERT_NEQUAL(application, nullptr); // Something wrong with Perämoottori.

	ASensorManager* sensorManager = ASensorManager_getInstance(); // ASensorManager is singleton class that handles device sensors.
	ASSERT_NEQUAL(sensorManager, nullptr); // Something wrong with device.

	// Get handle to possible accelerometer, no danger on reassigning pointer.
	accelerometerSensor = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_ACCELEROMETER);

	if(sensorEventQueue == nullptr) // Create queue that handles sensor events as they come.
		sensorEventQueue = ASensorManager_createEventQueue(sensorManager, application->looper, LOOPER_ID_USER, nullptr, nullptr);

	if (application != nullptr)
		CommandCenter::android_application = application; // Save application reference for later use.
	else
		DEBUG_WARNING(("Command Center initialize called with null application pointer."));
}

void CommandCenter::Clean()
{
	ASensorManager* sensorManager = ASensorManager_getInstance();
	ASensorManager_destroyEventQueue(sensorManager, sensorEventQueue); // Free all resources associated with event queue.
	accelerometerSensor = nullptr;
	sensorEventQueue = nullptr;
	android_application = nullptr;
}

void CommandCenter::EnableSensors()
{
	if (accelerometerSensor != nullptr) // Does device have accelerometer.
	{
		int tempStatus = ASensorEventQueue_enableSensor(sensorEventQueue, accelerometerSensor);

		if (tempStatus < 0)
			DEBUG_WARNING(("Enabling accelerometer failed!"));

		tempStatus = ASensorEventQueue_setEventRate(sensorEventQueue, accelerometerSensor, (1000L / 60) * 1000);

		if (tempStatus < 0)
			DEBUG_WARNING(("Setting accelerometer event rate failed!"));
	}
}

void CommandCenter::DisableSensors()
{
	if (accelerometerSensor != nullptr) // Stop monitoring the accelerometer. This is to avoid consuming battery while not being used.
	{
		int tempStatus = ASensorEventQueue_disableSensor(sensorEventQueue, accelerometerSensor);

		if (tempStatus < 0)
			DEBUG_WARNING(("Disabling accelerometer failed!"));
	}
}

void CommandCenter::UpdateSensors(int identity)
{
	Input::Update();

	if(identity == LOOPER_ID_USER)
	{
		if(accelerometerSensor != nullptr) // Update accelerometer paremeters.
		{
			ASensorEvent tempEvent; // Holds event details.
			while(ASensorEventQueue_getEvents(sensorEventQueue, &tempEvent, 1) > 0) // Loop through all accelerometer calls.
				Input::InputEventAccelerometer(tempEvent.acceleration.x, tempEvent.acceleration.y, tempEvent.acceleration.z);
		}
	}
}

void CommandCenter::Start()
{
	StartFunction tempFunctionPointer = Application::GetInstance()->getStartFunction();

	if (tempFunctionPointer != nullptr)
	{
		(*tempFunctionPointer)();
	}
	else
	{
		DEBUG_WARNING(("Start function pointer not defined"));
	}
}

void CommandCenter::Resume()
{
	ResumeFunction tempFunctionPointer = Application::GetInstance()->getResumeFunction();

	if (tempFunctionPointer != nullptr)
	{
		(*tempFunctionPointer)();
	}
	else
	{
		DEBUG_WARNING(("Resume function pointer not defined"));
	}
}

void CommandCenter::Pause()
{
	PauseFunction tempFunctionPointer = Application::GetInstance()->getPauseFunction();

	if (tempFunctionPointer != nullptr)
	{
		(*tempFunctionPointer)();
	}
	else
	{
		DEBUG_WARNING(("Pause function pointer not defined"));
	}
}

void CommandCenter::Stop()
{
	StopFunction tempFunctionPointer = Application::GetInstance()->getStopFunction();

	if (tempFunctionPointer != nullptr)
	{
		(*tempFunctionPointer)();
	}
	else
	{
		DEBUG_WARNING(("Stop function pointer not defined"));
	}
}

void CommandCenter::Destroy()
{
	Application::GetInstance()->DestroyInstance(); // Application takes care of cleaning up rest of modules.
	#ifdef _DEBUG 
	Memory::WriteLeaks(); // Write memory leaks to LogCat.
	#endif
	DEBUG_INFO(("Application has been destroyed!"));
}

void CommandCenter::ReadyWindow(android_app* application)
{
	ASSERT_NEQUAL(android_application->window, nullptr); // Make sure INIT_WINDOW call is legit.
	bool testSucces = Application::GetInstance()->window.LoadDisplay(android_application); // WindowHandler creates display, surface and context.
	ASSERT(testSucces);
	Application::GetInstance()->Initialize(application);
	TextureFactory::RecreateOGLTextures(); // Currently no confirmation everything was successful.
}

void CommandCenter::TerminateWindow()
{
	TextureFactory::DestroyOGLTextures();
	RenderSystem::GetInstance()->DestroyInstance(); // Destroy our rendering system, it will be reconstructed once we have our context back.
	bool testSucces = Application::GetInstance()->window.CloseDisplay(); // The window is being hidden or closed, clean it up.
	ASSERT(testSucces);
}

void CommandCenter::GainedFocus()
{
	focus = true;
	EnableSensors();
}

void CommandCenter::LostFocus()
{
	focus = false;
	DisableSensors();
}

int32_t CommandCenter::HandleInput(android_app* application, AInputEvent* _event)
{
	return Input::AndroidEventHandler(_event);
}

void CommandCenter::ProcessCommand(android_app* application, int32_t command)
{
	if(application != nullptr)
	{
		switch(command)
		{
		case APP_CMD_START:
			DEBUG_INFO(("ProcessCommand: START"));
			Start();
			break;

		case APP_CMD_RESUME:
			DEBUG_INFO(("ProcessCommand: RESUME"));
			Resume();
			break;

		case APP_CMD_PAUSE:
			DEBUG_INFO(("ProcessCommand: PAUSE"));
			Pause();
			break;

		case APP_CMD_STOP:
			DEBUG_INFO(("ProcessCommand: STOP"));
			Stop();
			break;

		case APP_CMD_DESTROY:
			DEBUG_INFO(("ProcessCommand: DESTROY"));
			Destroy();
			break;

		case APP_CMD_INIT_WINDOW:
			DEBUG_INFO(("ProcessCommand: INIT_WINDOW"));
			ReadyWindow(application);
			break;

		case APP_CMD_TERM_WINDOW:
			DEBUG_INFO(("ProcessCommand: TERM_WINDOW"));
			TerminateWindow();
			break;

		case APP_CMD_GAINED_FOCUS:
			DEBUG_INFO(("ProcessCommand: APP_CMD_GAINED_FOCUS"));
			GainedFocus();
			break;

		case APP_CMD_LOST_FOCUS:
			DEBUG_INFO(("ProcessCommand: APP_CMD_LOST_FOCUS"));
			LostFocus();
			break;

		default:
			break;
		}
	}
	else
		DEBUG_WARNING(("Could not ProcessCommand because Game has not been initialized yet."));
}