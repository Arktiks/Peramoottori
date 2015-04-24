#include "WindowHandler.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <core/Log.h>
#include <core/Passert.h>

using namespace pm;
using namespace std;

Vector2<int> WindowHandler::GetResolution()
{
	if(Warning(__func__))
		return Vector2<int>(0, 0);
	else
		return Vector2<int>(width, height);
}

void WindowHandler::Clear()
{
	if(Warning(__func__))
		return;

	DEBUG_GL_ERROR_CLEAR();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DEBUG_GL_ERROR();
}

void WindowHandler::SetClearColor(float red, float green, float blue)
{
	if(Warning(__func__))
		return;

	DEBUG_GL_ERROR_CLEAR();
	glClearColor(red, green, blue, 1.0f);
	DEBUG_GL_ERROR();
}

void WindowHandler::SwapBuffers()
{
	if(Warning(__func__))
		return;

	DEBUG_GL_ERROR_CLEAR();
	if(eglSwapBuffers(display, surface) == EGL_FALSE)
		DEBUG_WARNING(("Couldn't swap buffers."));
	DEBUG_GL_ERROR();
}

bool WindowHandler::HasContext()
{
	if (context != EGL_NO_CONTEXT)
		return true;
	else
		return false;
}

bool WindowHandler::LoadDisplay(android_app* application)
{
	DEBUG_GL_ERROR_CLEAR();

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
	DEBUG_GL_ERROR();

	bool testSucces = eglInitialize(display, 0, 0);
	DEBUG_GL_ERROR();
	ASSERT_NEQUAL(testSucces, EGL_FALSE);

	testSucces = eglChooseConfig(display, attribs, &config, 1, &numConfigs);
	DEBUG_GL_ERROR();
	ASSERT_NEQUAL(testSucces, EGL_FALSE);

	testSucces = eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
	DEBUG_GL_ERROR();
	ASSERT_NEQUAL(testSucces, EGL_FALSE);

	ANativeWindow_setBuffersGeometry(application->window, 0, 0, format);

	EGLSurface surface = eglCreateWindowSurface(display, config, application->window, nullptr);
	DEBUG_GL_ERROR();
	ASSERT_NEQUAL(surface, EGL_NO_SURFACE);

	EGLContext context = eglCreateContext(display, config, nullptr, attribList);
	DEBUG_GL_ERROR();
	ASSERT_NEQUAL(context, EGL_NO_CONTEXT);

	testSucces = eglMakeCurrent(display, surface, surface, context); // Crash the program if we can't bind context to rendering thread.
	DEBUG_GL_ERROR();
	ASSERT_NEQUAL(testSucces, EGL_FALSE);

	eglQuerySurface(display, surface, EGL_WIDTH, &width);
	DEBUG_GL_ERROR();
	ASSERT_NEQUAL(width, 0);

	eglQuerySurface(display, surface, EGL_HEIGHT, &height);
	DEBUG_GL_ERROR();
	ASSERT_NEQUAL(height, 0);

	// Hold this information in WindowHandler.
	(this->surface) = surface;
	(this->display) = display;
	(this->context) = context;
	(this->width) = width;
	(this->height) = height;

	return true;
}

bool WindowHandler::CloseDisplay()
{
	if (display != EGL_NO_DISPLAY)
	{
		DEBUG_GL_ERROR_CLEAR();

		bool testSucces = eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		DEBUG_GL_ERROR();
		ASSERT_NEQUAL(testSucces, EGL_FALSE);

		if (context != EGL_NO_CONTEXT)
		{
			testSucces = eglDestroyContext(display, context);
			DEBUG_GL_ERROR();
			ASSERT_NEQUAL(testSucces, EGL_FALSE);
		}

		if (surface != EGL_NO_SURFACE)
		{
			testSucces = eglDestroySurface(display, surface);
			DEBUG_GL_ERROR();
			ASSERT_NEQUAL(testSucces, EGL_FALSE);
		}

		testSucces = eglTerminate(display);
		DEBUG_GL_ERROR();
		ASSERT_NEQUAL(testSucces, EGL_FALSE);
	}

	display = EGL_NO_DISPLAY;
	context = EGL_NO_CONTEXT;
	surface = EGL_NO_SURFACE;

	return true;
}

bool WindowHandler::Warning(string function)
{
	if(!HasContext())
	{
		DEBUG_WARNING(("Device context is not ready - ending %s prematurely.", function.c_str()));
		return true;
	}
	else
		return false;
}