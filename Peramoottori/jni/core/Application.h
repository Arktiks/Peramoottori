#ifndef APPLICATION_H
#define APPLICATION_H

#include <core/WindowHandler.h>
#include <core/EventHandler.h>
#include <android_native_app_glue.h>

namespace pm
{
	/// Core application system.
	/// Handles most of communication with java side. 
	/// Should be inherited from for more specific application needs.

	class Application
	{

		friend class EventHandler; // Required for static android_native_app_glue functions.

	protected:

		Application() : androidApplication(nullptr) {}; ///< Default constructor: Initialize needs to be called for everything to work properly.

		/// Initializes Peramoottori modules.
		///		\param application: pointer to android_application.
		void Initialize(android_app* application);

		bool Update(); ///< Core update loop, should be nested in while-statement.

		void SwapBuffers(); ///< Handles swapping front and back buffers.

		void Clear(); ///< Clear display.

		android_app* androidApplication; ///< Pointer to android application.

		WindowHandler window; ///< Handles display of android device.

		EventHandler events; ///< Handles input and event processing.

		~Application(); ///< Protected destructor prevents delete through base class.
	};
}

#endif