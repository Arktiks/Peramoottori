#include "pmScene.h"
#include <core\Time.h>

pmScene::pmScene()
{
	pm::Application* app = pm::Application::GetInstance();
	spriteBatch = pm::SpriteBatch::GetInstance();
	resMan = pm::ResourceManager::GetInstance();
	time.Start();
	frameTime = 0;
	animTime = 0;
	InitializeResources();
	InitializeGameEntities();
}

pmScene::~pmScene()
{
}

void pmScene::InitializeResources()
{
	pmScene::AddTexture("space/background.png");
	pmScene::AddTexture("space/hero.png");
}


void pmScene::InitializeGameEntities()
{
	pm::GameEntity* ge = NEW pm::GameEntity();
	ge->AddComponent(GetTexture("space/background.png"));
	ge->AddComponent(NEW pm::Transformable(glm::vec2(0, 0), glm::vec2(1,1),0));
	ge->AddComponent(NEW pm::Rectangle(200,200));
	ge->AddComponent(NEW pm::Drawable);
	ge->AddComponent(NEW pm::Color);
	ge->GetComponent<pm::Transformable>()->SetDepth(1);
	AddGameEntity(ge, OPAQUE);

	pm::GameEntity* ge2 = NEW pm::GameEntity();
	ge2->AddComponent(NEW pm::Texture("space/hero.png"));
	ge2->AddComponent(NEW pm::Transformable(glm::vec2(400, 100), glm::vec2(1, 1), 30));
	ge2->GetComponent<pm::Transformable>()->SetDepth(2);
	ge2->AddComponent(NEW pm::Rectangle(50, 100));
	ge2->AddComponent(NEW pm::Drawable);
	ge2->AddComponent(NEW pm::TextureCoordinates);
	ge2->AddComponent(NEW pm::Color(glm::vec4(0.8,0.8,0.8,0.8)));
	ge2->AddComponent(NEW Animation);
	ge2->GetComponent<Animation>()->SetValues(140,230,0,14,7,2,100);
	ge2->GetComponent<Animation>()->GenerateCoords();
	AddGameEntity(ge2, TRANSLUCENT);
	animGEVector.push_back(ge2);

	pm::GameEntity* ge3 = NEW pm::GameEntity();
	ge3->AddComponent(GetTexture("space/hero.png"));
	ge3->AddComponent(NEW pm::Transformable(glm::vec2(200, 100), glm::vec2(1, 1), -10));
	ge3->AddComponent(NEW pm::Rectangle(50, 100));
	ge3->AddComponent(NEW pm::Drawable);
	ge3->AddComponent(NEW pm::TextureCoordinates);
	ge3->AddComponent(NEW pm::Color(glm::vec4(0.2, 0.2, 0.2, 0.5)));
	ge3->GetComponent<pm::Transformable>()->SetDepth(2);
	ge3->AddComponent(NEW Animation);
	ge3->GetComponent<Animation>()->SetValues(140, 230, 0, 14, 7, 2, 100);
	ge3->GetComponent<Animation>()->GenerateCoords();
	AddGameEntity(ge3, TRANSLUCENT);
	animGEVector.push_back(ge3);

	pm::GameEntity* ge4 = NEW pm::GameEntity();
	ge4->AddComponent(NEW pm::Texture("space/hero.png"));
	ge4->AddComponent(NEW pm::Transformable(glm::vec2(100,100),glm::vec2(1,1),10));
	ge4->AddComponent(NEW pm::Rectangle(50,100));
	ge4->AddComponent(NEW pm::Drawable);
	ge4->AddComponent(NEW pm::TextureCoordinates);
	ge4->AddComponent(NEW pm::Color(glm::vec4(0.2, 0.2, 0.2, 0.5)));
	ge4->GetComponent<pm::Transformable>()->SetDepth(2);
	ge4->AddComponent(NEW Animation);
	ge4->GetComponent<Animation>()->SetValues(140, 230, 0, 14, 7, 2, 100);
	ge4->GetComponent<Animation>()->GenerateCoords();
	AddGameEntity(ge4, TRANSLUCENT);
	animGEVector.push_back(ge4);

}
void pmScene::Update()
{
	frameTime += time.GetElapsedTime(pm::Time::FRACTION::MILLISECONDS);
	UpdateAnimation(frameTime);
	Draw();
}

void pmScene::UpdateAnimation(float dtime)
{
	animTime += dtime;
	for (int i = 0; i < animGEVector.size(); i++)
	{
		
		pm::GameEntity* GE = animGEVector[i];
		Animation* anime = GE->GetComponent<Animation>();
		if (anime->timeBetweenFrame < animTime)
		{
			pm::TextureCoordinates* texC = GE->GetComponent<pm::TextureCoordinates>();
			glm::vec4 coordinates;
			if (anime->animationFrame > anime->frameAmount)
				frameDir = -1;
			else if (anime->animationFrame < 0)
				frameDir = 1;
			anime->animationFrame+=frameDir;
			animTime = 0;
			texC->SetTextureCoordinates(anime->animationCoordinates[anime->animationFrame]);
		}
	}
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