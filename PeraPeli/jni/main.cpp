#include <android_native_app_glue.h>
#include <core\Application.h>
#include "GameDemo.h"
#include <chrono>
#include <thread>
using namespace pm;


void android_main(struct android_app* state)
{
	Application* app = Application::GetInstance();
	app->Initialize(state);
	app->Wait();

	if (GameDemo::first == false)
	{
		GameDemo* game = NEW GameDemo;
		game->Initialize();
		app->saveData = (void*)game;
		GameDemo::first = true;
	}

	
	while(app->Update())
	{
		
		GameDemo* access = (GameDemo*)app->saveData;
		
		if (app->IsFocused())
		{
			if (access->paused == true)
				access->Unpause();

			access->Update();
			app->window.Clear();
			app->Draw();
		}
		else
		{
			if (access->paused == false)
				access->Pause();
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
	}

}