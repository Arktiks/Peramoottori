#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H

#include <EGL/egl.h>
#include <android_native_app_glue.h>
#include <core/Vector2.h>

namespace pm
{
	/// Handles the display of android device.

	class WindowHandler
	{

	friend class Application; // Application can use this class freely.
	friend class Game;

	public:
		WindowHandler() :
			display(EGL_NO_DISPLAY),
			surface(EGL_NO_SURFACE),
			context(EGL_NO_CONTEXT),
			width(0),
			height(0) {};

	private:

		bool HasContext();

		Vector2<int> GetResolution();

		/// Called when APP_CMD_INIT_WINDOW is received by ProcessCommand.
		/// Initializes EGL surface, display and context.
		void LoadDisplay(android_app* application);

		/// Called when APP_CMD_TERM_WINDOW is received by ProcessCommand.
		///	Destroys EGL display, context and terminates the display when done.
		void CloseDisplay();

		EGLSurface surface;
		EGLDisplay display;
		EGLContext context;

		int width; ///< Width of device surface.
		int height; ///< Height of device surface.
	};
}

#endif