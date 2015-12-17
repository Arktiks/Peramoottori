#ifndef PMSCENE_H
#define PMSCENE_H
#include <scene\Scene.h>
#include <core\Application.h>
#include <core\Input.h>
#include <graphics\SpriteBatch.h>
#include <scene\GameEntity.h>
#include <scene\Transformable.h>
#include <scene\TextureCoordinates.h>
#include <scene\Camera.h>
#include <scene\CameraSystem.h>
#include <graphics\Rectangle.h>
#include <graphics\Drawable.h>
#include <graphics\Color.h>
#include "Physics.h"
#include "UpdateRate.h"
#include "Animation.h"
#include "GameEntityFactory.h"


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

class pmScene : public pm::Scene
{
	
public:
	
	pmScene();
	~pmScene();

	virtual void Update();
	void AddAnimationGameEntity(pm::GameEntity* gameEntity);
	void RemoveDrawableGameEntity(pm::GameEntity* gameEntity);
	void MoveCamera(glm::vec2 position);
	PhysicsManager physicsManager;
protected:
	virtual void InitializeResources();
	virtual void InitializeGameEntities();

	void UpdateAnimation(pm::GameEntity* gameEntity);
	void UpdateScaleRotation(pm::GameEntity* gameEntity);
	virtual void UpdateGameEntities(float time);

	void ButtonPress(pm::GameEntity* gameEntity);
	
	GameEntityFactory* gameEntityFactory;
	
	pm::SpriteBatch* spriteBatch;
	pm::Application* app;
	std::vector<pm::GameEntity*> animGEVector;

	pm::Time time;
	glm::vec2 limits;
	pm::Camera camera;
	pm::Input input;
	float cameraZoom;
	float heroTime;
	int direction;

};
#endif