#include <core\Application.h>
#include <core\Log.h>
#include <core\Passert.h>
#include <core\Memory.h>

#include <resources\ResourceManager.h>
#include <core\Time.h>
#include <graphics\Text.h>
#include <graphics\SpriteBatch.h>

#include <chrono>
#include <thread>

using namespace pm;
using namespace std;

/*void android_main(android_app* application)
{
	DEBUG_INFO(("Starting android_main."));

	Application* game = Application::GetInstance(); // For ease of use.//
	game->Initialize(application); // Contains loop which makes sure to initialize OpenGL and all modules.

	game->Wait();

	TextResource* txt = (TextResource*)ResourceManager::GetInstance()->LoadAsset("teksti.txt");
	FontResource* font = (FontResource*)ResourceManager::GetInstance()->LoadAsset("ASCII.ttf");

	Text* teksti = new Text(font, txt, 0, 50, 20, 20);

	//SpriteBatch::GetInstance()->AddGameEntity(teksti->GetGameEntity());
	int i = 0;
	while (game->Update())
	{
		//i++;
		game->window.Clear();
		//teksti->GetGameEntity()->GetComponent<Transformable>()->SetRotation(i);
		for (int i = 0; i < teksti->GetTextVector().size(); i++)
			SpriteBatch::GetInstance()->AddGameEntity(teksti->GetTextVector()[i]);

		game->Draw();
	}

	DEBUG_INFO(("Exiting android_main."));
}*/

/////////////////////// Tuukka ///////////////////////
#include <scene\GameEntity.h>
#include <scene\Transformable.h>
#include <resources\TextureFactory.h>
#include <graphics\Rectangle.h>
#include <graphics\Drawable.h>
#include <graphics\SpriteBatch.h>
#include <graphics\Color.h>
#include <audio\Audio.h>
#include <core\Input.h>
#include <core\Time.h>

namespace pm
{
	class GameClass // Test holding game information.
	{
		Time timer;
		Time timer2;
		TextResource* file;
		TextResource* file2;
		FontResource* font;
	public:
		GameClass() : rotation(0.0f), volume(50.0f), paused(false)
		{
			objects.push_back(GameEntity());
			objects[0].AddComponent(NEW Transformable(glm::vec2(500.0f, 500.0f), glm::vec2(1.0f, 1.0f), 0.0f));
			objects[0].AddComponent(NEW Color(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)));
			objects[0].AddComponent(TextureFactory::CreateTexture("DEF_LOGO.png"));
			objects[0].AddComponent(NEW Rectangle(150.0f, 150.0f));
			objects[0].AddComponent(NEW Drawable);

			file = (TextResource*)ResourceManager::GetInstance()->LoadAsset("TEXT.txt");
			file2 = (TextResource*)ResourceManager::GetInstance()->LoadAsset("TEXT2.txt");
			font = (FontResource*)ResourceManager::GetInstance()->LoadAsset("arial.ttf");
			texts.push_back(Text(font, file, 100, 100, 32, 32));

			sounds.push_back(NEW Audio("Midnight_Ride.ogg"));
			sounds[0]->SetLooping(true);
			sounds[0]->SetVolume(volume);
			//sounds[0]->Play();

			sounds.push_back(NEW Audio("Push.ogg"));
			sounds[1]->SetVolume(volume);
		};

		void Update()
		{
			rotation += 0.1f;
			volume -= 0.0f;
			sounds[0]->SetVolume(volume);

			if (input.GetSingleTouch())
			{
				sounds[0]->Stop();
				sounds[0]->PlayFrom(3000);
				texts.at(0).ReText(font, file2, 100, 100, 32, 32);
			}


			objects[0].GetComponent<Transformable>()->SetRotation(rotation);
			SpriteBatch::GetInstance()->AddGameEntity(&objects[0]);
			
			for (int i = 0; i < texts[0].GetTextVector().size(); i++)
				SpriteBatch::GetInstance()->AddGameEntity(texts[0].GetTextVector()[i]);
		};

		void Pause()
		{
			paused = true;
			sounds[0]->Pause();
		};

		void Unpause()
		{
			paused = false;
			sounds[0]->Play();
		};

		std::vector<GameEntity> objects;
		std::vector<Text> texts;
		std::vector<Audio*> sounds;
		float rotation, volume;
		bool paused;
		Input input;
		static bool first;
	};

	bool GameClass::first = false;
}
//////////////////////////////////////////////////////

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
	float fps = 0;

	while (app->Update())
	{
		GameClass* access = (GameClass*)app->saveData;

		if (app->IsFocused())
		{
			if(access->paused == true)
				access->Unpause();

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