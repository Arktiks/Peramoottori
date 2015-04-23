#include <core\Game.h>
#include <core\Log.h>
#include <core\Passert.h>
#include <core\Memory.h>

#include <EGL\egl.h>
#include <GLES2\gl2.h>
#include <resources\ResourceManager.h>
#include <audio\Audio.h>
#include <graphics\Text.h>


using namespace pm;


/// FOR TESTING PURPOSES ///

#include <core\Time.h>
#include <scene\GameEntity.h>
#include <graphics\RenderSystem.h>
#include <graphics\Rectangle.h>
#include <graphics\SpriteBatch.h>
#include <resources\TextureFactory.h>
#include <graphics\Drawable.h>

static std::vector<GameEntity*> entityVector; // For testing purposes
static float rotation = 0.0f;
static glm::vec2 position = {10.0f, 20.0f};

void InitializeGame();
void UpdateGame();

////////////////////////////


void android_main(android_app* application)
{
	DEBUG_INFO(("Starting android_main."));
	
	Game* game = Game::GetInstance(); // For ease of use.
	bool check = game->Initialize(application); // Contains loop which makes sure to initialize OpenGL and all modules.
	ASSERT(check);

	game->SetClearColor(1.0f, 0.4f, 1.0f);

	InitializeGame();

	Audio audio("test1.ogg");
	audio.Play();

	//ResourceManager::GetInstance()->LoadAsset("test.png");



	Time time;
	float fps = 0;

	while (game->Update())
	{
		fps = (1 / (time.CalculateTimeInFrame() / 1000000000));
		//DEBUG_INFO(("Main.cpp sanoo: fps = %f", fps));

		game->Clear();
		UpdateGame();

		game->Draw();
	}
	
	DEBUG_INFO(("Exiting android_main."));
}

void InitializeGame()
{
	for(int i = 0; i < 10; ++i)
	{
		position += glm::vec2(80.0f, 0.0f);

		GameEntity* entity = NEW GameEntity;

		entity->AddComponent(NEW Rectangle(128, 128));
		entity->GetComponent<Rectangle>()->SetOrigin(32, 32);
	
		entity->AddComponent(NEW Transformable());
		entity->GetComponent<Transformable>()->SetPosition(position);
		entity->GetComponent<Transformable>()->SetRotation(0);
		entity->GetComponent<Transformable>()->SetScale(1, 1);
		
		entity->AddComponent(NEW Drawable());
		entity->GetComponent<Drawable>()->SetDrawState(true);
		
		entity->AddComponent(TextureFactory::CreateTexture("test1.png"));

		entityVector.push_back(entity);
	}
	TextResource* txt = (TextResource*)ResourceManager::GetInstance()->LoadAsset("teksti.txt");
	FontResource* font = (FontResource*)ResourceManager::GetInstance()->LoadAsset("arial.ttf");
	
	Text* teksti = new Text(font, txt, 50, 50, 100, 100);
}

void UpdateGame()
{
	rotation += 1.01;

	for(int i = 0; i < entityVector.size(); i++)
	{
		entityVector[i]->GetComponent<Transformable>()->SetRotation(rotation * 1);

		glm::vec2 oldPosition = entityVector[i]->GetComponent<Transformable>()->GetPosition();

		entityVector[i]->GetComponent<Transformable>()->SetPosition(oldPosition.x, oldPosition.y + 1);

		SpriteBatch::GetInstance()->AddGameEntity(entityVector[i]);
	}
}