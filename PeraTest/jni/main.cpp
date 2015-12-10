#include <core\Application.h>
#include <core\Log.h>
#include <core\Memory.h>
#include <core\Input.h>
#include <core\Time.h>

#include "..\Scene.h"
#include "..\SceneManager.h"
#include "..\Drawables.h"
#include "..\Texts.h"
#include "..\Input.h"
#include "..\Audio.h"

#include "..\pmScene.h"
#include <scene\Scene.h>

#include <chrono>
#include <thread>

using namespace std;

void altMain(android_app *application);
int sceneSelection = 1;

void android_main(android_app* application)
{
	if (sceneSelection == 1)
		altMain(application);

	DEBUG_INFO(("Starting android_main."));
	pm::Application* app = pm::Application::GetInstance(); // For ease of use.
	app->Initialize(application); // Contains loop which makes sure to initialize OpenGL and all modules.

	pm::Time clock;
	clock.Restart();

	SceneManager manager;
	manager.AddScene(NEW Texts());
	manager.AddScene(NEW Drawables());
	manager.AddScene(NEW Input());
	manager.AddScene(NEW Audio());

	while (app->Update())
	{
		if (app->IsFocused())
		{
			manager.Update();
			app->window.Clear();
			app->Draw();

			if (clock.GetElapsedTime(pm::Time::FRACTION::SECONDS) >= 10.f)
			{
				Audio* audio = (Audio*)manager.GetScene("Audio");

				if (audio->pause)
					audio->Resume();
				else
					audio->Pause();

				if(manager.GetScene("Texts") != nullptr)
					manager.DeleteScene("Texts");

				//manager.AddScene(new Texts());
				
				clock.Restart();
			}
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			DEBUG_INFO(("Game is not focused."));
		}
	}

	DEBUG_INFO(("Exiting android_main."));
}

void altMain(android_app *application)
{
	DEBUG_INFO(("Starting android_altMain."));
	pm::Application* app = pm::Application::GetInstance(); // For ease of use.
	app->Initialize(application); // Contains loop which makes sure to initialize OpenGL and all modules.

	pmScene scene;
	while (app->Update())
	{
		if (app->IsFocused())
		{
			scene.Update();
			app->window.Clear();
			app->Draw();
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			DEBUG_INFO(("Game is not focused."));
		}
	}

	DEBUG_INFO(("Exiting android_altMain."));
}