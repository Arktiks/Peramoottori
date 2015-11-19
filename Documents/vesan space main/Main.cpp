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

#include <scene\Name.h>
#include <scene\GameEntity.h>
#include <scene\Transformable.h>
#include <audio\Audio.h>

#include <chrono>
#include <thread>

using namespace pm;
using namespace std;
bool asd = 1;


namespace pm
{
	class GameClass // Test holding game information.
	{
	public:
		void CreateGameObjects(std::string name, std::string filepath, glm::vec2 size, glm::vec2 position, int amount, int depth, float rotation);
		GameClass() : rotation(0.0f), volume(50.0f), paused(false)
		{
			
			pm::Input input;

			GameEntity* background = NEW GameEntity();
			objects.push_back(background);
			background->AddComponent(NEW Rectangle(1200, 1000));
			background->AddComponent(NEW Transformable(glm::vec2(0, 0), glm::vec2(1, 1), 0.0f));
			background->AddComponent(NEW Color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
			background->AddComponent(NEW Texture("space/background.png"));
			background->AddComponent(NEW Drawable);
			background->AddComponent(NEW Name("background"));
			background->GetComponent<Transformable>()->SetDepth(0);
			
			CreateGameObjects("galaxy", "space/galaxy.png", glm::vec2(300, 300),		glm::vec2(125, 200), 7, 2, 0);
			CreateGameObjects("hero", "space/hero.png", glm::vec2(100, 400),			glm::vec2(0, 225), 2, 4, -3);
			CreateGameObjects("spaceship", "space/spaceship.png", glm::vec2(100, 75),	glm::vec2(600, 0), 15, 5,-90);
			CreateGameObjects("stars", "space/stars.png", glm::vec2(1000, 1000),		glm::vec2(0, 0), 1,2, 0);
			CreateGameObjects("stars", "space/stars.png", glm::vec2(1000, 1000),		glm::vec2(0, 0), 1,2, 180);
			CreateGameObjects("rospot", "space/rospot.png", glm::vec2(100, 100),		glm::vec2(325, 310), 4, 3, 3);
			
		
			sounds.push_back(NEW Audio("Push.ogg"));
			sounds[0]->SetVolume(volume);
		};

		void Update()
		{
			rotation += 0.1f;

			for (int i = 0; i < objects.size(); i++)
			{
				if (objects[i]->GetComponent<Name>() != nullptr)
				{
					glm::vec2 position = objects[i]->GetComponent<Transformable>()->GetPosition();

					if (objects[i]->GetComponent<Name>()->GetName() == "galaxy")
					{
						if (position.x > 1000)
							objects[i]->GetComponent<Transformable>()->SetPosition(0,position.y);
						else
							objects[i]->GetComponent<Transformable>()->SetPosition(position.x + 1, position.y);
					}
					else if (objects[i]->GetComponent<Name>()->GetName() == "hero")
					{

						if (position.x < 0)
							objects[i]->GetComponent<Transformable>()->SetPosition(1000, position.y);
						else
							objects[i]->GetComponent<Transformable>()->SetPosition(position.x - 2, position.y);
					}
					else if (objects[i]->GetComponent<Name>()->GetName() == "spaceship")
					{

						if (position.y > 1000)
							objects[i]->GetComponent<Transformable>()->SetPosition(position.x, 0);
						else
							objects[i]->GetComponent<Transformable>()->SetPosition(position.x, position.y+1.5);
					}
					else if (objects[i]->GetComponent<Name>()->GetName() == "stars")
					{

						if (position.x > 1000)
							objects[i]->GetComponent<Transformable>()->SetPosition(0, position.y);
						else
							objects[i]->GetComponent<Transformable>()->SetPosition(position.x + 0.3, position.y);
					}
					else if (objects[i]->GetComponent<Name>()->GetName() == "rospot")
					{

						if (position.y < 0)
							objects[i]->GetComponent<Transformable>()->SetPosition(position.x, 1000);
						else
							objects[i]->GetComponent<Transformable>()->SetPosition(position.x, position.y-2);
					}
				}

			}


			if (input[0].IsTouching() == true)
			{
			
			}
			if (input[0].IsTouching() == false)
			{

			}

			for (int i = 0; i < objects.size(); i++)
			{
				if (objects[i]->GetComponent<Name>()->GetName() != "background")
				SpriteBatch::GetInstance()->AddTranslucentGameEntity(objects[i]);
				else
				SpriteBatch::GetInstance()->AddOpaqueGameEntity(objects[i]);

			}
			
			
		};

		void Pause()
		{
			paused = true;
			//sounds[0]->Pause();
		};

		void Unpause()
		{
			paused = false;
			//sounds[0]->Play();
		};

		std::vector<GameEntity*> objects;
		std::vector<Audio*> sounds;
		float rotation, volume;
		bool paused;
		Input input;
		static bool first;
	};

	bool GameClass::first = false;
}

void GameClass::CreateGameObjects(std::string name, std::string filepath, glm::vec2 size, glm::vec2 position, int amount, int depth, float rotation)
{
	for (int i = 0; i < amount; i++)
	{
		GameEntity* gaga = NEW GameEntity();
		objects.push_back(gaga);
		gaga->AddComponent(NEW Transformable(position, glm::vec2(1, 1), rotation));
		gaga->GetComponent<Transformable>()->SetDepth(depth);
		gaga->AddComponent(NEW Color(glm::vec4(1, 1, 1.0f, 1.0f)));

		gaga->AddComponent(NEW Texture(filepath));

		gaga->AddComponent(NEW Rectangle(size.x + i * 200, size.y + i * 200));
		gaga->AddComponent(NEW Drawable);
		gaga->AddComponent(NEW Name(name));
	}
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

	Time time;
	int timer = 0;

	while (app->Update())
	{
		GameClass* access = (GameClass*)app->saveData;

		if (app->IsFocused())
		{
			if (access->paused == true)
				access->Unpause();

			timer += 1;

			if (timer >= 300 && timer < 350)
			{


				//access->objects[4]->GetComponent<Drawable>()->SetDrawState(false);
				//access->objects[2]->RemoveComponent<Texture>();
				timer = 351;
			}

			access->Update();
			app->window.Clear();
			app->Draw();
		}
		else
		{
			if (access->paused == false)
				access->Pause();

			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			DEBUG_INFO(("Game is not focused."));
		}
	}

	DEBUG_INFO(("Exiting android_main."));
}