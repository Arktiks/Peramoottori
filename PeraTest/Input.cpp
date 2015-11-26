#include "Input.h"
#include <core\Application.h>

using namespace std;
#define APP pm::Application::GetInstance()

Input::Input() : Scene("Input")
{
	// Device screen dimensions.
	const int SCREEN_X = APP->window.GetResolution().x;
	const int SCREEN_Y = APP->window.GetResolution().y;
	const int SPACE = 200.0f; // Space between Boxes.
	const int BOXES = 20.0f; // Amount of Boxes to be drawn.

	int pos_x = SPACE; // Update position for new Boxes.
	int pos_y = SPACE;

	for (int i = 0; i < BOXES; i++)
	{
		boxes.push_back(Box());
		boxes[i].Transform()->SetPosition(pos_x, pos_y);
		//boxes[i].entity->GetComponent<pm::Transformable>()->SetPosition(pos_x, pos_y);
		pos_x += SPACE;
		
		if (pos_x >= SCREEN_X)
		{
			pos_x = SPACE;
			pos_y += SPACE;
		}
	}
}

Input::~Input()
{
}

void Input::Update()
{
	for (auto& box : boxes)
		box.Draw();
}