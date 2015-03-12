#include "Input.h"
#include <android/input.h>

using namespace pm;

float Input::_x = 0;
float Input::_y = 0;
float Input::lx = 0;
float Input::ly = 0;
bool Input::touch = false;
float Input::startOfDragX = 0;
float Input::startOfDragY = 0;

Input::Input()
{
	dragX = 0;
	dragY = 0;
}
Input::~Input()
{
}

glm::vec2 Input::GetTouchCoordinates()
{
	return glm::vec2(_x, _y);
}

bool Input::IsTouching()
{
	return touch;
}


/// Static functions used in Application.cpp 
void Input::InputEventMovement(float x, float y)
{
	_x = x;
	_y = y;
}
/// Static functions used in Application.cpp 
void Input::InputEventKeyDown()
{
	touch = true;
	startOfDragX = _x;
	startOfDragY = _y;
}
/// Static functions used in Application.cpp 
void Input::InputEventKeyUp()
{
	touch = false;
}
void Input::Update()
{
	lx = _x;
	ly = _y;

}