#ifndef PMSCENE_H
#define PMSCENE_H
#include <scene\Scene.h>
#include <core\Application.h>
#include <scene\GameEntity.h>
#include <graphics\SpriteBatch.h>
#include <scene\Transformable.h>
#include <scene\TextureCoordinates.h>
#include <graphics\Rectangle.h>
#include <graphics\Drawable.h>
#include <graphics\Color.h>
#include <resources\ResourceManager.h>
#include <core\Log.h>
#include <core\Time.h>
#include <vector>

#include "Animation.h"
enum TRANSLUCENCY
{
	TRANSLUCENT,
	OPAQUE
};

class pmScene : public pm::Scene
{
public:
	pmScene();
	~pmScene();

	void Update();
	void UpdateAnimation(float time);
	void Draw();
	void InitializeResources();
	void InitializeGameEntities();

	void AddGameEntity(pm::GameEntity* gameEntity, TRANSLUCENCY type);
	void RemoveDrawableGameEntity(pm::GameEntity* gameEntity);

private:
	pm::SpriteBatch* spriteBatch;
	pm::Application* app;
	pm::ResourceManager* resMan;
	std::vector<pm::GameEntity*> translucentGameEntityVector;
	std::vector<pm::GameEntity*> opaqueGameEntityVector;
	std::vector<pm::GameEntity*> animGEVector;
	pm::Time time;
	float frameTime;
	float animTime;
	int frameDir = 1;
};
#endif