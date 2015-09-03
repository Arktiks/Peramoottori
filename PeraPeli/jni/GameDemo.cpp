#include "GameDemo.h"
#include "RNG.h"

#include "TailEntity.h"
#include <graphics\SpriteBatch.h>
#include <graphics\Drawable.h>
#include <graphics\Color.h>
#include <scene\GameEntity.h>
#include <resources\ResourceManager.h>
#include <sstream>
bool GameDemo::first = false;

GameDemo::GameDemo()
{

}


GameDemo::~GameDemo()
{
}
void GameDemo::Pause()
{
	paused = true;
	music->Pause();
}
void GameDemo::Unpause()
{
	paused = false;
	music->Play();
}
void GameDemo::DeleteDone()
{
	std::vector<Smoke*>::iterator it = smokeVector.begin();
	while (it != smokeVector.end())
	{
		if ((*it)->done)
		{
			it = smokeVector.erase(it);
		}
		else
			it++;
	}
	std::vector<Enemy*>::iterator it2 = enemyVector.begin();
	while (it2 != enemyVector.end())
	{
		if ((*it2)->done)
		{

			it2 = enemyVector.erase(it2);
		}
		else
			it2++;
	}
	std::vector<SpriteObject*>::iterator it3 = spriteVector.begin();
	while (it3 != spriteVector.end())
	{
		if ((*it3)->done)
		{
			delete (*it3);
			it3 = spriteVector.erase(it3);
		}
		else
			it3++;
	}
	it3 = opaqueSpriteVector.begin();
	while (it3 != opaqueSpriteVector.end())
	{
		if ((*it3)->done)
		{
			delete (*it3);
			it3 = opaqueSpriteVector.erase(it3);
		}
		else
			it3++;
	}
	
}

void GameDemo::DeleteAllSprites()
{
	std::vector<Smoke*>::iterator it = smokeVector.begin();
	while (it != smokeVector.end())
	{
		it = smokeVector.erase(it);
	}
	std::vector<Enemy*>::iterator it2 = enemyVector.begin();
	while (it2 != enemyVector.end())
	{
		it2 = enemyVector.erase(it2);
	}
	std::vector<SpriteObject*>::iterator it3 = spriteVector.begin();
	while (it3 != spriteVector.end())
	{
		delete (*it3);
		it3 = spriteVector.erase(it3);

	}
	it3 = opaqueSpriteVector.begin();
	while (it3 != opaqueSpriteVector.end())
	{
		delete (*it3);
		it3 = opaqueSpriteVector.erase(it3);
	}
}

void GameDemo::Initialize()
{
	paused = false;
	win = false;
	score = 0;
	combo = 0;
	soundBool = false;
	pm::Vector2<int> pmLimits = pm::Application::GetInstance()->window.GetResolution();
	limits.x = pmLimits.x;
	limits.y = pmLimits.y;

	//logoAudio = NEW pm::Audio("sounds/logo.ogg");
	//logoAudio->SetVolume(30);
	//logoAudio->SetMaxPlayerCount(1);

	winAudio = NEW pm::Audio("sounds/Applause.ogg");
	winAudio->SetVolume(30);
	winAudio->SetMaxPlayerCount(3);

	winAudio2 = NEW pm::Audio("sounds/voitto.ogg");
	winAudio2->SetVolume(100);

	winAudio3 = NEW pm::Audio("sounds/victoryScream.ogg");
	winAudio3->SetVolume(40);


	touchAudio = NEW pm::Audio("sounds/hit.ogg");
	touchAudio->SetMaxPlayerCount(20);
	touchAudio->SetVolume(5);

	explosionAudio = NEW pm::Audio("sounds/explosion.ogg");
	touchAudio->SetMaxPlayerCount(5);
	touchAudio->SetVolume(5);

	music = NEW pm::Audio("sounds/happyMusic.ogg");
	music->SetLooping(true);
	music->SetVolume(5);
	music->Play();

	text = NEW pm::Text( font =static_cast<pm::FontResource*>(pm::ResourceManager::GetInstance()->LoadAsset("arial.ttf"))
		, textResource = NEW pm::TextResource("Score "), 32, limits.y - 32, 32, 32);
	
	InitializeTextures();
	
	SpriteObject* backGround = NEW SpriteObject(textureMap["background"]);
	backGround->SetPosition(glm::vec2(0, 0));
	backGround->SetSize(limits);
	backGround->SetDepth(0);
	
	help = NEW SpriteObject(pm::TextureFactory::CreateTexture("iiro.png"));
	help->SetPosition(glm::vec2(limits.x - 32, limits.y - 32));
	help->SetSize(32, 32);
	help->SetDrawState(false);

	spriteVector.push_back(backGround);
	time.CalculateTimeInFrame();
	deltaTime = time.CalculateTimeInFrame();
	fasterTimer = 2000000000;

	//SplashScreen();
}

void GameDemo::InitializeTextures()
{
	// Creating animation for sprite with multiple different textures
	// Using custom component "MultipleTexture" to store the textures for future use
	
	EnemyTextures.AddTexture(pm::TextureFactory::CreateTexture("sprites/enemy/frame-1.png"));
	EnemyTextures.AddTexture(pm::TextureFactory::CreateTexture("sprites/enemy/frame-2.png"));
	EnemyTextures.AddTexture(pm::TextureFactory::CreateTexture("sprites/enemy/frame-3.png"));
	EnemyTextures.AddTexture(pm::TextureFactory::CreateTexture("sprites/enemy/frame-4.png"));
	EnemyTextures.AddTexture(pm::TextureFactory::CreateTexture("sprites/enemy/frame-5.png"));
	EnemyTextures.AddTexture(pm::TextureFactory::CreateTexture("sprites/enemy/frame-6.png"));
	EnemyTextures.AddTexture(pm::TextureFactory::CreateTexture("sprites/enemy/frame-7.png"));
	EnemyTextures.AddTexture(pm::TextureFactory::CreateTexture("sprites/enemy/frame-8.png"));

	// Adding background

	textureMap["background"] = pm::TextureFactory::CreateTexture("sprites/background/felt_brown.png");
	textureMap["win"] = pm::TextureFactory::CreateTexture("sprites/voitto.png");
	// Adding smoke-, explosion- and helper spritesheets
	textureMap["smoke"] = pm::TextureFactory::CreateTexture("sprites/smoke/particlefx_03.png");
	textureMap["explosion"] = pm::TextureFactory::CreateTexture("sprites/smoke/explosion.png");
	textureMap["logo"] = pm::TextureFactory::CreateTexture("sprites/background/logo.png");
}

void GameDemo::SplashScreen()
{
	logoSprite = NEW SpriteObject(textureMap["logo"]);

	logoSprite->SetSize(limits);
	logoSprite->SetPosition(glm::vec2(0, 0));

	logoAudio->Play();

}

void GameDemo::OneTimeWinFunction()
{
	DeleteAllSprites();

	winSprite = NEW SpriteObject(textureMap["win"]);
	winSprite->SetSize(limits);
	winSprite->SetPosition(glm::vec2(0, 0));


	music->Stop();
	winAudio3->Play();
	

	winAudio->Play();

}
void GameDemo::WinFunction()
{
	
	pm::SpriteBatch::GetInstance()->AddGameEntity(winSprite);

	spawnTimer += time.CalculateTimeInFrame();
	if (spawnTimer > 1000000)
	{
		winAudio2->Play();
		winAudio->Play();
		spawnTimer = 0;
	
	}
}	

float logoTimer = 0;
void GameDemo::Update()
{
	logoTimer += time.CalculateTimeInFrame();
	if (logoTimer < 2000000)
	{

	}
	if (win)
		WinFunction();
	
	else
		{
		if (score > 1000)
		{
			win = true;
			OneTimeWinFunction();
			return;
		}
		deltaTime = time.CalculateTimeInFrame();


		spawnTimer += deltaTime;
		if (spawnTimer > fasterTimer)
		{
			for (int i = 0; i < RNG::Random(3); i++)
			AddEnemy(glm::vec2(RNG::Random(limits.x-100), RNG::Random(limits.y-100)));
			spawnTimer = 0;
			fasterTimer -= 10000;
		}
		
		for (int i = 0; i < enemyVector.size(); i++)
		{
			enemyVector[i]->Update(deltaTime);
		}
		for (int i = 0; i < smokeVector.size(); i++)
		{
			smokeVector[i]->Update(deltaTime);
		}

		
		//	BallPhysics(opaqueSpriteMap["ball"]);
		
		InputUpdate();
		DeleteDone();
		if (scoreBool)
		{
			
			scoreBool = false;
			std::stringstream ss;
			ss << score;

			std::string tempString = "Score " + ss.str();
			*textResource = pm::TextResource(tempString);

			*text = pm::Text(font, textResource, 32, limits.y - 32, 32, 32);
		}
		Draw();
	}
}

void GameDemo::AddEnemy(glm::vec2 location)
{

	Enemy* enemy = new Enemy();
	enemy->SetPosition(location);
	enemy->SetDrawState(false);
	
	enemy->SetSize(200, 200);
	enemy->SetDepth(1);
	enemy->SetTextureVector(EnemyTextures.textures);
	enemyVector.push_back(enemy);
	opaqueSpriteVector.push_back(enemy);
	AddSmoke(location);
	
}
void GameDemo::AddSmoke(glm::vec2 location)
{
	// Create atlascoordinates for smoke to use
	// These are based on textureAtlas
	glm::vec2 smokeSize(128.0f, 128.0f);
	std::vector<glm::vec2> smokeCoords;
	for (int y = 7; y > 0; y--)
	{
		for (int x = 0; x < 8; x++)
		{
			smokeCoords.push_back(glm::vec2(x * smokeSize.x, y * smokeSize.y));
		}
	}
	Smoke* smoke = new Smoke(textureMap["smoke"], smokeSize, smokeCoords );
	smoke->SetDepth(2);
	smoke->SetPosition(location);
	smoke->SetSize(300,300);
	smoke->SetOrigin(40, 20);
	smokeVector.push_back(smoke);
	opaqueSpriteVector.push_back(smoke);
}
void GameDemo::AddExplosion(glm::vec2 location)
{
	glm::vec2 explosionSize(64.0f, 64.0f);
	std::vector<glm::vec2> explosionCoords;
	for (int y = 3; y > 0; y--)
	{
		for (int x = 0; x < 4; x++)
		{
			explosionCoords.push_back(glm::vec2(x * explosionSize.x, y * explosionSize.y));
		}
	}
	Smoke* explosion = new Smoke(textureMap["explosion"], explosionSize, explosionCoords);
	explosion->SetDepth(2);
	explosion->SetPosition(location);
	explosion->SetSize(300, 300);
	explosion->SetOrigin(40, 20);
	smokeVector.push_back(explosion);
	opaqueSpriteVector.push_back(explosion);
}


void GameDemo::Draw()
{
	std::vector<SpriteObject*>::iterator it;

	for (it = spriteVector.begin(); it != spriteVector.end(); it++)
		pm::SpriteBatch::GetInstance()->AddGameEntity(*it);

	for (it = opaqueSpriteVector.begin(); it != opaqueSpriteVector.end(); it++)
		pm::SpriteBatch::GetInstance()->AddOpaqueGameEntity(*it);
	
	std::vector<pm::GameEntity*>::iterator it2;

	std::vector<pm::GameEntity*> textGEV = text->GetTextVector();
	for (it2 = textGEV.begin(); it2 != textGEV.end(); it2++)
		pm::SpriteBatch::GetInstance()->AddOpaqueGameEntity(*it2);
}

void GameDemo::InputUpdate()
{
	if (input.IsTouching())
	{
		if (!soundBool)
		{
			soundBool = true;
			touchAudio->Play();
		}
		glm::vec2 touchPosition = glm::vec2(input.GetTouchCoordinates().x, input.GetTouchCoordinates().y);

		//	opaqueSpriteMap["point"]->SetDrawState(true);
		//	opaqueSpriteMap["point"]->SetPosition(touchPosition);

		for (int i = 0; i < enemyVector.size(); i++)
		{
			if (CheckTouch(touchPosition, enemyVector[i]))
			{
				combo++;
				score += combo;
				scoreBool = true;
				explosionAudio->Play();
				AddExplosion(enemyVector[i]->GetPosition());
				
				enemyVector[i]->done = true;

			}
		}
		if (CheckTouch(touchPosition, help))
		{
			for (int i = 0; i < opaqueSpriteVector.size(); i++)
				opaqueSpriteVector[i]->done = true;
			scoreBool = true;
		}
	}
	else
		soundBool = false;
}

bool GameDemo::CheckTouch(glm::vec2 touch, SpriteObject *target)
{
	glm::vec2 position = target->GetPosition();
	glm::vec2 size = target->GetSize();

	if (position.x < touch.x && position.x + size.x > touch.x && 
		position.y < touch.y && position.y + size.y > touch.y)
			return true;
	else
	return false;
}

