#include <core\Application.h>
#include <core\Log.h>
#include <core\Passert.h>
#include <core\Memory.h>
#include <core\Time.h>
#include <core\Input.h>

#include <resources\ResourceManager.h>
#include <resources\TextureFactory.h>

#include <graphics\Text.h>
#include <graphics\SpriteBatch.h>
#include <graphics\Rectangle.h>
#include <graphics\Drawable.h>
#include <graphics\SpriteBatch.h>
#include <graphics\Color.h>

#include <scene\GameEntity.h>
#include <scene\Transformable.h>
#include <audio\Audio.h>

#include <scene\Physics.h>
#include <scene\PhysicsSystem.h>

#include <chrono>
#include <thread>

using namespace pm;
using namespace std;

namespace pm
{
	class GameClass // Test holding game information.
	{
	public:
		GameClass() : rotation(0.0f), volume(50.0f), paused(false)
		{
			pm::Vector2<int> resolution = Application::GetInstance()->window.GetResolution();
			float location = resolution.x * 0.5f;

			objects.push_back(NEW GameEntity());
			objects[0]->AddComponent(NEW Transformable(glm::vec2(location, 650), glm::vec2(1.0f, 1.0f), 0.0f));
			objects[0]->AddComponent(NEW Color(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)));
			objects[0]->AddComponent(NEW Rectangle(resolution.x, resolution.y * 0.1f));
			objects[0]->AddComponent(TextureFactory::CreateTexture("BOX.png"));
			objects[0]->AddComponent(NEW Drawable);
			objects[0]->AddComponent(NEW Physics);
			objects[0]->GetComponent<Physics>()->SetStatic();
			PhysicsSystem::Instance().AddGameEntity(objects[0]);

			float size = 1.0f;
			float color = 1.0f;
			float rectangle = 200.0f;

			for (int i = 1; i < 10; i++)
			{
				objects.push_back(NEW GameEntity());
				objects[i]->AddComponent(NEW Transformable(glm::vec2(location, 0), glm::vec2(size, size), 0.0f));
				objects[i]->AddComponent(NEW Color(glm::vec4(color, color, color, 1.0f)));
				objects[i]->AddComponent(TextureFactory::CreateTexture("BOX.png"));
				objects[i]->AddComponent(NEW Rectangle(rectangle, rectangle));
				objects[i]->AddComponent(NEW Drawable);
				objects[i]->AddComponent(NEW Physics);

				rectangle -= 10.0f;
				color -= 0.05f;
				PhysicsSystem::Instance().AddGameEntity(objects[i]);
			}
		};

		void Update()
		{
			for (int i = 0; i < objects.size(); i++)
				SpriteBatch::GetInstance()->AddOpaqueGameEntity(objects[i]);

			if(input[0].GetSingleTouch())
			{
				objects.push_back(NEW GameEntity());
				objects.back()->AddComponent(NEW Transformable(glm::vec2(input[0].GetPos().x, input[0].GetPos().y), glm::vec2(1.0f, 1.0f), 0.0f));
				objects.back()->AddComponent(NEW Color(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)));
				objects.back()->AddComponent(NEW Rectangle(100, 100));
				objects.back()->AddComponent(TextureFactory::CreateTexture("BOX.png"));
				objects.back()->AddComponent(NEW Drawable);
				objects.back()->AddComponent(NEW Physics);
				PhysicsSystem::Instance().AddGameEntity(objects.back());
			}
		};

		void Pause()
		{
			paused = true;
		};

		void Unpause()
		{
			paused = false;
		};

		std::vector<GameEntity*> objects;
		float rotation, volume;
		bool paused;
		Input input;
		static bool first;
	};

	bool GameClass::first = false;
}

void android_main(android_app* application)
{
	DEBUG_INFO(("Starting android_main."));

	Application* app = Application::GetInstance(); // For ease of use.
	app->Initialize(application); // Contains loop which makes sure to initialize OpenGL and all modules.
	app->Wait();

	if (GameClass::first == false)
	{
		GameClass* game = NEW GameClass;
		app->saveData = (void*)game;
		GameClass::first = true;
	}

	while (app->Update())
	{
		GameClass* access = (GameClass*)app->saveData;

		if (app->IsFocused())
		{
			if(access->paused == true)
				access->Unpause();

			access->Update();
			PhysicsSystem::Instance().Update();
			app->window.Clear();
			app->Draw();
		}
		else
		{
			if(access->paused == false)
				access->Pause();
	
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			DEBUG_INFO(("Game is not focused."));
		}
	}

	DEBUG_INFO(("Exiting android_main."));
}