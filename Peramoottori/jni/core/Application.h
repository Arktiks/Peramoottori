#ifndef APPLICATION_H
#define APPLICATION_H

#include "WindowHandler.h"
#include <android_native_app_glue.h>
#include <android/sensor.h>
#include <vector>

namespace pm
{
	/// Core application system.
	/// Handles most of communication with java side. 
	///	To use simply create an Application instance.
	///	Initialize it with pointer to android application.

	class Application
	{
	public:
		/// Default Constructor.
		Application() : eventSource(nullptr), androidApplication(nullptr), frameTime(0.0) {};

		/// Constructor that initializes everything neccessary.
		Application(android_app* application);

		/// Initializes our custom Application.
		///		\param application : pointer to android_application.
		void Initialize(android_app* application);

		/// TO-BE-USED-MAYBE - easily add our modules to the initializing list.
		void InitializeModules(android_app* application);

		/// The core update loop.
		///	You can construct the main loop of your game using Update(), place it in while(app.Update()).
		///		\return true as default. When TerminateDisplay is called returns false.
		bool Update();

		/// Handles swapping buffers if the display is initialized.
		/// TODO
		void DrawFrame();

		/// Clears the display.
		void ClearScreen();

		/// Get reference to display manager.
		//WindowHandler& GetWindow();

		/// Adds function calls to Update() loop.
		static void AddUpdateFunction(bool (*Update)());

		/// Adds function calls to DrawFrame() loop.
		static void AddDrawFunction(void (*Draw)());

		/// Adds functions call that are only called once after context creation.
		static void AddContextFunction(bool (*Context)());

		/// Handles inputs for android application.
		static int HandleInput(android_app* application, AInputEvent* event);

		/// Handles command processing for android application.
		static void ProcessCommand(android_app* application, int32_t command);

	private:
		android_poll_source* eventSource; ///< Used by Update().
		struct android_app* androidApplication; ///< Pointer to android application.
		double frameTime; ///< Track deltaTime.
		WindowHandler window; ///< Handles display of android device.

		ASensorManager* sensorManager; ///< Singleton that manages sensors.
		ASensorEventQueue* sensorEventQueue; ///< Sensor event queue.
		const ASensor* accelerometerSensor; ///< Accelerometer.

		static std::vector<bool (*)()> updateFunctions; ///< Functions that are added into Update() loop.
		static std::vector<void (*)()> drawFunctions; ///< Functions that are added into DrawFrame() loop.
		static std::vector<bool(*)()> contextFunctions; ///< Functions that are only called once after 
	};
}

#endif

/*
/// Returns Android AssetManager for use outside of this class.
///		\return Returns the AAssetManager*
AAssetManager* GetAssetManager();*/