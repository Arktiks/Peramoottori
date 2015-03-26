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

void WindowHandler::LoadDisplay(android_app* application)
{
	DEBUG_INFO(("WindowHandler::LoadDisplay() beginning."));

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
	eglInitialize(display, 0, 0);
	eglChooseConfig(display, attribs, &config, 1, &numConfigs);
	eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
	ANativeWindow_setBuffersGeometry(application->window, 0, 0, format);

	EGLSurface surface = eglCreateWindowSurface(display, config, application->window, nullptr);
	EGLContext context = eglCreateContext(display, config, nullptr, attribList);

	// Crash the program if we can't bind context to rendering thread.
	EGLBoolean check = eglMakeCurrent(display, surface, surface, context);
	ASSERT_NEQUAL(check, EGL_FALSE);

	eglQuerySurface(display, surface, EGL_WIDTH, &width);
	eglQuerySurface(display, surface, EGL_HEIGHT, &height);

	// Hold this information in WindowHandle class.
	(this->surface) = surface;
	(this->display) = display;
	(this->context) = context;
	(this->width) = width;
	(this->height) = height;

	glClearColor(1.0f, 0.4f, 1.0f, 1);

	DEBUG_INFO(("WindowHandler::LoadDisplay() ending."));
}

void WindowHandler::CloseDisplay()
{
	DEBUG_INFO(("WindowHandler::CloseDisplay() beginning."));

	if (display != EGL_NO_DISPLAY)
	{
		eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if (context != EGL_NO_CONTEXT)
			eglDestroyContext(display, context);
		if (surface != EGL_NO_SURFACE)
			eglDestroySurface(display, surface);
		eglTerminate(display);
	}

	display = EGL_NO_DISPLAY;
	context = EGL_NO_CONTEXT;
	surface = EGL_NO_SURFACE;

	DEBUG_INFO(("WindowHandler::CloseDisplay() ending."));
}