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
}

void CommandCenter::Resume()
{
}

void CommandCenter::Pause()
{
}

void CommandCenter::Stop()
{
}

void CommandCenter::Destroy()
{
	Application::GetInstance()->DestroyInstance(); // Application takes care of cleaning up rest of modules.
	Memory::WriteLeaks(); // Write memory leaks to LogCat.
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

int CommandCenter::HandleInput(android_app* application, AInputEvent* event)
{

	/*
	Actual C++ explanation, but very brief.
	http://flohofwoe.blogspot.fi/2014/10/cross-platform-multitouch-input.html

	How its done in java, might be useful.
	http://stackoverflow.com/questions/14391818/how-do-you-use-motionevent-action-pointer-index-shift
	*/

	/** CURRENT PROBLEMS
	* How to make sure pointer index of the AMOTION_EVENT_ACTION is correct?
	* Done with bitshift?
	* Reshift the index to a temp mask with the event type, then compare flags for action and index?
	*/


	if (AInputEvent_getSource(event) == AINPUT_SOURCE_TOUCHSCREEN) // AInputEvent contains properties of input events.
	{
		if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
		{
			int action = AMotionEvent_getAction(event);
			int pointerIndex = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
			int pointerID = AMotionEvent_getPointerId(event, pointerIndex);

			switch (action & AMOTION_EVENT_ACTION_MASK)
			{
			case AMOTION_EVENT_ACTION_DOWN && AMOTION_EVENT_ACTION_POINTER_DOWN:
			{
				Input::NewPointer(pointerID, AMotionEvent_getX(event, pointerIndex), AMotionEvent_getY(event, pointerIndex));
				break;
			}
			case AMOTION_EVENT_ACTION_UP:
			{
				Input::NoPointers();
				break;
			}
			case AMOTION_EVENT_ACTION_POINTER_UP:
			{
				if (Input::CheckPointer(pointerID))
					Input::RemovePointer(pointerID);
				break;
			}
			case AMOTION_EVENT_ACTION_MOVE:
			{
				if (Input::CheckPointer(pointerID))
					Input::MovePointer(pointerID, AMotionEvent_getX(event, pointerIndex), AMotionEvent_getY(event, pointerIndex));
				break;
			}

			default:
				break;
			}


		}
	}
	return 0; // Return 0 for any default dispatching.
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