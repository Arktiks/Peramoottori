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
#include <graphics\Color.h>
#include <core\Input.h>
#include <core\Time.h>


// For testing purposes
static std::vector<GameEntity*> entityVector; 
static std::vector<GameEntity*> demoEntityVector;
static float rotation = 0.0f;
static glm::vec2 position = {10.0f, 20.0f};
static glm::vec4 touchArea1 = { 0.0f, 512.0f, 256.0f, 256.0f };
static glm::vec4 touchArea2 = { 1024.0f, 512.0f, 256.0f, 256.0f };

Input input;
Time deltaTime;


int touch(glm::vec2 touchPosition);

void InitializeGame();
void UpdateGame();

void InitializeDemo();
void UpdateDemo();

////////////////////////////


void android_main(android_app* application)
{
	DEBUG_INFO(("Starting android_main."));
	
	Game* game = Game::GetInstance(); // For ease of use.
	bool check = game->Initialize(application); // Contains loop which makes sure to initialize OpenGL and all modules.
	ASSERT(check);

	game->SetClearColor(1.0f, 0.4f, 1.0f);

	//InitializeGame();
	InitializeDemo();


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
		//UpdateGame();
		UpdateDemo();

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

void InitializeDemo()
{

	GameEntity* point = NEW GameEntity;

	point->AddComponent(NEW Rectangle(40, 80));

	point->AddComponent(NEW Transformable());
	point->GetComponent<Transformable>()->SetPosition(position);
	point->GetComponent<Transformable>()->SetScale(3, 3);
	point->GetComponent<Transformable>()->SetDepth(0.2f);

	point->AddComponent(NEW Drawable());
	point->GetComponent<Drawable>()->SetDrawState(true);

	point->AddComponent(TextureFactory::CreateTexture("point.png"));
	demoEntityVector.push_back(point);

	glm::vec2 position = glm::vec2(50, 50);

	GameEntity* ground = NEW GameEntity;

	ground->AddComponent(NEW Rectangle(1000, 100));

	ground->AddComponent(NEW Transformable());
	ground->GetComponent<Transformable>()->SetPosition(position);
	ground->GetComponent<Transformable>()->SetRotation(25);


	ground->AddComponent(NEW Drawable());
	ground->GetComponent<Drawable>()->SetDrawState(true);
	ground->GetComponent<Transformable>()->SetDepth(-0.3);
	ground->AddComponent(TextureFactory::CreateTexture("groundTexture.png"));
	demoEntityVector.push_back(ground);


	//initialize areas
	GameEntity* area = NEW GameEntity;

	area->AddComponent(NEW Rectangle(touchArea1[2], touchArea1[3]));

	area->AddComponent(NEW Transformable());
	area->GetComponent<Transformable>()->SetPosition(touchArea1[0], touchArea1[1]);
	area->GetComponent<Transformable>()->SetDepth(-0.3);

	area->AddComponent(NEW Drawable());
	area->GetComponent<Drawable>()->SetDrawState(true);

	area->AddComponent(NEW Color(glm::vec4(0, 0, 1, 0)));
	demoEntityVector.push_back(area);
	

	GameEntity* area2 = NEW GameEntity;

	area2->AddComponent(NEW Rectangle(touchArea2[2], touchArea2[3]));

	area2->AddComponent(NEW Transformable());
	area2->GetComponent<Transformable>()->SetPosition(touchArea2[0], touchArea2[1]);
	area2->GetComponent<Transformable>()->SetDepth(0.6);

	area2->AddComponent(NEW Drawable());
	area2->GetComponent<Drawable>()->SetDrawState(true);

	area2->AddComponent(NEW Color(glm::vec4(0, 0, 1, 0)));
	demoEntityVector.push_back(area2);
	//


	
}

void UpdateDemo()
{	
glm::vec2 touchPosition = input.GetTouchCoordinates();

demoEntityVector[0]->GetComponent<Transformable>()->SetPosition(touchPosition);

int touchArea = touch(touchPosition);

if (touchArea == 1)
{
	demoEntityVector[2]->GetComponent<Color>()->SetColor(glm::vec4(0, 1, 0, 0));
	demoEntityVector[3]->GetComponent<Color>()->SetColor(glm::vec4(1, 0, 0, 0));
}
else if (touchArea == 2)
{
	demoEntityVector[2]->GetComponent<Color>()->SetColor(glm::vec4(1, 0, 0, 0));
	demoEntityVector[3]->GetComponent<Color>()->SetColor(glm::vec4(0, 1, 1, 0));
}

for (int i = 0; i < demoEntityVector.size(); i++)
{
	SpriteBatch::GetInstance()->AddGameEntity(demoEntityVector[i]);
}

}

int touch(glm::vec2 touchPosition)
{

	if (touchPosition[0] > touchArea1[0] && touchPosition[0] < touchArea1[0] + touchArea1[2] &&
		touchPosition[1] > touchArea1[1] && touchPosition[1] < touchArea1[1] + touchArea1[3])
		return 1;

	else if (touchPosition[0] > touchArea2[0] && touchPosition[0] < touchArea2[0] + touchArea2[2] &&
		touchPosition[1] > touchArea2[1] && touchPosition[1] < touchArea2[1] + touchArea2[3])
		return 2;
	else
		return 0;
}