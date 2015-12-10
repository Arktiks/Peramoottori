#include "Input.h"
#include <core\Application.h>
#include <core\Profiler.h>
#include <scene\Hitbox.h>

using namespace std;
#define APP pm::Application::GetInstance()

Input::Input() : Scene("Input")
{
	// Device screen dimensions.
	const int SCREEN_X = APP->window.GetResolution().x;
	const int SCREEN_Y = APP->window.GetResolution().y;
	const float SPACE = 250.0f; // Space between Boxes.
	const int BOXES = 10; // Amount of Boxes to be drawn.

	float pos_x = 100.f; // Update position for new Boxes.
	float pos_y = 100.f;

	for (int i = 0; i < BOXES; i++) // Initialise touchable boxes.
	{
		Box* box = new Box();
		box->Transform()->SetPosition(pos_x, pos_y);
		box->entity->AddComponent(new pm::Hitbox());
		boxes.push_back(box);

		pos_x += SPACE;
		if (pos_x + 100.f >= SCREEN_X)
		{
			pos_x = 100.f;
			pos_y += SPACE;
		}
	}

	box_amount = BOXES;
}

Input::~Input()
{
	for (auto it = boxes.begin(); it != boxes.end(); it++)
		delete (*it);
}

void Input::Update()
{
	/* Destroy boxes that are touched. */
	for (int i = 0; i < input.GetPointerCount(); i++)
	{
		if (input[i].IsTouching())
		{
			for (auto it = boxes.begin(); it != boxes.end(); )
			{
				if ((*it)->entity->GetComponent<pm::Hitbox>()->CheckCollision(input[i].GetPos()))
					/*(*it)->Contains(input[i].GetPos()))*/
				{
					delete (*it);
					it = boxes.erase(it);
					box_amount--;
				}
				else
					it++;
			}
		}
	}

	for (auto& box : boxes) // Draw boxes.
		box->Draw();
}