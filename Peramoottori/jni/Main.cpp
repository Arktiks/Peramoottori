#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <core\Application.h>
#include <core\Log.h>
#include <core\Passert.h>
#include <core\Memory.h>
#include <resources\ResourceManager.h>
#include <graphics\SpriteBatch.h>
#include <graphics\Sprite.h>

using namespace pm;


static bool TestFunction()
{
	DEBUG_INFO(("Olen funktio joka palauttaa true :D"));
	return true;
}


std::vector<Sprite*> sprites; // Vector for spritebatch testing.

void initializeSpriteBatch() // Temporary spritebatch test initialization function.
{
	Texture texture("test.png");
	Sprite* sprite = new Sprite(texture);
	Sprite* sprite2 = new Sprite(texture);
	Sprite* sprite3 = new Sprite(texture);
	
	sprite->setPosition(glm::vec2(150, 150));
	sprite->setSize(glm::vec2(100, 100));
	
	sprite->setPosition(glm::vec2(50, 50));
	sprite->setSize(glm::vec2(100, 50));

	sprite->setPosition(glm::vec2(250, 250));
	sprite->setSize(glm::vec2(200, 100));
	
	sprites.push_back(sprite2);
	sprites.push_back(sprite);
	sprites.push_back(sprite3);

	pm::SpriteBatch::GetInstance()->addSprite(sprites[0]);
	pm::SpriteBatch::GetInstance()->addSprite(sprites[1]);
	pm::SpriteBatch::GetInstance()->addSprite(sprites[2]);
}


void android_main(android_app* application)
{
	Application app(application);
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

	//SpriteBatch testing
	initializeSpriteBatch();

	app.AddContextFunction(TestFunction);

	//ResourceManager::GetInstance()->ReadAsset("aani.ogg");
	//ResourceManager::GetInstance()->ReadAsset("test.png");

	/*DEBUG_INFO(("Tassa on numero %i ja stringi %s.", 2, "STRING"));
	//DEBUG_WARNING(("Tama on vain tekstia"));

	//ASSERT(true);
	//ASSERT_EQUAL(true, true);
	//ASSERT_NEQUAL(true, false);
	//ASSERT_MINMAX(2, 4, 5);

	//int* a = NEW int(3);
	//float* b = NEW float(2.2f);
	//double* c = NEW double(2.3333);
	//delete b;
	Memory::WriteLeaks();*/
	
	while (app.Update())
	{
		app.ClearScreen();

		/// MAIN LOOP ///

		app.DrawFrame();
	}
}