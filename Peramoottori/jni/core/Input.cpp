#include "Input.h"
#include <android/input.h>

using namespace pm;

float Input::_x = 0;
float Input::_y = 0;
float Input::lx = 0;
float Input::ly = 0;
bool Input::touch = false;
bool Input::singleTouch = false;
bool Input::startOfDrag = false;
float Input::startOfDragX = 0;
float Input::startOfDragY = 0;
glm::vec3 Input::accelerometer = glm::vec3(0, 0, 0);

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
glm::vec2 Input::GetDragVector()
{
	if (touch == true && startOfDrag == false)
	{
		startOfDrag = true;
		return glm::vec2(0, 0);
	}
	return glm::vec2(_x - lx, _y - ly);
}
bool Input::IsTouching()
{
	return touch;
}
bool Input::GetSingleTouch()
{
	if (touch == true && singleTouch == false)
	{
		singleTouch = true;
		return true;
	}
	return false;
}

glm::vec3 Input::GetAccelerometerData()
{
	return accelerometer;
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
/// Static function used in Application.cpp
void Input::Update()
{
	lx = _x;
	ly = _y;
	
	if (touch == false)
	{
		singleTouch = false;
		startOfDrag = false;
	}
}
///Static function used in Application.cpp to get Accelerometer Data
void Input::InputEventAccelerometer(float x, float y, float z)
{
	accelerometer.x = x;
	accelerometer.y = y;
	accelerometer.z = z;
}