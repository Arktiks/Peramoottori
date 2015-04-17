#include "Game.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <core/Log.h>
#include <core/Passert.h>
#include <core/Memory.h>
#include <resources/TextureFactory.h>
#include <graphics/RenderSystem.h>

using namespace pm;
using namespace std;

Game* Game::instance = nullptr;

Game* Game::GetInstance()
{
	if (instance == nullptr) // If instance has not been initialized yet.
		instance = NEW Game;
	return instance;
}

void Game::DestroyInstance()
{
	delete instance;
	instance = nullptr;
	DEBUG_INFO(("Game instance deleted."));
}

bool Game::Initialize(android_app* application)
{
	Application::Initialize(application);
	
	//SetClearColor(1.0f, 0.4f, 1.0f); // Set default clear color.

	if (this->androidApplication != nullptr)
	{
		initialized = true;
		return true;
	}
	else
		return false;
}

bool Game::IsReady()
{
	if (androidApplication != nullptr && window.HasContext()) // If Game has been initialized and device context is ready.
		return true;
	else
		return false;
}

Vector2<int> Game::GetResolution()
{
	return window.GetResolution();
}

void Game::Clear()
{
	if (!IsReady())
		return;

	GLfloat tempColors[4];
	glGetFloatv(GL_COLOR_CLEAR_VALUE, tempColors);



	Application::Clear();
}

void Game::SetClearColor(float red, float green, float blue)
{
	glClearColor(red, green, blue, 1.0f);
}

bool Game::Update()
{
	return Application::Update();
}

void Game::Draw()
{
	if (!IsReady()) // Prematurely end function if everything is not prepared.
		return;
	rotation += 0.01;
	for (int i = 0; i < entityVector.size(); i++)
	{
		entityVector[i]->GetComponent<Transformable>()->SetRotation(rotation * i);
		SpriteBatch::GetInstance()->AddGameEntity(entityVector[i]);

	}

	SpriteBatch::GetInstance()->Draw();

	Application::SwapBuffers();
}

void Game::InitializeGame()
{
	RenderSystem::GetInstance()->Initialize();
	rotation = 0; 

	entityVector.push_back(NEW GameEntity());
	entityVector[0]->AddComponent(NEW Rectangle(64, 64));
	entityVector[0]->GetComponent<Rectangle>()->SetOrigin(32, 32);
				 
	entityVector[0]->AddComponent(NEW Transformable());
	entityVector[0]->GetComponent<Transformable>()->SetPosition(200, 200);
	entityVector[0]->GetComponent<Transformable>()->SetRotation(0);
	entityVector[0]->GetComponent<Transformable>()->SetScale(1, 1);
				 
	entityVector[0]->AddComponent(NEW Drawable());
	entityVector[0]->GetComponent<Drawable>()->SetDrawState(true);
				 
	entityVector[0]->AddComponent(TextureFactory::CreateTexture("test1.png"));


	//for (int i = 0; i < 10; i++)
	//{
	//	for (int j = 0; j < 10; j++)
	//	{
	//		entityVector.push_back(NEW GameEntity());
	//		entityVector[i*10 + j]->AddComponent(NEW Rectangle(64, 64));
	//		entityVector[i*10 + j]->GetComponent<Rectangle>()->SetOrigin(32, 32);
	//
	//		entityVector[i*10 + j]->AddComponent(NEW Transformable());
	//		entityVector[i*10 + j]->GetComponent<Transformable>()->SetPosition(120*i, 70*j);
	//		entityVector[i*10 + j]->GetComponent<Transformable>()->SetRotation(rotation*(i*10+j));
	//		entityVector[i*10 + j]->GetComponent<Transformable>()->SetScale(1, 1);
	//
	//		entityVector[i*10 + j]->AddComponent(NEW Drawable());
	//		entityVector[i*10 + j]->GetComponent<Drawable>()->SetDrawState(true);
	//		//if ((i*10 + j) % 2)
	//		//	entityVector[i*10 + j]->AddComponent(TextureFactory::CreateTexture("test1.png"));
	//		//else
	//			entityVector[i * 10 + j]->AddComponent(TextureFactory::CreateTexture("test1.png"));
	//	}
	//}
	/////////////////////////////////////////////////////////////
}

void Game::UpdateGame()
{
}
