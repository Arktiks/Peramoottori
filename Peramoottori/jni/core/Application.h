#ifndef APPLICATION_H
#define APPLICATION_H

#include <core/WindowHandler.h>
#include <android_native_app_glue.h>

namespace pm
{
	/// Core application system.
	/// Handles most of communication with java side. 

	class Application
	{

		friend class EventHandler; // Required for static android_native_app_glue functions.

	public:

		/// Return only instance of Application. 
		/// Only one instance of Application should exist during runtime.
		static Application* GetInstance();

		/// Deletes Application.
		void DestroyInstance();

		/// Initializes Perämoottori and its modules.
		///		\param application: pointer to android_application struct.
		void Initialize(android_app* application);

		/// Core update loop, should be nested in while-statement.
		bool Update(); 

		/// Draw GameObjects contained in SpriteBatch.
		void Draw();

		/// Return true if Application is ready to be updated and drawn.
		bool IsReady();

		bool IsFocused();

		/// Loops infinitely until Application is ready to be updated and drawn.
		void Wait();

		WindowHandler window; ///< Handles display of android device.

		void* saveData; ///< Pointer to hold saved data.

	private:

		/// Print warning messages if trying to use Application without initializing.
		bool Warning(std::string function);

		/// Default constructor.
		/// Initialize needs to be called for Application to work properly.
		Application() : application(nullptr) {}; 

		/// Private destructor prevents delete.
		/// Class needs to be cleaned up with DestroyInstance.
		~Application() {};

		android_app* application; ///< Pointer to android application.

		static Application* instance; ///< Pointer to only instance of the class.
	};
}

#endif