#include "AndroidContext.h"

using namespace PORT;

void processCommand(android_app* application, int command);

Context::Context(android_app* application)
{
	app_dummy();

	FileLoader::getInstance()->setAssetManager(application->activity->assetManager);

	memset(&_engine, 0, sizeof(engine));
	_engine._context = this;
	application->userData = &_engine;
	_engine.app = application;
	_engine.app->onAppCmd = processCommand;

}

void Context::kill()
{
	if (_engine.display != EGL_NO_DISPLAY)
	{
		eglMakeCurrent(_engine.display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if (_engine.context != EGL_NO_CONTEXT)
			eglDestroyContext(_engine.display, _engine.context);
		if (_engine.surface != EGL_NO_SURFACE)
			eglDestroySurface(_engine.display, _engine.surface);

		eglTerminate(_engine.display);
	}

	_engine.display = EGL_NO_DISPLAY;
	_engine.context = EGL_NO_CONTEXT;
	_engine.surface = EGL_NO_SURFACE;
}

void Context::update(android_app* application)
{
	while (ALooper_pollAll(0, NULL, NULL, reinterpret_cast<void**>(&eventSource)) >= 0)
	{
		if (eventSource != nullptr)
			eventSource->process(application, eventSource);

		if (application->destroyRequested != 0)
		{
			kill();
			return;
		}
	}
	draw();
}
void Context::draw()
{
	if (_engine.display == NULL)
		return;

	game->update();
	
	eglSwapBuffers(_engine.display, _engine.surface);
}

void Context::initialize()
{
	const EGLint attributes[] =
	{
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_NONE
	};

	EGLint AttribList[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};
	EGLint dummy, format, numConfigs;

	EGLConfig config;

	_engine.display = eglGetDisplay(EGL_DEFAULT_DISPLAY);


	eglInitialize(_engine.display, 0, 0);

	eglChooseConfig(_engine.display, attributes, &config, 1, &numConfigs);

	eglGetConfigAttrib(_engine.display, config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(_engine.app->window, 0, 0, format);

	_engine.surface = eglCreateWindowSurface(_engine.display, config, _engine.app->window, NULL);

	_engine.context = eglCreateContext(_engine.display, config, NULL, AttribList);


	if (eglMakeCurrent(_engine.display, _engine.surface, _engine.surface, _engine.context) == EGL_FALSE)
	{
		LOG("Unable to eglMakeCurrent");
	}

	eglQuerySurface(_engine.display, _engine.surface, EGL_WIDTH, &_engine.width);
	eglQuerySurface(_engine.display, _engine.surface, EGL_HEIGHT, &_engine.height);


	Shader* shader = Shader::getInstance();
	shader->newShader();

	game = Game::instance();
}

void processCommand(android_app* application, int command)
{
	struct Context::engine* tempEngine2 = (struct Context::engine*)application->userData;

	switch (command)
	{
	case APP_CMD_SAVE_STATE:
		LOG("SAVE STATE");
		break;

	case APP_CMD_INIT_WINDOW:
		LOG("INITIALIZE");
		if (tempEngine2->app->window != NULL)
		{
			tempEngine2->_context->initialize();
			tempEngine2->_context->draw();
		}
		break;

	case APP_CMD_TERM_WINDOW:
		LOG("TERMINATE");
		tempEngine2->_context->kill();
		break;

	case APP_CMD_GAINED_FOCUS:
		LOG("RESUME");
		break;

	case APP_CMD_LOST_FOCUS:
		LOG("PAUSE");
		tempEngine2->_context->draw();
		break;

	default:
		break;
	}
}