#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <core\Game.h>
#include <core\Log.h>
#include <core\Passert.h>
#include <core\Memory.h>
#include <resources\ResourceManager.h>

using namespace pm;

void android_main(android_app* application)
{
	DEBUG_INFO(("Starting android_main."));

	Game* game = Game::GetInstance();
	game->Initialize(application);

	while (!game->IsReady())
		game->Update();

	game->SetClearColor(1.0f, 0.4f, 1.0f);

	ResourceManager::GetInstance()->LoadAsset("teksti.txt");
	ResourceManager::GetInstance()->LoadAsset("test.png");

	while (game->Update())
	{
		game->Clear();
		game->Draw();
	}
	
	DEBUG_INFO(("Exiting android_main."));
}