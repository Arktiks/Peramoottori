#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <core\Game.h>
#include <core\Log.h>
#include <core\Passert.h>
#include <core\Memory.h>
#include <resources\ResourceManager.h>
#include <audio\Audio.h>
#include <graphics\Text.h>


using namespace pm;

void android_main(android_app* application)
{
	DEBUG_INFO(("Starting android_main."));
	GLuint n = 1;
	SHADER_GL_ERROR((n));
	
	Game* game = Game::GetInstance();
	game->Initialize(application);

	while (!game->IsReady())
		game->Update();

	game->InitializeGame();

	game->SetClearColor(1.0f, 0.4f, 1.0f);

	Audio audio("test1.ogg");
	audio.Play();


	

	//TextResource* teksti = (TextResource*)ResourceManager::GetInstance()->LoadAsset("teksti.txt");
	//FontResource* fontti = (FontResource*)ResourceManager::GetInstance()->LoadAsset("arial.ttf");
	//
	//Text* ntext = NEW Text(fontti, teksti);


	//ResourceManager::GetInstance()->LoadAsset("test.png");

	while (game->Update())
	{
		
		game->Clear();
		//ntext->show_image();
		game->Draw();
	}
	
	DEBUG_INFO(("Exiting android_main."));
}