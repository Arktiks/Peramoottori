#include "GameDemo.h"


GameDemo::GameDemo()
{
}


GameDemo::~GameDemo()
{
}

void GameDemo::Initialize()
{
	touchAudio = NEW pm::Audio("0477.ogg");
	touchAudio->SetMaxPlayerCount(10);

	pm::Texture* pointTexture = pm::TextureFactory::CreateTexture("point.png");
	pm::Texture* groundTexture = pm::TextureFactory::CreateTexture("groundTexture.png");
	textureVector.push_back(pointTexture);
	textureVector.push_back(groundTexture);


	Sprite* pointSprite = new Sprite(pointTexture);
	opaqueSpriteVector.push_back(pointSprite);
	pointSprite->SetDepth(3);
	pointSprite->SetSize(200, 300);
	pointSprite->SetOrigin(30, 0);


	Sprite* groundSprite = new Sprite(groundTexture);
	spriteVector.push_back(groundSprite);
	groundSprite->SetPosition(500, 500);
	groundSprite->SetSize(1000, 100);
	groundSprite->SetRotation(5.0f);


	Sprite* touchSprite1 = new Sprite();
	spriteVector.push_back(touchSprite1);
	touchSprite1->SetPosition(0, 500);
	touchSprite1->SetSize(200, 200);

	Sprite* touchSprite2 = new Sprite();
	spriteVector.push_back(touchSprite2);
	touchSprite2->SetPosition(700, 500);
	touchSprite2->SetSize(200, 200);
}
void GameDemo::Update()
{
	glm::vec2 touchPosition = input.GetTouchCoordinates();
	opaqueSpriteVector[0]->SetPosition(touchPosition);

	Draw();
}

void GameDemo::Draw()
{
	for (int i = 0; i < opaqueSpriteVector.size(); i++)
	{
		pm::SpriteBatch::GetInstance()->AddGameEntity(opaqueSpriteVector[i]->GetGameEntity());
	}

	for (int i = 0; i < spriteVector.size(); i++)
	{
		pm::SpriteBatch::GetInstance()->AddGameEntity(spriteVector[i]->GetGameEntity());
	}
}