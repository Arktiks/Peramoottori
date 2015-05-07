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
	touchAudio->SetMaxPlayerCount(3);

	pm::Texture* pointTexture = pm::TextureFactory::CreateTexture("point.png");
	pm::Texture* groundTexture = pm::TextureFactory::CreateTexture("groundTexture.png");

	textureMap["point"] = pointTexture;
	textureMap["ground"] = groundTexture;

	SpriteObject* pointSprite = new SpriteObject(pointTexture);
	opaqueSpriteMap["point"] = pointSprite;
	pointSprite->SetDepth(3);
	pointSprite->SetSize(200, 300);
	pointSprite->SetOrigin(30, 0);


	SpriteObject* groundSprite = new SpriteObject(groundTexture);
	spriteMap["ground"] = groundSprite;
	groundSprite->SetDepth(2);
	groundSprite->SetPosition(500, 500);
	groundSprite->SetSize(1000, 100);
	groundSprite->SetRotation(5.0f);


	pointSprite->SetDepth(5);
	SpriteObject* touchSprite1 = new SpriteObject();
	spriteMap["touchArea1"] = touchSprite1;
	touchSprite1->SetColor(glm::vec4(0, 0, 1, 0));
	touchSprite1->SetDepth(5);
	touchSprite1->SetPosition(0, 500);
	touchSprite1->SetSize(200, 200);

	SpriteObject* touchSprite2 = new SpriteObject();
	spriteMap["touchArea2"] = touchSprite2;
	touchSprite2->SetColor(glm::vec4(0, 0, 1, 0));
	touchSprite2->SetDepth(10);
	touchSprite2->SetPosition(900, 500);
	touchSprite2->SetSize(200, 200);
}
void GameDemo::Update()
{
	glm::vec2 touchPosition = input.GetTouchCoordinates();
	opaqueSpriteMap["point"]->SetPosition(touchPosition);

	int area = CheckTouch(touchPosition);

	if (area == 1)
	{
		spriteMap["touchArea1"]->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
		spriteMap["touchArea2"]->SetColor(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
		touchAudio->Play();
	}
	if (area == 2)
	{
		spriteMap["touchArea1"]->SetColor(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
		spriteMap["touchArea2"]->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
		touchAudio->Play();
	}

	Draw();
}

void GameDemo::Draw()
{
	std::map<std::string, SpriteObject*>::iterator it;

	for (it = spriteMap.begin(); it != spriteMap.end(); it++)
		pm::SpriteBatch::GetInstance()->AddGameEntity(it->second);

	for (it = opaqueSpriteMap.begin(); it != opaqueSpriteMap.end(); it++)
		pm::SpriteBatch::GetInstance()->AddGameEntity(it->second);


}

int GameDemo::CheckTouch(glm::vec2 touch)
{
	glm::vec2 positionOne = spriteMap["touchArea1"]->GetPosition();
	glm::vec2 sizeOne = spriteMap["touchArea1"]->GetSize();

	glm::vec2 positionTwo = spriteMap["touchArea2"]->GetPosition();
	glm::vec2 sizeTwo = spriteMap["touchArea2"]->GetSize();
	
	if (positionOne.x < touch.x && sizeOne.x > touch.x)
		if (positionOne.y < touch.y && sizeOne.y > touch.y)
			return 1;
	if (positionTwo.x < touch.x && sizeTwo.x > touch.x)
		if (positionTwo.y < touch.y && sizeTwo.y > touch.y)
			return 2;
	return 0;
}