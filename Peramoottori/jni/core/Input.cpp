#include "Input.h"
#include <android/input.h>
#include "Pointer.h"
using namespace pm;

//Static member variables
glm::vec3 Input::accelerometer = glm::vec3(0, 0, 0);
std::vector<Pointer*> Input::pointers;


bool Input::CheckPointer(int id)
{
	for (auto &_pointer : pointers)
		if (_pointer->GetID() == id)
			return true;
	return false;

}

void Input::NewPointer(int id, float x, float y)
{
	pointers.push_back(new Pointer(id, x, y));
}

void Input::RemovePointer(int id)
{
	std::vector<Pointer*>::iterator it;
	for (it = pointers.begin(); it != pointers.end(); it++)
		if ((*it)->GetID() == id)
			pointers.erase(it);
}

void Input::NoPointers()
{
	pointers.clear();
}

void Input::MovePointer(int id, float x, float y)
{
	for (auto &_pointer : pointers)
		if (_pointer->GetID() == id)
		{
			_pointer->SetLastPos(_pointer->GetPos().x, _pointer->GetPos().y);
			_pointer->SetPos(x, y);
		}
}


/////////////////////////////////////
/*Everything from before the rework*/
/////////////////////////////////////

glm::vec2 Input::GetTouchCoordinates()
{
	return glm::vec2((*pointers.begin())->x, (*pointers.begin())->y);
}

glm::vec3 Input::GetAccelerometerData()
{
	return accelerometer;
}


bool Input::Touch()
{
	if (pointers.begin() != pointers.end())
		return true;
	return false;
}

/**** Below are static functions used in Application.cpp ****/

void Input::InputEventAccelerometer(float x, float y, float z)
{
	accelerometer.x = x;
	accelerometer.y = y;
	accelerometer.z = z;
}