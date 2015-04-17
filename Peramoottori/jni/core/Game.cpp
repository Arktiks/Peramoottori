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

	SpriteBatch::GetInstance()->AddGameEntity(&gameEntity);
	SpriteBatch::GetInstance()->Draw();

	Application::SwapBuffers();
}

void Game::InitializeGame()
{
	DEBUG_WARNING(("glGetError game line 91: %i", glGetError()));
	RenderSystem::GetInstance()->Initialize();

	DEBUG_WARNING(("glGetError game line 94: %i", glGetError()));
	gameEntity.AddComponent(NEW Rectangle(100, 200));

	DEBUG_WARNING(("glGetError game line 97: %i", glGetError()));
	gameEntity.AddComponent(NEW Transformable());
	gameEntity.GetComponent<Transformable>()->SetPosition(400, 200);

	DEBUG_WARNING(("glGetError game line 101: %i", glGetError()));
	gameEntity.AddComponent(NEW Drawable());
	gameEntity.GetComponent<Drawable>()->SetDrawState(true);
	DEBUG_WARNING(("glGetError game line 104: %i", glGetError()));
	gameEntity.AddComponent(TextureFactory::CreateTexture("test.png"));
	DEBUG_WARNING(("glGetError game line 106: %i", glGetError()));
}

void Game::UpdateGame()
{
}
