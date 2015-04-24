#include <android_native_app_glue.h>
#include <core\Application.h>

using namespace pm;

static float red = 0.0f;

void android_main(struct android_app* state)
{
	Application::GetInstance()->Initialize(state);

	while(Application::GetInstance()->Update())
	{
		if (red < 255.0f)
			red += 1.0f;
		else
			red = 0.0f;

		Application::GetInstance()->window.SetClearColor(red, 0.f, 1.f);

		Application::GetInstance()->window.Clear();
		Application::GetInstance()->Draw();
	}

}