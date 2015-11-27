/** \cond HIDDEN_SYMBOLS */

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
			float location = 50.0f;
			float size = 1.0f;
			float color = 0.3f;
			float rectangle = 200.0f;

			for (int i = 0; i < 2; i++)
			{

				//scene->createobject("nimi");

				//scene->deleteobject();

				objects.push_back(NEW GameEntity());
				objects[i]->AddComponent(NEW Transformable(glm::vec2(location, location), glm::vec2(size, size), 0.0f));
				objects[i]->AddComponent(NEW Color(glm::vec4(color*i, color*i, color, 1.0f)));

				//if((i % 2) == 0)
					objects[i]->AddComponent(NEW Texture("DEF_TEXTURE_SMALL.png"));
				//else						
					objects[i]->AddComponent(NEW Texture("DEF_TEXTURE.png"));

				objects[i]->AddComponent(NEW Rectangle(rectangle, rectangle));
				objects[i]->AddComponent(NEW Drawable);

				rectangle -= 30.0f;
				location += 150.0f;
				size -= 0.1f;
				color -= 0.2f;
			}
			objects[0]->GetComponent<Transformable>()->SetDepth(2);
			objects[1]->GetComponent<Transformable>()->SetDepth(1);
			/*TextResource* file = (TextResource*)ResourceManager::GetInstance()->LoadAsset("TEXT.txt");
			FontResource* font = (FontResource*)ResourceManager::GetInstance()->LoadAsset("arial.ttf");
			texts.push_back(Text(font, file, 100, 100, 32, 32));*/

			/*sounds.push_back(NEW Audio("Midnight_Ride.ogg"));
			sounds[0]->SetLooping(true);
			sounds[0]->SetVolume(volume);
			sounds[0]->Play();*/

			sounds.push_back(NEW Audio("Push.ogg"));
			sounds[0]->SetVolume(volume);
		};

		void Update()
		{
			rotation += 0.1f;
			//objects[0]->GetComponent<Transformable>()->SetDepth(-objects[0]->GetComponent<Transformable>()->GetDepth());
			//objects[1]->GetComponent<Transformable>()->SetDepth(-objects[0]->GetComponent<Transformable>()->GetDepth());
			for (int i = 0; i < 2; i++)
			{
				//objects[i]->GetComponent<Transformable>()->SetRotation(rotation);
				SpriteBatch::GetInstance()->AddTranslucentGameEntity(objects[i]);
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
			if(access->paused == true)
				access->Unpause();

			timer += 1;

			if (timer >= 300 && timer < 350)
			{
				access->objects[0]->GetComponent<Transformable>()->SetDepth(1);
				access->objects[1]->GetComponent<Transformable>()->SetDepth(2);
				
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
			if(access->paused == false)
				access->Pause();
	
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			DEBUG_INFO(("Game is not focused."));
		}
	}

	DEBUG_INFO(("Exiting android_main."));
}

/** \endcond */