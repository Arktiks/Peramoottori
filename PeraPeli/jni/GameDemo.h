#pragma once

// GameDemo poistetaan ja tehd‰‰n uudestaan mainiin

#include "SpriteObject.h"

#include <core\Log.h>
#include <core\Passert.h>
#include <core\Memory.h>
#include <core\Application.h>
#include <core\Input.h>
#include <core\Time.h>
#include <resources\ResourceManager.h>
#include <resources\TextureFactory.h>
#include <audio\Audio.h>

//#include <graphics\Rectangle.h>
#include <graphics\SpriteBatch.h>
#include <graphics\Drawable.h>
#include <graphics\Color.h>
#include <scene\GameEntity.h>

#include <map>
class GameDemo
{
public:
	GameDemo();
	~GameDemo();
	void Initialize();
	void Update();
	pm::Time time;
	pm::Audio* touchAudio;
	pm::Input input;
	pm::Texture FindTexture(std::string name);
	SpriteObject FindSpriteObject(std::string name);
private:
	void BallPhysics(SpriteObject* target);
	bool CheckTouch(glm::vec2 touch, SpriteObject* target);
	bool holdingBall;
	void Draw();
	std::map<std::string, pm::Texture*> textureMap;
	std::map<std::string, SpriteObject*> spriteMap;
	std::map<std::string, SpriteObject*> opaqueSpriteMap;
};

