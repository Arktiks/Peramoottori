#ifndef APPLICATION_H
#define APPLICATION_H

#include <cstddef>
#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "Info", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "Warning", __VA_ARGS__))

#include <android_native_app_glue.h>
#include <android/asset_manager.h>
#include <EGL/egl.h>

namespace AApp
{

	/// Struct that holds application information and can be stored on java side.



	/// The core application system.
	/**
		Handles most of the communication with java side.
		*/
	class Application
	{
	public:
		/// Default Constructor.
		Application();

		/// Initializing the Application.
		/**
			\param application takes in the android_app
			*/
		void Initialize(android_app* application);

		/// The core update loop.
		/**
			TODO
			*/
		bool Update();

		/// Handles swapping buffers if the display is initialized.
		/**
		\param event input event received on java side
		\return Returns 1 if input is received, 0 if not.
		*/
		void DrawFrame();

		/// Returns Android AssetManager for use outside of this class.
		/**
		\return Returns the AAssetManager*
		*/
		AAssetManager* GetAssetManager();

		/// Processes command events.
		/**
		\param command the command event number
		*/
		// void ProcessCommand(android_app* application, int32_t command);
		struct Engine
		{
			struct android_app* app;
			AAssetManager* assetManager;
			Application* applicationPointer;

			EGLDisplay display;
			EGLSurface surface;
			EGLContext context;

			float x;
			float y;
			int width;
			int height;

			Engine() : app(nullptr), assetManager(nullptr), display(EGL_NO_DISPLAY),
				surface(EGL_NO_SURFACE), context(EGL_NO_SURFACE), x(0.0f), y(0.0f), width(0), height(0) {};
		};

		/// Called when APP_CMD_TERM_WINDOW is received by processCommand.
		/**
		*/
		void TerminateDisplay();

		/// Called when APP_CMD_INIT_WINDOW is received by processCommand.
		/**
		*/
		int InitializeDisplay();

		/// Given to android_app for handling input.
		/**
			\return Returns 0 on success, -1 if failed.
			*/
		//int HandleInput(android_app* application, AInputEvent* event);

		Engine engine;
	};

	// Static data members need to be defined, in addition to being declared in the class.
}

#endif