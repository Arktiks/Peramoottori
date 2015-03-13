#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
//#include <android/log.h>
#include <android_native_app_glue.h>
#include <core\Application.h>

//#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "Info", __VA_ARGS__))
//#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "Warning", __VA_ARGS__))


#include <core\Log.h>
#include <core\Passert.h>
#include <core\Memory.h>


void android_main(android_app* application)
{
	pm::Application app;
	app.Initialize(application);

	bool initialize = true;


	while (app.Update())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Main Loop Here //
		/////////////////////
		if (initialize == true)
		{
			DEBUG_INFO(("tama on tekstia"));
			DEBUG_INFO(("tassa on numeroita %i %i", 2, 3));
			DEBUG_WARNING(("sitten viela varoitus %s", "string"));

			DEBUG_INFO(("eka assert"));
			ASSERT(true);

			DEBUG_INFO(("toka assert"));
			ASSERT_EQUAL(true, true);

			DEBUG_INFO(("kolmas assert"));
			ASSERT_NEQUAL(true, false);

			DEBUG_INFO(("neljas assert"));
			ASSERT_MINMAX(2, 4, 5);

			//DEBUG_INFO(("viides assert"));
			//ASSERT(false);

			int* a = NEW int(3);
			float* b = NEW float(2.2f);
			double* c = NEW double(2.3333);
			delete b;
			pm::Memory::WriteLeaks();

			initialize = false;
		}



		//LOGI("Frame time: %f", frameTime);

		glClearColor(0, 1, 0, 1);

		//Swaps buffers
		app.DrawFrame();
	}

}