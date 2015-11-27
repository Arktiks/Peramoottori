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
#include "Physics.h"
#include "UpdateRate.h"
#include "Animation.h"


#include "PhysicsManager.h"
#include <resources\ResourceManager.h>
#include <core\Log.h>
#include <core\Time.h>
#include <vector>


enum TRANSLUCENCY
{
	TRANSLUCENT,
	OPAQUE
};


class GameEntityFactory;
class pmScene : public pm::Scene
{
	
public:
	pmScene();
	~pmScene();

	void Update();
	void Draw();
	void AddGameEntity(pm::GameEntity* gameEntity, TRANSLUCENCY type);
	void AddAnimationGameEntity(pm::GameEntity* gameEntity, TRANSLUCENCY type);
	void RemoveDrawableGameEntity(pm::GameEntity* gameEntity);
	PhysicsManager physicsManager;
private:
	void InitializeResources();
	void InitializeGameEntities();

	void UpdateAnimation(pm::GameEntity* gameEntity);
	void UpdateScaleRotation(pm::GameEntity* gameEntity);
	void UpdateGameEntities(float time);

	GameEntityFactory* gameEntityFactory;
	
	pm::SpriteBatch* spriteBatch;
	pm::Application* app;
	std::vector<pm::GameEntity*> translucentGameEntityVector;
	std::vector<pm::GameEntity*> opaqueGameEntityVector;
	std::vector<pm::GameEntity*> animGEVector;

	pm::Time time;
	glm::vec2 limits;



};
#endif