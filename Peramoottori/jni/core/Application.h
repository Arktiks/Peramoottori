#ifndef APPLICATION_H
#define APPLICATION_H

#include <core/WindowHandler.h>
#include <android_native_app_glue.h>
#include <android/sensor.h>
#include <vector>

namespace pm
{
	/// Core application system.
	/// Handles most of communication with java side. 


	//class Application;
	//static void AddContextFunction(bool(*Context)()); /// Adds functions call that are only called once after context creation.


	class Application
	{

		friend class android_native_app_glue; // User won't be able to tamper with input handling and command processing.
		friend class TestClass;

	protected: // User should only use Game class.

		/// Default constructor: Initialize needs to be called for everything to work properly.
		Application() :
			eventSource(nullptr),
			androidApplication(nullptr),
			sensorManager(nullptr),
			sensorEventQueue(nullptr),
			accelerometerSensor(nullptr) {};

		/// Constructor that calls Initialize().
		Application(android_app* application);

		~Application();

		/// Initializes context and ResourceManger.
		///		\param application: pointer to android_application.
		void Initialize(android_app* application);

		/// Core update loop.
		///		\return true as default; when TerminateDisplay is called returns false.
		bool Update();

		/// Handles swapping buffers if display is initialized.
		void DrawFrame();

		/// Clears display.
		void ClearScreen();

		android_poll_source* eventSource; ///< Used by Update().
		android_app* androidApplication; ///< Pointer to android application.
		ASensorManager* sensorManager; ///< Singleton that manages sensors.
		ASensorEventQueue* sensorEventQueue; ///< Sensor event queue.
		const ASensor* accelerometerSensor; ///< Accelerometer.

		WindowHandler window; ///< Handles display of android device.

		static std::vector<bool (*)()> updateFunctions; ///< Functions that are added into Update() loop.
		static std::vector<void (*)()> drawFunctions; ///< Functions that are added into DrawFrame() loop.
		static std::vector<bool(*)()> contextFunctions; ///< Functions that are only called once after context initialize.


	private: // These should work because app_glue is friend class.

		/// Handles inputs for android application.
		static int HandleInput(android_app* application, AInputEvent* event);

		/// Handles command processing for android application.
		static void ProcessCommand(android_app* application, int32_t command);

	};
}

#endif

/*
/// Returns Android AssetManager for use outside of this class.
///		\return Returns the AAssetManager*
AAssetManager* GetAssetManager();
/// TO-BE-USED-MAYBE - easily add our modules to the initializing list.
//void InitializeModules(android_app* application);
/// Get reference to display manager.
//WindowHandler& GetWindow();
//double frameTime; ///< Track deltaTime.
/// Adds function calls to Update() loop.
static void AddUpdateFunction(bool(*Update)());

/// Adds function calls to DrawFrame() loop.
static void AddDrawFunction(void(*Draw)());
*/