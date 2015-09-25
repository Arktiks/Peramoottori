#include "GameDemo.h"
#include "RNG.h"


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
	audioMap["alternativeMusic"]->Pause();
}

void GameDemo::Unpause()
{
	paused = false;
	audioMap["alternativeMusic"]->Play();
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
			delete *it3;
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
			delete *it3;
			it3 = opaqueSpriteVector.erase(it3);
		}
		else
			it3++;
	}
	
}


void GameDemo::InitializeGameValues()
{
	paused = false;
	win = false;
	score = 0;
	combo = 0;
	soundBool = false;
	deltaTime = time.CalculateTimeInFrame();
	fasterTimer = 2000000000;
	
	pm::RenderSystem::GetInstance()->SetActiveCamera(&asdcamera);
	pm::Vector2<int> pmLimits = pm::Application::GetInstance()->window.GetResolution();
	limits.x = pmLimits.x;
	limits.y = pmLimits.y;
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

	textureMap["background"]	= pm::TextureFactory::CreateTexture("sprites/background/felt_brown.png");
	textureMap["win"]			= pm::TextureFactory::CreateTexture("sprites/background/mg.png");
	textureMap["smoke"]			= pm::TextureFactory::CreateTexture("sprites/smoke/particlefx_03.png");
	textureMap["explosion"]		= pm::TextureFactory::CreateTexture("sprites/smoke/explosion.png");
	textureMap["logo"]			= pm::TextureFactory::CreateTexture("sprites/background/logo.png");
}

void GameDemo::InitializeSounds()
{
	// Load sound files and add them to map
	audioMap["applause"]		= NEW pm::Audio("sounds/Applause.ogg");
	audioMap["winPhrase"]		= NEW pm::Audio("sounds/voitto.ogg");
	audioMap["victoryScream"]	= NEW pm::Audio("sounds/victoryScream.ogg");
	audioMap["hit"]				= NEW pm::Audio("sounds/hit.ogg");
	audioMap["explosion"]		= NEW pm::Audio("sounds/explosion.ogg");
	audioMap["happyMusic"]		= NEW pm::Audio("sounds/happyMusic.ogg");
	audioMap["alternativeMusic"]= NEW pm::Audio("sounds/koo.ogg");

	// Set attributes of sounds.
	audioMap["applause"]->SetVolume(30);
	audioMap["applause"]->SetMaxPlayerCount(3);
	
	audioMap["winPhrase"]->SetVolume(1000);
	
	audioMap["victoryScream"]->SetVolume(40);
	
	audioMap["hit"]->SetMaxPlayerCount(20);
	audioMap["hit"]->SetVolume(10);
	
	audioMap["explosion"]->SetMaxPlayerCount(20);
	audioMap["explosion"]->SetVolume(50);
	
	audioMap["alternativeMusic"]->SetLooping(true);
	audioMap["alternativeMusic"]->SetVolume(60);
}

void GameDemo::InitializeText()
{
	text = NEW pm::Text(font = static_cast<pm::FontResource*>(pm::ResourceManager::GetInstance()->LoadAsset("arial.ttf")),
		textResource = NEW pm::TextResource("Score "), 32, limits.y - 32, 32, 32);

}
void GameDemo::InitializeGameEntities()
{
	SpriteObject* backGround = NEW SpriteObject(textureMap["background"]);
	backGround->SetPosition(glm::vec2(0, 0));
	backGround->SetSize(limits);
	backGround->SetDepth(0);
	spriteVector.push_back(backGround);

	help = NEW SpriteObject(pm::TextureFactory::CreateTexture("iiro.png"));
	help->SetPosition(glm::vec2(limits.x - 32, limits.y - 32));
	help->SetSize(32, 32);
	help->SetDrawState(false);
}

void GameDemo::Initialize()
{
	InitializeGameValues();

	InitializeTextures();

	InitializeSounds();

	InitializeText();
	
	InitializeGameEntities();
	audioMap["winPhrase"]->Play();
	audioMap["alternativeMusic"]->Play();
	//SplashScreen();
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

void GameDemo::SplashScreen()
{
	logoSprite = NEW SpriteObject(textureMap["logo"]);

	logoSprite->SetSize(limits);
	logoSprite->SetPosition(glm::vec2(0, 0));

}

void GameDemo::OneTimeWinFunction()
{
	DeleteAllSprites();

	winSprite = NEW SpriteObject(textureMap["win"]);
	winSprite->SetSize(limits);
	winSprite->SetPosition(glm::vec2(0, 0));

	audioMap["alternativeMusic"]->Stop();

	audioMap["applause"]->Play();
	audioMap["victoryScream"]->Play();

	audioBool = true;
}
void GameDemo::WinFunction()
{
	
	pm::SpriteBatch::GetInstance()->AddGameEntity(winSprite);

	spawnTimer += time.CalculateTimeInFrame();
	if (spawnTimer > 1000000 && audioBool)
	{
		audioMap["applause"]->Play();
		audioBool = false;
	}
	if (spawnTimer > 1100000)
	{
		audioMap["winPhrase"]->Play();
		spawnTimer = 0;
		audioBool = true;
	}
}	

float logoTimer = 0;
void GameDemo::Update()
{
	asdcamera.RotateCamera(1.0f);
	inverseCameraMatrix = asdcamera.GetInverseCameraMatrix();


	deltaTime = time.CalculateTimeInFrame();
	if (win)
		WinFunction();
	
	else
	{
		if (score > 700)
		{
			win = true;
			OneTimeWinFunction();
			return;
		}
		
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
		
		CheckInput();
		DeleteDone();

		if (scoreChange)
		{
			scoreChange = false;
			SetScoreString();
		}
		Draw();
	}
}

void GameDemo::SetScoreString()
{
	//TODO: Testaa johtuuko vuoto tekstien m‰‰r‰st‰

	std::stringstream ss;
	ss << score;

	std::string tempString = "Score " + ss.str();
	*textResource = pm::TextResource(tempString);
	// Destroy old text resource
	// Temporary, will be changed when texture has function to change string.
	//if (text != nullptr)
	//{
	//	text->~Text();
	//}
	text->ReText(font, textResource, 32, limits.y -32, 32, 32);
	//*text = pm::Text(font, textResource, 32, limits.y - 32, 32, 32);
	
}

void GameDemo::AddEnemy(glm::vec2 location)
{
	// Create new enemy and set it's attributes
	Enemy* enemy = NEW Enemy();
	enemy->SetPosition(location);
	enemy->SetDrawState(false);
	
	enemy->SetSize(200, 200);
	enemy->SetDepth(float(RNG::Between(100,200))/100.0f);
	// Copy multipleTexture-component's texture pointers to enemy's multipleTexture-component.
	enemy->SetTextureVector(EnemyTextures.textures);
	enemyVector.push_back(enemy);
	opaqueSpriteVector.push_back(enemy);
	AddSmoke(location);
	
}
void GameDemo::AddSmoke(glm::vec2 location)
{
	// Create atlascoordinates for smoke to use
	// These are based on textureAtlas
	// Size of one sprite
	glm::vec2 smokeSize(128.0f, 128.0f);
	// amount of sprites in x & y
	glm::vec2 smokeAmount(8, 8);
	std::vector<glm::vec2> smokeCoords;
	//std::vector<glm::vec2> smokeCoords = CreateSpriteSheet(smokeSize, smokeAmount);
	for (int y = 7; y > 0; y--)
	{
		for (int x = 0; x < 8; x++)
		{
			smokeCoords.push_back(glm::vec2(x * smokeSize.x, y * smokeSize.y));
		}
	}

	Smoke* smoke = NEW Smoke(textureMap["smoke"], smokeSize, smokeCoords);
	smoke->SetDepth(2);
	smoke->SetPosition(location);
	smoke->SetSize(300,300);
	smoke->SetOrigin(40, 20);
	smokeVector.push_back(smoke);
	opaqueSpriteVector.push_back(smoke);
}

std::vector<glm::vec2> GameDemo::CreateSpriteSheet(glm::vec2 pixelSize, glm::vec2 spriteAmount)
{
	std::vector<glm::vec2> coordinates;
	for (int y = spriteAmount.y-1; y > 0; y--)
	{
		for (int x = 0; x < spriteAmount.x; x++)
		{
			coordinates.push_back(glm::vec2(x * pixelSize.x, y * pixelSize.y));
		}
	}
	return coordinates;
}
// add Smoke-SpriteObject to given position
void GameDemo::AddExplosion(glm::vec2 location)
{
	// Set size for one sprite in sheet.
	glm::vec2 explosionSize(64.0f, 64.0f);
	// create vector for explosion spritesheet.
	std::vector<glm::vec2> explosionCoords;
	// Add sprites according to their position on texture
	for (int y = 3; y > 0; y--)
	{
		for (int x = 0; x < 4; x++)
		{
			explosionCoords.push_back(glm::vec2(x * explosionSize.x, y * explosionSize.y));
		}
	}
	// Use smoke (Sprite with animation) to create explosion.
	Smoke* explosion = NEW Smoke(textureMap["explosion"], explosionSize, explosionCoords);
	// Set how deep explosion is drawn.
	explosion->SetDepth(2);
	explosion->SetPosition(location);
	explosion->SetSize(300, 300);
	explosion->SetOrigin(40, 20);

	// Add explosion to smokeVector, so that it is updated in update()
	smokeVector.push_back(explosion);
	opaqueSpriteVector.push_back(explosion);
}


void GameDemo::Draw()
{
	// GO throught gameObjects to add them to be drawn.
	std::vector<SpriteObject*>::iterator it;

	// add non-opaque sprites first
	for (it = spriteVector.begin(); it != spriteVector.end(); it++)
		pm::SpriteBatch::GetInstance()->AddGameEntity(*it);
	// add opaque sprites
	for (it = opaqueSpriteVector.begin(); it != opaqueSpriteVector.end(); it++)
		pm::SpriteBatch::GetInstance()->AddOpaqueGameEntity(*it);
	// create iterator to go throught letter entities
	std::vector<pm::GameEntity*>::iterator it2;

	// add letter entities
	std::vector<pm::GameEntity*> textGEV = text->GetTextVector();
	
	pm::SpriteBatch::GetInstance()->AddOpaqueGameEntity(textGEV);

}

void GameDemo::CheckInput()
{
	// Check if touchscreen is being touched
	if (input.IsTouching())
	{
		
		// Get current position of touch
		//glm::vec4 touchxPosition = (inverseCameraMatrix * glm::vec4(input.GetTouchCoordinates(), 1, 1));
		glm::vec2 touchPosition = input.GetTouchCoordinates();
		// Check if touch sound has already been played
		if (!soundBool)
		{
			// Play touch sound
			audioMap["hit"]->Play();
		}
		// Check if touch is inside any enemy sprites.
		for (int i = 0; i < enemyVector.size(); i++)
		{
			// Set score, destruction-animation and destruction flag for enemy.
			if (CheckTouch(touchPosition, enemyVector[i]))
			{
				combo++;
				score += combo;
				scoreChange = true;
				
				audioMap["explosion"]->Play();
				AddExplosion(enemyVector[i]->GetPosition());
				
				enemyVector[i]->done = true;
			}
		}
		// Temporary function for clearing the screen.
		if (CheckTouch(touchPosition, help))
		{
			for (int i = 0; i < opaqueSpriteVector.size(); i++)
				opaqueSpriteVector[i]->done = true;
			scoreChange = true;
		}
		soundBool = true;
	}
	else
		soundBool = false;
}

//Check if touched area is inside sprite's area.
//touchPosition = position touched, target = SpriteObject which area is checked.

bool GameDemo::CheckTouch(glm::vec2 touchPosition, SpriteObject *target)
{
	glm::vec2 position = target->GetPosition();
	glm::vec2 size = target->GetSize();

	if (position.x < touchPosition.x && position.x + size.x > touchPosition.x &&
		position.y < touchPosition.y && position.y + size.y > touchPosition.y)
	{
		return true;
	}
	else
	return false;
}

bool GameDemo::CheckTouchCircle(glm::vec2 touchPosition, SpriteObject *target)
{
	glm::vec2 position = target->GetPosition();
	glm::vec2 size = target->GetSize();

	if (position.x < touchPosition.x && position.x + size.x > touchPosition.x &&
		position.y < touchPosition.y && position.y + size.y > touchPosition.y)
	{
		return true;
	}
	else
		return false;
}

// Check if touched area is inside the target area.
// touchPosition = position touched, target = position and size of target.
bool GameDemo::CheckTouch(glm::vec2 touchPosition, glm::vec4 target)
{
	if (target.x < touchPosition.x && target.x + target.z > touchPosition.x &&
		target.y < touchPosition.y && target.y + target.w > touchPosition.y)
			return true;
	else
	return false;
}

