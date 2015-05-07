#include <core\Application.h>
#include <core\Log.h>
#include <core\Passert.h>
#include <core\Memory.h>

#include <resources\ResourceManager.h>
#include <core\Time.h>

using namespace pm;
using namespace std;

/////////////////////// Tuukka ///////////////////////
#include <scene\GameEntity.h>
#include <scene\Transformable.h>
#include <resources\TextureFactory.h>
#include <graphics\Rectangle.h>
#include <graphics\Drawable.h>
#include <graphics\SpriteBatch.h>
#include <graphics\Text.h>

void android_main(android_app* application)
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
}