#include "pmScene.h"
#include <audio\Audio.h>
#include <core\Time.h>
#include <core\Vector2.h>
#include "GameEntityFactory.h"
pmScene::pmScene()
{
	pm::Application* app = pm::Application::GetInstance();
	spriteBatch = pm::SpriteBatch::GetInstance();
	time.Start();

	glm::vec2 asd = app->window.GetResolution();
	limits.x = asd.x;
	limits.y = asd.y;

	physicsManager = PhysicsManager(limits, 0.01);
	gameEntityFactory = NEW GameEntityFactory(this);

	InitializeResources();
	InitializeGameEntities();

	pm::Audio* audio = NEW pm::Audio("space/AvaruusMusiikki.ogg");
	audio->SetLooping(true);
	audio->Play();
	
	heroTime = 0;
	cameraZoom = 1;
	pm::CameraSystem::GetInstance()->SetActiveCamera(&camera);
	direction = 1;
	
}

pmScene::~pmScene()
{
}

void pmScene::InitializeResources()
{
	pmScene::AddTexture("space/background.png");
	pmScene::AddTexture("space/hero.png");
	pmScene::AddTexture("space/rospot.png");
}


void pmScene::InitializeGameEntities()
{
	pm::GameEntity* background = NEW pm::GameEntity();
	background->AddComponent(GetTexture("space/background.png"));
	background->AddComponent(NEW pm::Name("background"));
	background->AddComponent(NEW pm::Transformable(glm::vec2(0, 0), glm::vec2(1, 1), 0));
	background->AddComponent(NEW pm::Rectangle(1280, 720));
	background->AddComponent(NEW pm::Drawable);
	background->AddComponent(NEW pm::Color(glm::vec4(1, 1, 1, 1)));
	background->GetComponent<pm::Transformable>()->SetDepth(1);
	AddGameEntity(background);

	gameEntityFactory->CreateHero(glm::vec2(300, 300), 2, glm::vec2(200, 400), glm::vec2(100, 30), 0.1);
	gameEntityFactory->CreateHero(glm::vec2(600, 500), 3, glm::vec2(150, 300), glm::vec2(205, 125), 0.05);
	gameEntityFactory->CreateHero(glm::vec2(100, 200), 4, glm::vec2(100, 200), glm::vec2(50, 50), 0.01);
	gameEntityFactory->CreateRospot(glm::vec2(300, 200), 5, glm::vec2(200, 200), glm::vec2(60, 0));
	gameEntityFactory->CreateButton(glm::vec2(500, 500), 5, glm::vec2(200, 200));
	gameEntityFactory->CreateMovingOpaque("space/opaqueTest.png", glm::vec2(500, 500), 4, glm::vec2(200, 200), glm::vec2(0.5, 0.2));
	gameEntityFactory->CreateMovingOpaque("space/opaqueTest.png", glm::vec2(333, 500), 2, glm::vec2(220, 200), glm::vec2(0.2, 0.5));
	gameEntityFactory->CreateMovingOpaque("space/opaqueTest2.png", glm::vec2(500, 333), 6, glm::vec2(200, 220), glm::vec2(0.0, 0.2));
	gameEntityFactory->CreateMovingOpaque("space/opaqueTest3.png", glm::vec2(200, 100), 1, glm::vec2(200, 300), glm::vec2(0.2, 0.5));

}
void pmScene::Update()
{
	float frameTime = time.Restart(pm::Time::FRACTION::SECONDS);
	UpdateGameEntities(frameTime);
	
	if (direction == 1)
	{
		if (cameraZoom > 0.2)
			cameraZoom -= 0.001;
		else
			direction = -1;
	}
	else
	{
		if (cameraZoom < 1.2)
			cameraZoom += 0.001;
		else
			direction = 1;
	}
	
		
	camera.SetCameraZoom(cameraZoom);
	Draw();
}
void pmScene::UpdateGameEntities(float time)
{
	pm::GameEntity* gameEntity;
	heroTime += time;
	for (int i = 0; i < animGEVector.size(); i++)
	{
		gameEntity = animGEVector[i];
		UpdateRate* updateRate = gameEntity->GetComponent<UpdateRate>();
		updateRate->time += time;

		if (updateRate->time > updateRate->updateRate)
		{
			UpdateAnimation(gameEntity);
			UpdateScaleRotation(gameEntity);
			updateRate->time = 0;
		}
	}
	if (heroTime > 1)
	{
		physicsManager.AddForceToHeroes(glm::vec2(2, 2));
		heroTime = 0;
	}
	physicsManager.Update(time);

	
	for (int i = 0; i < gameEntityVector.size(); i++)
	{
		if (gameEntityVector[i]->GetComponent<pm::Name>() != nullptr)
		{
			if (gameEntityVector[i]->GetComponent<pm::Name>()->GetName() == "rospot")
			{
				camera.SetCameraPosition(glm::vec2(gameEntityVector[i]->GetComponent<pm::Transformable>()->GetPosition().x -
					limits.x/2,
					gameEntityVector[i]->GetComponent<pm::Transformable>()->GetPosition().y - limits.y / 2));
			}
			if (gameEntityVector[i]->GetComponent<pm::Name>()->GetName() == "button")
			{
			
				if (input[0].IsTouching())
				{
					if (gameEntityVector[i]->GetComponent<pm::Hitbox>()->CheckCollision(input[0].GetPos()))
						ButtonPress(gameEntityVector[i]);
				}
						
			}

		}
	}
}

void pmScene::ButtonPress(pm::GameEntity* gameEntity)
{
	pm::Color* color = gameEntity->GetComponent <pm::Color>();

	if (color->GetColor() == glm::vec4(1, 0.5, 1, 1))
	{
		color->SetColor(glm::vec4(0.5, 1, 1, 1));
	}
	else
	{
		color->SetColor(glm::vec4(1, 0.5, 1, 1));
	}
	
}

void pmScene::UpdateAnimation(pm::GameEntity* gameEntity)
{
	pm::GameEntity* GE = gameEntity;
	Animation* anime = GE->GetComponent<Animation>();

	pm::TextureCoordinates* texC = GE->GetComponent<pm::TextureCoordinates>();
	glm::vec4 coordinates;

	if (anime->animationFrame >= anime->frameAmount - 1)
		anime->frameDir = -1;

	else if (anime->animationFrame <= 0)
		anime->frameDir = 1;

	anime->animationFrame += anime->frameDir;
	texC->SetTextureCoordinates(anime->animationCoordinates[anime->animationFrame]);
	
	
}

void pmScene::UpdateScaleRotation(pm::GameEntity* gameEntity)
{
	Animation* anime = gameEntity->GetComponent<Animation>();
	pm::Transformable* transformable = gameEntity->GetComponent<pm::Transformable>();
	transformable->SetRotation(transformable->GetRotation()-1);

	float currentScale = transformable->GetScale().x;
	if (currentScale > 1.5)
		anime->scaleDir = -0.05;
	else if (currentScale < 0.5)
		anime->scaleDir = 0.05;

	transformable->SetScale(glm::vec2(transformable->GetScale().x + anime->scaleDir,
		transformable->GetScale().y + anime->scaleDir));
}



void pmScene::AddAnimationGameEntity(pm::GameEntity* gameEntity)
{
	Scene::AddGameEntity(gameEntity);
	
	animGEVector.push_back(gameEntity);


}
void pmScene::RemoveDrawableGameEntity(pm::GameEntity* gameEntity)
{
	RemoveGameEntity(gameEntity);
}