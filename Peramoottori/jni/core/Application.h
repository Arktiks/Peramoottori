#ifndef APPLICATION_H
#define APPLICATION_H

//#include <cstddef>
//#include <android/asset_manager.h>
//#include <EGL/egl.h>


#include <android_native_app_glue.h>
#include "WindowHandler.h"


namespace pm
{
	/// The core application system.
	/**
	Handles most of the communication with java side. 
		-Create an Application instance.
		-use the Initialize.
		-Create your mainloop with while(app.Update)
	*/
	class Application
	{
	public:

		/// Default Constructor.
		Application() {};

		/// Initializing the Application.
		/**
			\param application takes in the android_app
		*/
		void Initialize(android_app* application);

		/// The core update loop.
		/**
			You can construct the main loop of your game using the update, place it in while(app.Update).
			\return Returns true as default, when TerminateDisplay is called, returns false.
		*/
		bool Update();

		/// Handles swapping buffers if the display is initialized.
		/**
			TODO
		*/
		void DrawFrame();

		/// Returns Android AssetManager for use outside of this class.
		/**
			\return Returns the AAssetManager*
		*/
		AAssetManager* GetAssetManager();

		/// Called when APP_CMD_TERM_WINDOW is received by processCommand.
		/**
			Destroys the egl Context, Surface and terminates the Display when done.
		*/
		void TerminateDisplay();

		/// Called when APP_CMD_INIT_WINDOW is received by processCommand.
		/**
			Initializes the EGL surface, display and context, Stores them in Engine.
			\return Returns -1 if failed to make the display, surface and context current. Returns 0 if succesful.
		*/
		int InitializeDisplay();



	private:

		android_poll_source* eventSource; ///< Used by Update() 

		struct android_app* app; // android app pointteri

		double frameTime; // ehkä timeria varten

		WindowHandler window;

	};
}

#endif