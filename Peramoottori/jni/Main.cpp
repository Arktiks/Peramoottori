#include <core\Application.h>
#include <core\Log.h>
#include <core\Passert.h>
#include <core\Memory.h>

#include <resources\ResourceManager.h>
#include <core\Time.h>

using namespace pm;
using namespace std;

/*void android_main(android_app* application)
{
	DEBUG_INFO(("Starting android_main."));

	Application* game = Application::GetInstance(); // For ease of use.
	game->Initialize(application); // Contains loop which makes sure to initialize OpenGL and all modules.

	game->Wait();

	TextResource* txt = (TextResource*)ResourceManager::GetInstance()->LoadAsset("teksti.txt");
	FontResource* font = (FontResource*)ResourceManager::GetInstance()->LoadAsset("arial.ttf");

	Text* teksti = new Text(font, txt, 50, 50, 100, 100);

	//SpriteBatch::GetInstance()->AddGameEntity(teksti->GetGameEntity());
	int i = 0;
	while (game->Update())
	{
		//i++;
		game->window.Clear();
		teksti->GetGameEntity()->GetComponent<Transformable>()->SetRotation(i);
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

namespace pm
{
	class GameClass // Test holding game information.
	{
	public:
		GameClass() : rotation(0.0f)
		{
			objects.push_back(GameEntity());
			objects[0].AddComponent(NEW Transformable(glm::vec2(500.0f, 500.0f), glm::vec2(1.0f, 1.0f), 0.0f));
			objects[0].AddComponent(NEW Color(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)));
			objects[0].AddComponent(TextureFactory::CreateTexture("iiro.png"));
			objects[0].AddComponent(NEW Rectangle(150.0f, 150.0f));
			objects[0].AddComponent(NEW Drawable);
		};

		void Update()
		{
			rotation += 0.1f;
			objects[0].GetComponent<Transformable>()->SetRotation(rotation);
			SpriteBatch::GetInstance()->AddGameEntity(&objects[0]);
			//DEBUG_INFO(("Position: %f, %f", objects[0].GetComponent<Transformable>()->GetPosition().y,
				//objects[0].GetComponent<Transformable>()->GetPosition().y));
		};

		void Draw()
		{
		};

		std::vector<GameEntity> objects;
		float rotation;

		static bool first;
	};

	bool GameClass::first = false;
}
//////////////////////////////////////////////////////

void android_main(android_app* application)
{
	DEBUG_INFO(("Starting android_main."));

	Application* game = Application::GetInstance(); // For ease of use.
	game->Initialize(application); // Contains loop which makes sure to initialize OpenGL and all modules.

	game->Wait();

	if (GameClass::first == false)
	{
		GameClass* g = NEW GameClass;
		game->saveData = (void*)g;
		GameClass::first = true;
	}

	Time time;
	float fps = 0;

	while (game->Update())
	{
		GameClass* access = (GameClass*)game->saveData;
		access->Update();

		//glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

		game->window.Clear();
		game->Draw();
	}

	DEBUG_INFO(("Exiting android_main."));
}