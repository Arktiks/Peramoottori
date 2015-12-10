#include "Drawables.h"
using namespace pm;

#include <core\Application.h>
#include <graphics\SpriteBatch.h>

#include <scene\GameEntity.h>
#include <graphics\Color.h>
#include <graphics\Rectangle.h>
#include <graphics\Drawable.h>
#include <scene\Transformable.h>
#include <resources\TextureFactory.h>
#include <scene\CameraSystem.h>
#include <core\Log.h>

#include <cstdlib> // Random generation.
#include <ctime>
#include <vector>

Drawables::Drawables() : Scene("Drawables"), rotation(0.0f), camera_direction(1), zoom_direction(1), camera(nullptr)
{
	// Initialise variables.
	std::srand(std::time(0));
	clock.Restart();

	const unsigned int WIN_X = Application::GetInstance()->window.GetResolution().x;
	const unsigned int WIN_Y = Application::GetInstance()->window.GetResolution().y;
	float location_x = 100.0f;
	float location_y = 100.0f;
	float scale_x = 1.0f;
	float scale_y = 1.0f;
	float size_x = MAX_WIDTH;
	float size_y = MAX_HEIGHT;

	DEBUG_INFO(("Setting Drawables camera."));

	camera = NEW Camera();
	CameraSystem::GetInstance()->SetActiveCamera(camera);

	for (int i = 0; i < SQUARES; i++)
	{
		entities.push_back(NEW GameEntity());
		entities[i]->AddComponent(NEW Color(glm::vec4(Random(), Random(), Random(), Random())));
		entities[i]->AddComponent(NEW Rectangle(size_x, size_y));
		entities[i]->GetComponent<Rectangle>()->SetOrigin(size_x * 0.5f, size_y * 0.5f);
		entities[i]->AddComponent(NEW Drawable);

		if ((i % 2) == 0)
		{
			entities[i]->AddComponent(NEW Transformable(glm::vec2(location_x, location_y), glm::vec2(scale_x, scale_y), 0.0f));
			entities[i]->AddComponent(TextureFactory::CreateTexture("DEF_TEXTURE_SMALL.png"));
		}
		else if ((i % 3) == 0)
		{
			entities[i]->AddComponent(NEW Transformable(glm::vec2(location_x, location_y), glm::vec2(scale_x * 0.8f, scale_y * 0.8f), 0.0f));
			entities[i]->AddComponent(TextureFactory::CreateTexture("BOX.png"));
		}
		else
		{
			entities[i]->AddComponent(NEW Transformable(glm::vec2(location_x, location_y), glm::vec2(scale_x * 0.5f, scale_y * 0.5f), 0.0f));
			entities[i]->AddComponent(TextureFactory::CreateTexture("DEF_TEXTURE.png"));
		}

		location_x += MAX_WIDTH;
		size_x = MAX_WIDTH - Random(50);
		size_y = MAX_HEIGHT - Random(50);

		if (location_x >= WIN_X)
		{
			location_x = 0;
			location_y += MAX_HEIGHT * 1.2f;
		}

		if (location_y >= WIN_Y)
			break;
	}
}

Drawables::~Drawables()
{
	DEBUG_INFO(("Clearing GameEntities."));
	for (auto it = entities.begin(); it != entities.end(); it++)
		delete (*it);

	DEBUG_INFO(("Creating new default Camera."));
	CameraSystem::GetInstance()->CreateDefaultCamera();

	DEBUG_INFO(("Deleting Drawables old Camera."));
	delete camera;
}

void Drawables::Pause()
{
	pause = true;
}

void Drawables::Resume()
{
	pause = false;
}

void Drawables::Update()
{
	// Change rotation of all entities.
	rotation += 0.1f;
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->GetComponent<Transformable>()->SetRotation(rotation);
		SpriteBatch::GetInstance()->AddOpaqueGameEntity(entities[i]);
	}

	// Move camera between two spots.
	if (clock.GetElapsedTime(Time::FRACTION::SECONDS) >= 2)
	{
		camera->MoveCamera(camera_direction * CAMERA_MOVE, 0);
		camera_direction *= -1;
		clock.Restart();
	}

	// Rotate and zoom camera periodically.
	camera->RotateCamera(0.1f);
	camera->ZoomCamera(0.01f * zoom_direction);

	if (camera->GetCameraZoom() >= 1.5f)
		zoom_direction = -1;
	if (camera->GetCameraZoom() <= 0.5f)
		zoom_direction = 1;
}

void Drawables::Initialise()
{
}

float Drawables::Random(int max)
{
	return (float)(rand() % max + 1);
}

float Drawables::Random()
{
	return (float)(rand() / (float)RAND_MAX);
}