#include "GameEntityFactory.h"
#include <scene\Name.h>
#include <scene\Transformable.h>
#include <scene\TextureCoordinates.h>
#include <graphics\Rectangle.h>
#include <graphics\Drawable.h>
#include <graphics\Color.h>
#include "Physics.h"
#include "UpdateRate.h"
#include "Animation.h"
GameEntityFactory::GameEntityFactory(pmScene* scene)
{
	this->scene = scene;
}


GameEntityFactory::~GameEntityFactory()
{
}

pm::GameEntity* GameEntityFactory::CreateHero(glm::vec2 position, int depth, glm::vec2 size, glm::vec2 force, float animationFrameTime)
{
	pm::GameEntity* heroGameEntity = NEW pm::GameEntity();
	heroGameEntity->AddComponent(NEW pm::Name("hero"));

	AddSpriteComponents(heroGameEntity, "space/hero.png", position, glm::vec2(1,1), 0, depth, size, glm::vec4(1,1,1,0.6));
	AddAnimationComponents(heroGameEntity, glm::vec4(0, 0, 140, 230), animationFrameTime, glm::vec2(140, 230),
		glm::vec2(7, 2), 14, 0);


	// Add default physics to GameEntity.
	scene->physicsManager.AddPhysics(heroGameEntity);
	// Add gameEntity on pmScene's animGEVector, and in drawVector, Translucent because we know hero.png is translucent image.
	scene->AddAnimationGameEntity(heroGameEntity, TRANSLUCENT);

	return heroGameEntity;
}

pm::GameEntity* GameEntityFactory::CreateRospot(glm::vec2 position, int depth, glm::vec2 size,
	glm::vec2 force)
{
	pm::GameEntity* rospotGameEntity = NEW pm::GameEntity();
	rospotGameEntity->AddComponent(NEW pm::Name("rospot"));
	
	AddSpriteComponents(rospotGameEntity, "space/rospot.png", position, glm::vec2(1, 1), 0, depth, size, glm::vec4(1, 1, 1, 1));

	// Add physics to GameEntity.
	scene->physicsManager.AddPhysics(rospotGameEntity);
	scene->AddGameEntity(rospotGameEntity, TRANSLUCENT);
	return rospotGameEntity;
}
pm::GameEntity* GameEntityFactory::CreateButton(glm::vec2 position, int depth, glm::vec2 size)
{
	pm::GameEntity* buttonGameEntity = NEW pm::GameEntity();
	AddSpriteComponents(buttonGameEntity, "space/galaxy.png", position, glm::vec2(1, 1), 0, depth, size, glm::vec4(1, 0.5, 0.5, 1));
	buttonGameEntity->AddComponent(NEW pm::Name("button"));

	AddInputComponents(buttonGameEntity);

	scene->AddGameEntity(buttonGameEntity, TRANSLUCENT);
}
void GameEntityFactory::AddSpriteComponents(pm::GameEntity* gameEntity, std::string textureFilePath, glm::vec2 position, glm::vec2 scale, 
	float rotation, int depth, glm::vec2 size, glm::vec4 color)
{
	gameEntity->AddComponent(scene->GetTexture(textureFilePath));
	gameEntity->AddComponent(NEW pm::Transformable(position, scale, rotation));
	gameEntity->GetComponent<pm::Transformable>()->SetDepth(depth);
	gameEntity->AddComponent(NEW pm::Rectangle(size));
	gameEntity->AddComponent(NEW pm::Color(color));
	gameEntity->AddComponent(NEW pm::Drawable());
}

void GameEntityFactory::AddAnimationComponents(pm::GameEntity* gameEntity, glm::vec4 textureCoordinates, float animationFrameTime, glm::vec2 frameSize,
	glm::vec2 frameAmounts, int frameAmount, int startFrame)
{
	pm::TextureCoordinates* o = NEW pm::TextureCoordinates();
	gameEntity->AddComponent(o);
	gameEntity->GetComponent<pm::TextureCoordinates>()->SetTextureCoordinates(textureCoordinates);
	gameEntity->AddComponent(NEW Animation(animationFrameTime));
	gameEntity->GetComponent<Animation>()->SetValues(frameSize.x, frameSize.y, startFrame, frameAmount, frameAmounts.x, frameAmounts.y);
	gameEntity->GetComponent<Animation>()->GenerateCoords();
}

void GameEntityFactory::AddInputComponents(pm::GameEntity* gameEntity)
{
	gameEntity->AddComponent(NEW pm::Hitbox());
}