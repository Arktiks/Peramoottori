#include "pmScene.h"
#include <audio\Audio.h>
#include <core\Time.h>
#include <core\Vector2.h>
pmScene::pmScene()
{
	pm::Application* app = pm::Application::GetInstance();
	spriteBatch = pm::SpriteBatch::GetInstance();
	time.Start();

	InitializeResources();
	InitializeGameEntities();

	pm::Audio* audio = NEW pm::Audio("space/AvaruusMusiikki.ogg");
	audio->SetLooping(true);
	audio->Play();

	pm::Vector2<int> asd =app->window.GetResolution();

	limits.x = asd.x;
	limits.y = asd.y;
	physicsManager = PhysicsManager(limits, 0.01);
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
	pm::GameEntity* ge = NEW pm::GameEntity();
	ge->AddComponent(GetTexture("space/background.png"));
	ge->AddComponent(NEW pm::Transformable(glm::vec2(0, 0), glm::vec2(1,1),0));
	ge->AddComponent(NEW pm::Rectangle(1280,720));
	ge->AddComponent(NEW pm::Drawable);
	ge->AddComponent(NEW pm::Color(glm::vec4(1,1,1,1)));
	ge->GetComponent<pm::Transformable>()->SetDepth(1);
	AddGameEntity(ge, OPAQUE);

	pm::GameEntity* ge2 = NEW pm::GameEntity();
	ge2->AddComponent(GetTexture("space/hero.png"));
	ge2->AddComponent(NEW pm::Transformable(glm::vec2(400, 600), glm::vec2(1, 1), 30));
	ge2->GetComponent<pm::Transformable>()->SetDepth(2);
	ge2->AddComponent(NEW pm::Rectangle(125, 250));
	ge2->GetComponent<pm::Rectangle>()->SetOrigin(62.5, 125);
	ge2->AddComponent(NEW pm::Drawable);
	ge2->AddComponent(NEW pm::TextureCoordinates);
	ge2->GetComponent<pm::TextureCoordinates>()->SetTextureCoordinates(0, 0, 140, 230);
	ge2->AddComponent(NEW pm::Color(glm::vec4(0.8,0.8,0.8,0.8)));
	ge2->AddComponent(NEW Animation(0.3));
	ge2->GetComponent<Animation>()->SetValues(140,230,0,14,7,2);
	ge2->GetComponent<Animation>()->GenerateCoords();
	ge2->AddComponent(NEW Physics(glm::vec2(3, 4)));
	physicsManager.AddPhysics(ge2);
	AddGameEntity(ge2, TRANSLUCENT);
	animGEVector.push_back(ge2);
	

	pm::GameEntity* ge3 = NEW pm::GameEntity();
	ge3->AddComponent(GetTexture("space/hero.png"));
	ge3->AddComponent(NEW pm::Transformable(glm::vec2(600, 400), glm::vec2(1, 1), -10));
	ge3->AddComponent(NEW pm::Rectangle(100, 200));
	ge3->GetComponent<pm::Rectangle>()->SetOrigin(50, 100);
	ge3->AddComponent(NEW pm::Drawable);
	ge3->AddComponent(NEW pm::TextureCoordinates);
	ge3->GetComponent<pm::TextureCoordinates>()->SetTextureCoordinates(0, 0, 140, 230);
	ge3->AddComponent(NEW pm::Color(glm::vec4(1, 1, 1, 1)));
	ge3->GetComponent<pm::Transformable>()->SetDepth(2);
	ge3->AddComponent(NEW Animation(0.5));
	ge3->GetComponent<Animation>()->SetValues(140, 230, 0, 14, 7, 2);
	ge3->GetComponent<Animation>()->GenerateCoords();
	ge3->AddComponent(NEW Physics(glm::vec2(-2, 1)));
	physicsManager.AddPhysics(ge3);
	AddGameEntity(ge3, TRANSLUCENT);
	animGEVector.push_back(ge3);

	pm::GameEntity* ge4 = NEW pm::GameEntity();
	ge4->AddComponent(GetTexture("space/hero.png"));
	ge4->AddComponent(NEW pm::Transformable(glm::vec2(500,500),glm::vec2(1,1),10));
	ge4->AddComponent(NEW pm::Rectangle(300,300));
	ge4->GetComponent<pm::Rectangle>()->SetOrigin(150, 150);
	ge4->AddComponent(NEW pm::Drawable);
	ge4->AddComponent(NEW pm::TextureCoordinates);
	ge4->GetComponent<pm::TextureCoordinates>()->SetTextureCoordinates(0, 0, 140, 230);
	ge4->GetComponent<pm::Transformable>()->SetDepth(2);
	ge4->AddComponent(NEW Animation(0.1));
	ge4->GetComponent<Animation>()->SetValues(140, 230, 0, 14, 7, 2);
	ge4->GetComponent<Animation>()->GenerateCoords();
	ge4->AddComponent(NEW Physics(glm::vec2(2, -1)));
	physicsManager.AddPhysics(ge4);
	AddGameEntity(ge4, TRANSLUCENT);
	animGEVector.push_back(ge4);

}
void pmScene::Update()
{
	float frameTime = time.Restart(pm::Time::FRACTION::SECONDS);
	UpdateGameEntities(frameTime);
	Draw();
}
void pmScene::UpdateGameEntities(float time)
{
	pm::GameEntity* gameEntity;

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
	physicsManager.Update(time);
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
void pmScene::Draw()
{

	for (int translucentIndex = 0; translucentIndex < translucentGameEntityVector.size(); translucentIndex++)
	{
		spriteBatch->AddTranslucentGameEntity(translucentGameEntityVector[translucentIndex]);
	}
	for (int opaqueIndex = 0; opaqueIndex < opaqueGameEntityVector.size(); opaqueIndex++)
	{
		spriteBatch->AddOpaqueGameEntity(opaqueGameEntityVector[opaqueIndex]);
	}
	
}

void pmScene::AddGameEntity(pm::GameEntity* drawableGameEntity, TRANSLUCENCY type)
{
	Scene::AddGameEntity(drawableGameEntity);
	if (type == TRANSLUCENT)
	{
		translucentGameEntityVector.push_back(drawableGameEntity);
	}
	else if (type == OPAQUE)
	{
		opaqueGameEntityVector.push_back(drawableGameEntity);
	}
	else
	{
		DEBUG_INFO(("Added unknown drawable type of GameEntity, it wont be drawn."));
	}
}

void pmScene::RemoveDrawableGameEntity(pm::GameEntity* gameEntity)
{
	std::vector<pm::GameEntity*>::iterator it;
	bool skipOpaque = false;

	for (it = translucentGameEntityVector.begin(); it != translucentGameEntityVector.end();)
	{
		if (*it == gameEntity)
		{
			it = translucentGameEntityVector.erase(it);
			skipOpaque = true;
			break;
		}
		else
			it++;
	}
	if (skipOpaque == false)
	{ 
		for (it = opaqueGameEntityVector.begin(); it != opaqueGameEntityVector.end();)
		{
			if (*it == gameEntity)
			{
				it = opaqueGameEntityVector.erase(it);
				break;
			}
			else
				it++;
		}
	}
	RemoveGameEntity(gameEntity);
}