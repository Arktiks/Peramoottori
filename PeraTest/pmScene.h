#pragma once
#include <scene\Scene.h>
#include <core\Application.h>
#include <scene\GameEntity.h>
#include <graphics\SpriteBatch.h>
#include <core\Log.h>
#include <vector>

enum TRANSLUCENCY
{
	TRANSLUCENT,
	OPAQUE,
};

class pmScene : public pm::Scene
{
public:
	pmScene();
	~pmScene();

	void Update();
	void Draw();

	void AddGameEntity(pm::GameEntity* gameEntity, TRANSLUCENCY type);
	void RemoveDrawableGameEntity(pm::GameEntity* gameEntity);

private:
	pm::SpriteBatch* spriteBatch;
	pm::Application* app;
	std::vector<pm::GameEntity*> translucentGameEntityVector;
	std::vector<pm::GameEntity*> opaqueGameEntityVector;
};