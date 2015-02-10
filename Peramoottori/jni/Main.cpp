#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <android/log.h>
#include <android_native_app_glue.h>

#include "Application.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "Info", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "Warning", __VA_ARGS__))


void android_main(android_app* application)
{
	PM::Application app;
	app.Initialize(application);
	while (app.Update())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Main Loop Here //

		LOGI("huiehuehuehiueh");
		/////////////////////

		//Swaps buffers
		app.DrawFrame();
	}

}