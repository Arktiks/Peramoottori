#pragma once

// Sprite -> periytym‰‰n gameObjectista ja uudellenime‰minen SpriteObject
// GameDemo poistetaan ja tehd‰‰n uudestaan mainiin
// Vektorit mapeiksi, jotta voidaan k‰ytt‰‰ helpommin

#include "Sprite.h"

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

#include <vector>
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
private:
	void Draw();
	std::vector<pm::Texture*> textureVector;
	std::vector<Sprite*> spriteVector;
	std::vector<Sprite*> opaqueSpriteVector;
};

