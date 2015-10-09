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
std::vector<Pointer*> Input::pointers;


bool Input::CheckPointer(int id)
{
	for (auto &_pointer : pointers)
		if (_pointer->id == id)
			return true;
	return false;

}

void Input::NewPointer(int id, float x, float y)
{
	Pointer* newPointer = new Pointer();
	newPointer->id = id;
	newPointer->sx = x;
	newPointer->sy = y;
	newPointer->x = x;
	newPointer->y = y;
	newPointer->lx = 0;
	newPointer->ly = 0;
	pointers.push_back(newPointer);

}

void Input::RemovePointer(int id)
{
	std::vector<Pointer*>::iterator it;
	for (it = pointers.begin(); it != pointers.end(); it++)
		if ((*it)->id == id)
			pointers.erase(it);
}

void Input::NoPointers()
{
	pointers.clear();
}

void Input::MovePointer(int id, float x, float y)
{
	for (auto &_pointer : pointers)
		if (_pointer->id == id)
		{
			_pointer->lx = _pointer->x;
			_pointer->ly = _pointer->y;
			_pointer->x = x;
			_pointer->y = y;
		}
}


/////////////////////////////////////
/*Everything from before the rework*/
/////////////////////////////////////

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

glm::vec3 Input::GetAccelerometerData()
{
	return accelerometer;
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

bool Input::IsTouching()
{
	return touch;
}

/**** Below are static functions used in Application.cpp ****/

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

void Input::InputEventKeyUp()
{
	touch = false;
}

void Input::InputEventKeyDown()
{
	touch = true;
	startOfDragX = _x;
	startOfDragY = _y;
}

void Input::InputEventMovement(float x, float y)
{
	_x = x;
	_y = y;
}

void Input::InputEventAccelerometer(float x, float y, float z)
{
	accelerometer.x = x;
	accelerometer.y = y;
	accelerometer.z = z;
}