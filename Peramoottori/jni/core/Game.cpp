#include "Game.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <core/Passert.h>

using namespace pm;
using namespace std;

std::size_t Game::instances = 0;

Game::Game() : Application()
{
	AddInstance();
}

Game::Game(android_app* application) : Application()
{
	AddInstance();
	Game::Initialize(application);
}

bool Game::Initialize(android_app* application)
{
	ASSERT_EQUAL(this->androidApplication, nullptr); // Assert if Game has already been initialized.

	Application::Initialize(application);
	
	if (this->androidApplication != nullptr)
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

	Application::ClearScreen();
}

void Game::SetClearColor(float red, float green, float blue)
{
	glClearColor(red, green, blue, 1.0f);
}

bool Game::IsReady()
{
	if (androidApplication != nullptr && window.HasContext()) // If Game has been initialized AND context is ready.
		return true;
	else
		return false;
}

bool Game::Update()
{
	/*if (!contextFunctions.empty() && IsReady())
	{
		for (vector<bool(*)()>::iterator it = contextFunctions.begin(); it != contextFunctions.end(); it++)
		{
			ASSERT(*it);
			it = contextFunctions.erase(it);
		}
	}*/

	return Application::Update();
}

void Game::Draw()
{
	if (!IsReady()) // Prematurely end Draw if everything is not prepared.
		return;

	Application::DrawFrame();
}

Game::~Game()
{
	instances--;
}

void Game::AddInstance()
{
	instances++;
	ASSERT_EQUAL(instances, std::size_t(1)); // Only one instance of Game should ever exist.
}