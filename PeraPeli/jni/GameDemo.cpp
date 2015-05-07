#include "GameDemo.h"


GameDemo::GameDemo()
{
	
}


GameDemo::~GameDemo()
{
}

void GameDemo::Initialize()
{
	holdingBall = false;

	touchAudio = NEW pm::Audio("0477.ogg");
	touchAudio->SetMaxPlayerCount(10);

	pm::Texture* pointTexture = pm::TextureFactory::CreateTexture("point.png");
	pm::Texture* groundTexture = pm::TextureFactory::CreateTexture("groundTexture.png");
	pm::Texture* footBallTexture = pm::TextureFactory::CreateTexture("Football.png");
	textureMap["point"] = pointTexture;
	textureMap["ground"] = groundTexture;

	SpriteObject* pointSprite = new SpriteObject(pointTexture);
	opaqueSpriteMap["point"] = pointSprite;
	pointSprite->SetDepth(3);
	pointSprite->SetSize(200, 300);
	pointSprite->SetOrigin(40, 40);

	SpriteObject* rotationBall = new SpriteObject(footBallTexture);
	rotationBall->AddPhysics();
	opaqueSpriteMap["ball"] = rotationBall;
	rotationBall->SetDepth(2);
	rotationBall->SetSize(128.0f, 128.0f);
	rotationBall->SetColor(glm::vec4(0.5f, 1.0f, 0, 0));
	rotationBall->SetOrigin(64.0f, 64.0f);
	rotationBall->SetPosition(100.0f, 100.0f);
	rotationBall->SetVelocity(glm::vec2(2.0f, 3.0f));

	SpriteObject* groundSprite = new SpriteObject(groundTexture);
	spriteMap["ground"] = groundSprite;
	groundSprite->SetDepth(2);
	groundSprite->SetPosition(500, 500);
	groundSprite->SetSize(1000, 100);
	groundSprite->SetRotation(5.0f);


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
	BallPhysics(opaqueSpriteMap["ball"]);
	if (input.IsTouching())
	{
		glm::vec2 touchPosition = input.GetTouchCoordinates();

		opaqueSpriteMap["point"]->SetDrawState(true);
		opaqueSpriteMap["point"]->SetPosition(touchPosition);

		if (CheckTouch(touchPosition, spriteMap["touchArea1"]))
		{
			spriteMap["touchArea1"]->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
			spriteMap["touchArea2"]->SetColor(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
			touchAudio->Play();
		}

		if (CheckTouch(touchPosition, spriteMap["touchArea2"]))
		{
			spriteMap["touchArea1"]->SetColor(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
			spriteMap["touchArea2"]->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
			touchAudio->Play();
		}
		if (CheckTouch(touchPosition, opaqueSpriteMap["ball"]))
		{
			holdingBall = true;
		}

		if (holdingBall)
		{
			glm::vec2 dragVector = input.GetDragVector();
			dragVector.x = dragVector.x / 5;
			dragVector.y = dragVector.y / 5;
			opaqueSpriteMap["ball"]->SetVelocity(dragVector);
			opaqueSpriteMap["ball"]->SetPosition(touchPosition.x, touchPosition.y);
		}
	}
	else
	{
		opaqueSpriteMap["point"]->SetDrawState(false);
		holdingBall = false;
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

void GameDemo::BallPhysics(SpriteObject* target)
{
	if (target->GetPosition().y > 680)
	{
		target->SetVelocity(glm::vec2(target->GetVelocity().x, 0));
		target->SetPosition(glm::vec2(target->GetPosition().x, 680));
	}
	else
	{
		target->SetVelocity(glm::vec2(target->GetVelocity().x, target->GetVelocity().y + 0.1f));
	}
	target->SetRotation(target->GetRotation() + target->GetVelocity().x);
	target->SetPosition(target->GetPosition() + target->GetVelocity());
}