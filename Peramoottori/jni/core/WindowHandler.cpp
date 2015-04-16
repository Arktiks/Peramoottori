#include "WindowHandler.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <core/Log.h>
#include <core/Passert.h>

using namespace pm;

bool WindowHandler::HasContext()
{
	if (context != EGL_NO_CONTEXT)
		return true;
	else
		return false;
}

Vector2<int> WindowHandler::GetResolution()
{
	if (HasContext())
		return Vector2<int>(width, height);
	else
	{
		return Vector2<int>(0, 0);
		DEBUG_WARNING(("GetResolution() without context!"));
	}
}

bool WindowHandler::LoadDisplay(android_app* application)
{
	//DEBUG_INFO(("WindowHandler::LoadDisplay() beginning."));

	EGLBoolean testSucces = false; // Test if calls are successful.

	// Attributes are hard customised to work with OpenGL ES2.
	const EGLint attribs[] =
	{
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_DEPTH_SIZE, 16,
		EGL_NONE
	};

	EGLint attribList[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	EGLint width, height, dummy, format, numConfigs;
	EGLConfig config;

	EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	testSucces = eglInitialize(display, 0, 0);
	ASSERT_NEQUAL(testSucces, EGL_FALSE);

	testSucces = eglChooseConfig(display, attribs, &config, 1, &numConfigs);
	ASSERT_NEQUAL(testSucces, EGL_FALSE);

	testSucces = eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
	ASSERT_NEQUAL(testSucces, EGL_FALSE);

	ANativeWindow_setBuffersGeometry(application->window, 0, 0, format);

	EGLSurface surface = eglCreateWindowSurface(display, config, application->window, nullptr);
	ASSERT_NEQUAL(surface, EGL_NO_SURFACE);

	EGLContext context = eglCreateContext(display, config, nullptr, attribList);
	ASSERT_NEQUAL(context, EGL_NO_CONTEXT);

	testSucces = eglMakeCurrent(display, surface, surface, context); // Crash the program if we can't bind context to rendering thread.
	ASSERT_NEQUAL(testSucces, EGL_FALSE);

	eglQuerySurface(display, surface, EGL_WIDTH, &width);
	ASSERT_NEQUAL(width, 0);

	eglQuerySurface(display, surface, EGL_HEIGHT, &height);
	ASSERT_NEQUAL(height, 0);

	// Hold this information in WindowHandler.
	(this->surface) = surface;
	(this->display) = display;
	(this->context) = context;
	(this->width) = width;
	(this->height) = height;

	return true;
	//DEBUG_INFO(("WindowHandler::LoadDisplay() finished."));
}

bool WindowHandler::CloseDisplay()
{
	//DEBUG_INFO(("WindowHandler::CloseDisplay() beginning."));

	EGLBoolean testSucces = false; // Test if calls are successful.

	if (display != EGL_NO_DISPLAY)
	{
		testSucces = eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		ASSERT_NEQUAL(testSucces, EGL_FALSE);

		if (context != EGL_NO_CONTEXT)
		{
			testSucces = eglDestroyContext(display, context);
			ASSERT_NEQUAL(testSucces, EGL_FALSE);
		}

		if (surface != EGL_NO_SURFACE)
		{
			testSucces = eglDestroySurface(display, surface);
			ASSERT_NEQUAL(testSucces, EGL_FALSE);
		}

		testSucces = eglTerminate(display);
		ASSERT_NEQUAL(testSucces, EGL_FALSE);
	}

	display = EGL_NO_DISPLAY;
	context = EGL_NO_CONTEXT;
	surface = EGL_NO_SURFACE;

	return true;
	//DEBUG_INFO(("WindowHandler::CloseDisplay() finished."));
}