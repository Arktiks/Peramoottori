#include <android/asset_manager.h>
#include <android/input.h>
#include <android/log.h>
#include <android_native_app_glue.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include "Application.h"

#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "Default", __VA_ARGS__)

void Application::application()
{


}
static void Application::init(android_app* application)
{
	application->onAppCmd = processCommand;
	application->userData = &engine;
	application->onInputEvent = handleInput;
	engine.app = application;
	engine.assetManager = application->activity->assetManager;

}

static bool Application::update()
{
	while (ALooper_pollAll(0, nullptr, nullptr, reinterpret_cast<void**>(&eventSource)) >= 0)
	{
		if (eventSource != 0)
		{
			eventSource->process(application, eventSource);
		}
		if (application->destroyRequested != 0)
		{
			return false;
		}
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawFrame();
	return true;
}

static void Application::processCommand(int command)
{
	switch (command)
	{
	case APP_CMD_RESUME:
		LOG("RESUME");
		break;
	case APP_CMD_PAUSE:
		LOG("PAUSE");
		break;
	case APP_CMD_INIT_WINDOW:
		// The window is being shown, get it ready.
		if (engine->app->window != NULL) {
			initializeDisplay(engine);
		}
		break;
	case APP_CMD_TERM_WINDOW:
		// The window is being hidden or closed, clean it up.
		//redo
		terminateDisplay(engine);
		break;
	default:
		break;
	}
}

static void Application::drawFrame()
{
	if (engine->display == NULL) {
		// No display.
		return;
	}

	eglSwapBuffers(engine->display, engine->surface);
}

static void Application::terminateDisplay()
{
	LOG("TERMINATE DISPLAY");
	if (engine->display != EGL_NO_DISPLAY) {
		eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if (engine->context != EGL_NO_CONTEXT) {
			eglDestroyContext(engine->display, engine->context);
		}
		if (engine->surface != EGL_NO_SURFACE) {
			eglDestroySurface(engine->display, engine->surface);
		}
		eglTerminate(engine->display);
	}
	engine->display = EGL_NO_DISPLAY;
	engine->context = EGL_NO_CONTEXT;
	engine->surface = EGL_NO_SURFACE;
}

static int Application::initializeDisplay()
{

	LOG("INITIALIZE DISPLAY");
	const EGLint attribs[] = {
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
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
	EGLint w, h, dummy, format;
	EGLConfig config;
	EGLint numConfigs;

	EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	eglInitialize(display, 0, 0);
	eglChooseConfig(display, attribs, &config, 1, &numConfigs);
	eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
	ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);

	EGLSurface surface = eglCreateWindowSurface(display, config, engine->app->window, NULL);


	EGLContext context = eglCreateContext(display, config, NULL, attribList);

	if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
	{
		LOG("Func eglMakeCurrent failed");
		return -1;
	}

	eglQuerySurface(display, surface, EGL_WIDTH, &w);
	eglQuerySurface(display, surface, EGL_HEIGHT, &h);

	engine->display = display;
	engine->context = context;
	engine->surface = surface;
	engine->width = w;
	engine->height = h;

	glClearColor(1.0f, 1.0f, 1.0f, 1);

	return 0;

}

static int Application::handleInput(AInputEvent* event)
{
	if (AInputEvent_getType(inputEvent) == AINPUT_EVENT_TYPE_MOTION)
	{
		engine->state.x = AMotionEvent_getX(inputEvent, 0);
		engine->state.y = AMotionEvent_getY(inputEvent, 0);

		return 1;
	}
	return 0;

}
