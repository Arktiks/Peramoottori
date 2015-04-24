#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H

#include <EGL/egl.h>
#include <android_native_app_glue.h>
#include <core/Vector2.h>
#include <string>

namespace pm
{
	/// Handles display of android device.

	class WindowHandler
	{

	friend class CommandCenter; // CommandCenter handles window loading and closing.
	friend class Application;

	public:

		/// Return display resolution.
		Vector2<int> GetResolution();

		/// Clears display with set color.
		void Clear();

		void SetClearColor(float red, float green, float blue);

		void SwapBuffers();

		/// Status of context.
		bool HasContext();

	private:

		/// Only Application should invoke constructor.
		WindowHandler() :
			display(EGL_NO_DISPLAY),
			surface(EGL_NO_SURFACE),
			context(EGL_NO_CONTEXT),
			width(0), height(0) {};

		/// Initializes EGL surface, display and context.
		bool LoadDisplay(android_app* application);

		///	Destroys EGL display, context and terminates display when done.
		bool CloseDisplay();

		bool Warning(std::string function);

		EGLSurface surface;
		EGLDisplay display;
		EGLContext context;

		int width; ///< Width of device surface.
		int height; ///< Height of device surface.
	};
}

#endif