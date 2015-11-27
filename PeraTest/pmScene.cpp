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

	gameEntityFactory->CreateHero(glm::vec2(300, 300), 2, glm::vec2(200, 400), glm::vec2(100, 30), 0.1);
	gameEntityFactory->CreateHero(glm::vec2(600, 500), 3, glm::vec2(150, 300), glm::vec2(205, 125), 0.05);
	gameEntityFactory->CreateHero(glm::vec2(100, 200), 4, glm::vec2(100, 200), glm::vec2(50, 50), 0.01);
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


void pmScene::AddAnimationGameEntity(pm::GameEntity* gameEntity, TRANSLUCENCY type)
{
	Scene::AddGameEntity(gameEntity);
	if (type == TRANSLUCENT)
	{
		translucentGameEntityVector.push_back(gameEntity);
	}
	else if (type == OPAQUE)
	{
		opaqueGameEntityVector.push_back(gameEntity);
	}
	else
	{
		DEBUG_INFO(("Added unknown drawable type of GameEntity, it wont be drawn."));
	}
	animGEVector.push_back(gameEntity);


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