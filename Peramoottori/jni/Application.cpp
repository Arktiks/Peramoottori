#include "Application.h"
#include <jni.h>
#include <errno.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/input.h>

Application::Application()
{
	(this->engine) = new Engine;
}

void Application::Initialize(android_app* application)
{
	//app_dummy(); // Ensures glue code isn't stripped.
	application->onAppCmd = ProcessCommand;
	application->userData = engine;
	application->onInputEvent = HandleInput;
	engine->app = application;
	engine->assetManager = application->activity->assetManager;
	LOGI("Application has been initialized.");
}

bool Application::Update(android_poll_source* eventSource)
{
	while (ALooper_pollAll(0, nullptr, nullptr, reinterpret_cast<void**>(&eventSource)) >= 0)
	{
		if (eventSource != nullptr)
			eventSource->process(engine->app, eventSource);

		if (engine->app->destroyRequested != 0)
		{
			TerminateDisplay();
			return false;
		}
	}

	DrawFrame();
	return true;
}

void Application::ProcessCommand(android_app* application, int command)
{
	switch (command)
	{
	case APP_CMD_RESUME:
		LOGI("RESUME");
		break;

	case APP_CMD_PAUSE:
		LOGI("PAUSE");
		break;

	case APP_CMD_INIT_WINDOW:
		if (engine->app->window != NULL) // The window is being shown, get it ready.
			InitializeDisplay();
		break;

	case APP_CMD_TERM_WINDOW:
		TerminateDisplay(); // The window is being hidden or closed, clean it up.
		break;

	default:
		break;
	}
}

void Application::DrawFrame()
{
	if (engine->display == EGL_NO_DISPLAY)
	{
		// No display.
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	eglSwapBuffers(engine->display, engine->surface);
}

void Application::TerminateDisplay()
{
	LOGI("Terminating the display.");
	if (engine->display != EGL_NO_DISPLAY)
	{
		eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if (engine->context != EGL_NO_CONTEXT)
			eglDestroyContext(engine->display, engine->context);
		if (engine->surface != EGL_NO_SURFACE)
			eglDestroySurface(engine->display, engine->surface);
		eglTerminate(engine->display);
	}

	engine->display = EGL_NO_DISPLAY;
	engine->context = EGL_NO_CONTEXT;
	engine->surface = EGL_NO_SURFACE;
	LOGI("Display has been terminated.");
}

int Application::InitializeDisplay()
{
	LOGI("Initializing display.");
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

	EGLint w, h, dummy, format, numConfigs;
	EGLConfig config;

	EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	eglInitialize(display, 0, 0);
	eglChooseConfig(display, attribs, &config, 1, &numConfigs);
	eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
	ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);

	EGLSurface surface = eglCreateWindowSurface(display, config, engine->app->window, NULL);
	EGLContext context = eglCreateContext(display, config, NULL, attribList);

	if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
	{
		LOGW("Function eglMakeCurrent failed.");
		return -1;
	}

	eglQuerySurface(display, surface, EGL_WIDTH, &w);
	eglQuerySurface(display, surface, EGL_HEIGHT, &h);

	engine->display = display;
	engine->context = context;
	engine->surface = surface;
	engine->width = w;
	engine->height = h;

	/*glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	glClearColor(1.0f, 1.0f, 1.0f, 1);

	LOGI("Succesfully initialized display.");
	return 0;
}

int Application::HandleInput(android_app* application, AInputEvent* event)
{
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
	{
		engine->x = AMotionEvent_getX(event, 0);
		engine->y = AMotionEvent_getY(event, 0);
		LOGI("TOUCH @ (%f, %f)", engine->x, engine->y);
		return 1;
	}
	return 0;
}