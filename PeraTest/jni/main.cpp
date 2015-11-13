#include <core\Application.h>
#include <core\Log.h>
#include <core\Memory.h>
#include <core\Input.h>
#include <core\Time.h>

#include "..\Scene.h"
#include "..\SceneManager.h"
#include "..\Drawables.h"

#include <chrono>
#include <thread>

using namespace pm;
using namespace std;

#define DS manager.GetScene("Drawables")

void android_main(android_app* application)
{
	DEBUG_INFO(("Starting android_main."));

	Application* app = Application::GetInstance(); // For ease of use.
	app->Initialize(application); // Contains loop which makes sure to initialize OpenGL and all modules.
	Input input;
	Time clock;
	clock.Restart();

	SceneManager manager;
	manager.AddScene(NEW Drawables());

	while (app->Update())
	{
		if (app->IsFocused())
		{
			manager.Update();
			app->window.Clear();
			app->Draw();

			if (clock.GetElapsedTime(Time::FRACTION::SECONDS) >= 5.f)
			{
				//manager.DeleteScene("Drawables");
				//manager.AddScene(new Drawables());
				manager.ChangeScene(NEW Drawables());
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