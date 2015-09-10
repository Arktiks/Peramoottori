#pragma once

// GameDemo poistetaan ja tehd‰‰n uudestaan mainiin

#include "SpriteObject.h"
#include "Enemy.h"
#include "Smoke.h"
#include "MultipleTexture.h"
#include <vector>
#include <core\Log.h>
#include <core\Passert.h>
#include <core\Memory.h>
#include <core\Application.h>
#include <core\Input.h>
#include <core\Time.h>
#include <graphics\Text.h>
#include <resources\ResourceManager.h>
#include <resources\TextureFactory.h>
#include <audio\Audio.h>
#include <map>
class GameDemo
{
public:
	GameDemo();
	~GameDemo();
	void Initialize();
	void Update();
	pm::Time time;

	pm::Input input;
	bool paused;
	static bool first;
	void Pause();
	void Unpause();

private:


	SpriteObject* winSprite, *logoSprite;
	bool audioBool;
	pm::Text* text;
	pm::TextResource* textResource;
	pm::FontResource* font;
	int score;
	bool scoreBool;
	bool scoreChange;
	int combo;
	float fasterTimer;
	float spawnTimer;
	float deltaTime;
	bool soundBool;
	glm::vec2 limits;

	void InitializeGameValues();
	void InitializeTextures();
	void InitializeSounds();
	void InitializeText();
	void InitializeGameEntities();

	void AddEnemy(glm::vec2 location);
	void AddSmoke(glm::vec2 location);
	void AddExplosion(glm::vec2 location);
	

	bool win;
	void SplashScreen();
	void WinFunction();
	void OneTimeWinFunction();
	
	bool CheckTouch(glm::vec2 touchPosition, SpriteObject* target);
	bool CheckTouch(glm::vec2 touchPosition, glm::vec4 target);

	void CheckInput();
	void Draw();
	void DeleteDone();
	void DeleteAllSprites();

	void SetScoreString();

	MultipleTexture EnemyTextures;
	SpriteObject* help;
	std::map<std::string, pm::Texture*> textureMap;
	std::map<std::string, pm::Audio*> audioMap;
	std::vector<Smoke*> smokeVector;
	
	std::vector<Enemy*> enemyVector;

	std::vector<SpriteObject*> spriteVector;
	std::vector<SpriteObject*> opaqueSpriteVector;

	
};

