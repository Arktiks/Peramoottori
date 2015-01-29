#ifndef ANDROIDCONTEXT_H
#define ANDROIDCONTEXT_H

#include <android/log.h>
#include <android_native_app_glue.h>
#include <android/asset_manager.h>
#include <EGL\egl.h>
#include <GLES2\gl2.h>
#include "Shader.h"

#include "Game.h"
#include "FileLoader.h"

#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "NativeSample", __VA_ARGS__)

namespace PORT
{
	class Context
	{
	public:
		Context(android_app* application);

		void update(android_app* application);

		struct engine
		{
			struct android_app* app;

			EGLDisplay display;
			EGLSurface surface;
			EGLContext context;
			int32_t width;
			int32_t height;
			Context* _context;
		};

		void initialize();
		void draw();
		void kill();

	private:

		android_poll_source* eventSource;

		Game* game;

		engine _engine;

	};
}
#endif