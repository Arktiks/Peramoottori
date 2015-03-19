#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <core\Application.h>
#include <core\Log.h>
#include <core\Passert.h>
#include <core\Memory.h>
#include <resources\ResourceManager.h>

using namespace pm;

void android_main(android_app* application)
{
	Application app(application);
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	bool init = true;

	/// MAIN LOOP ///
	while (app.Update())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (init)
		{
			init = false;

			ResourceManager::GetInstance()->ReadAsset("teksti.txt");
			ResourceManager::GetInstance()->ReadAsset("fontti.ttf");
			ResourceManager::GetInstance()->ReadAsset("aani.ogg");
			ResourceManager::GetInstance()->ReadAsset("test.png");

			DEBUG_INFO(("Tassa on numero %i ja stringi %s.", 2, "STRING"));
			DEBUG_WARNING(("Tama on vain tekstia"));

			ASSERT(true);
			ASSERT_EQUAL(true, true);
			ASSERT_NEQUAL(true, false);
			ASSERT_MINMAX(2, 4, 5);

			int* a = NEW int(3);
			float* b = NEW float(2.2f);
			double* c = NEW double(2.3333);
			delete b;
			Memory::WriteLeaks();
		}

		//LOGI("Frame time: %f", frameTime);
		app.DrawFrame(); // Swap buffers.
	}
}