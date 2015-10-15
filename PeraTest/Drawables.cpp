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

#include <cstdlib> // Random generation.
#include <ctime>

Drawables::Drawables() : Scene("Drawables"), rotation(0.0f)
{
	/* Variables used in initialisation. */
	std::srand(std::time(0));
	const unsigned int WIN_X = Application::GetInstance()->window.GetResolution().x;
	const unsigned int WIN_Y = Application::GetInstance()->window.GetResolution().y;
	float location_x = 100.0f;
	float location_y = 100.0f;
	float scale_x = 1.0f;
	float scale_y = 1.0f;
	float size_x = MAX_WIDTH;
	float size_y = MAX_HEIGHT;

	for (int i = 0; i < SQUARES; i++)
	{
		entities.push_back(NEW GameEntity());
		entities[i]->AddComponent(NEW Transformable(glm::vec2(location_x, location_y), glm::vec2(scale_x, scale_y), 0.0f));
		entities[i]->AddComponent(NEW Color(glm::vec4(Random(), Random(), Random(), Random())));

		if ((i % 2) == 0)
			entities[i]->AddComponent(TextureFactory::CreateTexture("DEF_TEXTURE_SMALL.png"));
		else
			entities[i]->AddComponent(TextureFactory::CreateTexture("DEF_TEXTURE.png"));

		entities[i]->AddComponent(NEW Rectangle(size_x, size_y));
		entities[i]->AddComponent(NEW Drawable);

		/* Vary drawables between creating them. */
		location_x += MAX_WIDTH;
		scale_x = Random() + Random();
		scale_y = Random() + Random();
		size_x = Random(MAX_WIDTH);
		size_y = Random(MAX_HEIGHT);

		if (location_x >= WIN_X) // Next row.
		{
			location_x = 0;
			location_y += MAX_HEIGHT * 1.2f;
		}

		if (location_y >= WIN_Y) // Screen is full.
			break;
	}
}

Drawables::~Drawables()
{
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
	rotation += 0.1f;
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->GetComponent<Transformable>()->SetRotation(rotation);
		SpriteBatch::GetInstance()->AddGameEntity(entities[i]);
	}
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