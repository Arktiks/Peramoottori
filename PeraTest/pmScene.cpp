#include "pmScene.h"

pmScene::pmScene()
{
	pm::Application* app = pm::Application::GetInstance();
	spriteBatch = pm::SpriteBatch::GetInstance();
}

pmScene::~pmScene()
{
}

void pmScene::Update()
{
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
	app->Draw();
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
	for (std::vector<pm::GameEntity*>::iterator it = gameEntityVector.begin(); it != gameEntityVector.end();)
	{
		if (*it == gameEntity)
		{
			delete *it;
			it = gameEntityVector.erase(it);
			break;
		}
		else
			it++;
	}
	RemoveGameEntity(gameEntity);
}