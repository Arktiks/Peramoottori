#include <android_native_app_glue.h>
#include <core\Application.h>
#include "GameDemo.h"

using namespace pm;

static float red = 0.0f;

void android_main(struct android_app* state)
{
	Application::GetInstance()->Initialize(state);

	GameDemo gameDemo;
	gameDemo.Initialize();

	while(Application::GetInstance()->Update())
	{
		gameDemo.Update();

		Application::GetInstance()->window.Clear();
		Application::GetInstance()->Draw();
	}

}