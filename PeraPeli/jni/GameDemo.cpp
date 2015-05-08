#include "GameDemo.h"
#include "RNG.h"

#include "TailEntity.h"
#include <graphics\SpriteBatch.h>
#include <graphics\Drawable.h>
#include <graphics\Color.h>
#include <scene\GameEntity.h>

GameDemo::GameDemo()
{
	
}


GameDemo::~GameDemo()
{
}

void GameDemo::Initialize()
{
	soundBool = false;
	pm::Vector2<int> pmLimits = pm::Application::GetInstance()->window.GetResolution();
	limits.x = pmLimits.x;
	limits.y = pmLimits.y;

	holdingBall = false;

	touchAudio = NEW pm::Audio("0477.ogg");
	touchAudio->SetMaxPlayerCount(10);
	touchAudio->SetVolume(1);

	music = NEW pm::Audio("LGMThePortal.ogg");
	music->SetLooping(true);
	music->SetVolume(50);
	music->Play();

	pm::Texture* pointTexture = pm::TextureFactory::CreateTexture("point.png");
	pm::Texture* groundTexture = pm::TextureFactory::CreateTexture("groundTexture.png");
	pm::Texture* footBallTexture = pm::TextureFactory::CreateTexture("Football.png");
	pm::Texture* spiralTexture = pm::TextureFactory::CreateTexture("spiral.png");
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

	SpriteObject* spiral = new SpriteObject(spiralTexture);
	spiral->SetOrigin(400, 400);
	spiral->SetPosition(256, 256);
	spiral->SetSize(128, 128);
	spiral->SetDepth(5);
	opaqueSpriteMap["spiral"] = spiral;
	

	time.CalculateTimeInFrame();
}
void GameDemo::Update()
{
	SpriteObject* obj = opaqueSpriteMap["spiral"];
	assert( obj != 0);
	obj->SetRotation(obj->GetRotation() - 1);
	ColorRNG(obj);

	// Update physics every two seconds
	if (time.CalculateTimeInFrame() > 2.0f)
		BallPhysics(opaqueSpriteMap["ball"]);
	
	InputUpdate();
	Draw();
}

void GameDemo::Draw()
{
	std::map<std::string, SpriteObject*>::iterator it;

	for (it = spriteMap.begin(); it != spriteMap.end(); it++)
		pm::SpriteBatch::GetInstance()->AddGameEntity(it->second);

	for (it = opaqueSpriteMap.begin(); it != opaqueSpriteMap.end(); it++)
		pm::SpriteBatch::GetInstance()->AddOpaqueGameEntity(it->second);
}

void GameDemo::InputUpdate()
{
	if (input.IsTouching())
	{
		glm::vec2 touchPosition = glm::vec2(input.GetTouchCoordinates().x - 40, input.GetTouchCoordinates().y);

		opaqueSpriteMap["point"]->SetDrawState(true);
		opaqueSpriteMap["point"]->SetPosition(touchPosition);

		if (CheckTouch(touchPosition, spriteMap["touchArea1"]))
		{
			spriteMap["touchArea1"]->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
			spriteMap["touchArea2"]->SetColor(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
			if (soundBool)
			{
				touchAudio->Play();
				soundBool = false;
			}
		}

		if (CheckTouch(touchPosition, spriteMap["touchArea2"]))
		{
			spriteMap["touchArea1"]->SetColor(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
			spriteMap["touchArea2"]->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
			if (!soundBool)
			{
				touchAudio->Play();
				soundBool = true;
			}
		}
		if (CheckTouch((touchPosition + opaqueSpriteMap["ball"]->GetOrigin()), opaqueSpriteMap["ball"]))
		{
			holdingBall = true;
		}

		if (holdingBall)
		{
			glm::vec2 dragVector = input.GetDragVector();
			dragVector.x = dragVector.x / 3;
			dragVector.y = dragVector.y / 3;
			opaqueSpriteMap["ball"]->SetVelocity(dragVector);
			opaqueSpriteMap["ball"]->SetPosition(touchPosition.x, touchPosition.y);
		}
	}
	else
	{
		opaqueSpriteMap["point"]->SetDrawState(false);
		holdingBall = false;
	}

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
	CheckLimits(target);

	target->SetRotation(target->GetRotation() + target->GetVelocity().x);
	target->SetPosition(target->GetPosition() + target->GetVelocity());
}

void GameDemo::CheckLimits(SpriteObject* target)
{
	if (target->GetPosition().x - target->GetSize().x/2 < 0)
	{
		target->SetPosition(target->GetSize().x / 2, target->GetPosition().y);
		target->SetVelocity(glm::vec2(target->GetVelocity().x * -0.8f, target->GetVelocity().y));
	}
	else if (target->GetPosition().x > limits.x - target->GetSize().x/2)
	{
		target->SetPosition(limits.x - target->GetSize().x / 2, target->GetPosition().y);
		target->SetVelocity(glm::vec2(target->GetVelocity().x * -0.8f, target->GetVelocity().y));
	}

	if (target->GetPosition().y > limits.y - target->GetSize().y/2)
	{
		target->SetVelocity(glm::vec2(target->GetVelocity().x, target->GetVelocity().y * -0.8f));
		target->SetPosition(glm::vec2(target->GetPosition().x, limits.y - target->GetSize().y / 2));
	}
	else
	{
		target->SetVelocity(glm::vec2(target->GetVelocity().x, target->GetVelocity().y + 0.1f));
	}
}

float CheckMinMax(float color)
{
	if (color < 0.00f)
		return 0.01f;
	else if (color > 1.00f)
		return 0.99f;
	else
		return color;
}

void GameDemo::ColorRNG(SpriteObject* target)
{
	glm::vec4 newColor = target->GetColor();

	int plusOrMinus = 1;
	if (RNG::Random(1))
		plusOrMinus = -1;
	
	newColor.r += static_cast<float>(RNG::RandomNotZero(100)) / 1000 * plusOrMinus;
	newColor.b += static_cast<float>(RNG::RandomNotZero(100)) / 1000 * plusOrMinus;
	newColor.g += static_cast<float>(RNG::RandomNotZero(100)) / 1000 * plusOrMinus;


	newColor.r = CheckMinMax(newColor.r);
	newColor.b = CheckMinMax(newColor.b);
	newColor.g = CheckMinMax(newColor.g);


	target->SetColor(newColor);
}

void GameDemo::TailFunction(SpriteObject* target)
{

}