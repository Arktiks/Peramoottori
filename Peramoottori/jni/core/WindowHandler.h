#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H

#include <EGL/egl.h>
#include <android_native_app_glue.h>
#include <core/Vector2.h>
#include <string>

namespace pm
{
	/** \brief Handles display of android device. Should be accessed through Application class.
	*
	* Main functionality includes clearing screen and returning device resolution.
	*/

	class WindowHandler
	{

	friend class CommandCenter; // CommandCenter handles window loading and closing.
	friend class Application;

	public:

		/** \brief Return device resolution.
		*
		* \return Vector2<int>: screen width (x) and height (y).
		*/
		Vector2<int> GetResolution();

		/// Clear display with set color.
		void Clear();

		/// Set color for Clear() as RGB.
		void SetClearColor(float red, float green, float blue);

		/** \brief Exchanges front and back buffers of device window.
		*
		* Double buffering uses two display buffers to smoothen animation.
		* The next screen is prepared in back buffer, while the current screen is held in front buffer.
		* 
		* Already included in Application::Draw() function.
		*/
		void SwapBuffers();

		/** \brief Returns current status of device rendering context.
		*
		* Initializing the rendering context can take up to multiple seconds, as such
		* it's important to make sure the context is up before proceeding with other graphical tasks.
		* \return True if EGL rendering context is working.
		*/
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