#include "Input.h"
#include <core\Log.h>
using namespace pm;

//Static member variables
glm::vec3 Input::accelerometer = glm::vec3(0, 0, 0);
Input::Pointer Input::pointers[8];
int Input::pointerCount = 0;
int Input::incrPointerID = 1;

int32_t Input::AndroidEventHandler(AInputEvent* aEvent)
{
	int32_t action = AMotionEvent_getAction(aEvent);
	if (AInputEvent_getSource(aEvent) == AINPUT_SOURCE_TOUCHSCREEN)
	{
		switch (action & AMOTION_EVENT_ACTION_MASK)
		{
		case AMOTION_EVENT_ACTION_DOWN:
		case AMOTION_EVENT_ACTION_POINTER_DOWN:
		{
			int idx = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
				>> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;

			if (idx >= maxInputs)
				break;


			pointerCount++;

			if (incrPointerID > 10000)
				incrPointerID = 1;
			incrPointerID++;

			pointers[idx].sPos.x = AMotionEvent_getX(aEvent, idx);
			pointers[idx].sPos.y = AMotionEvent_getY(aEvent, idx);
			pointers[idx].index = idx;
			pointers[idx].id = incrPointerID;
			pointers[idx].singleTouch = true;
			pointers[idx].touching = true;
		}
		break;
		case AMOTION_EVENT_ACTION_MOVE:
		{
			const int count = AMotionEvent_getPointerCount(aEvent);

			for (int idx = 0; idx < count && idx < maxInputs; idx++)
			{
				pointers[idx].pos.x = AMotionEvent_getX(aEvent, idx);
				pointers[idx].pos.y = AMotionEvent_getY(aEvent, idx);
			}

		}
		break;
		case AMOTION_EVENT_ACTION_UP:
		case AMOTION_EVENT_ACTION_POINTER_UP:
		case AMOTION_EVENT_ACTION_CANCEL:
		case AMOTION_EVENT_ACTION_OUTSIDE:
		{
			int idx = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
				>> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;

			if (idx >= maxInputs)
				break;


			pointerCount--;

			pointers[idx].touching = false;
			pointers[idx].id = 0;
			pointers[idx].sPos.x = AMotionEvent_getX(aEvent, idx);
			pointers[idx].sPos.y = AMotionEvent_getY(aEvent, idx);

			for (unsigned int i = idx; i < maxInputs - 1; i++)
			{
				pointers[i].index = pointers[i + 1].index;
				pointers[i].sPos = pointers[i + 1].sPos;
			}

		}
		break;
		default:
			break;
		}
	}
	else if (AInputEvent_getSource(aEvent) == AINPUT_SOURCE_CLASS_BUTTON)
	{
		int key_code = AKeyEvent_getKeyCode(aEvent);
		switch (key_code)
		{
			case AKEYCODE_BACK:
				//Overriding System Back Button
				return 1;
				break;
			default:
				break;
		}
	}
	return 0;
}
int Input::GetPointerCount()
{
	return pointerCount;
}

Input::Pointer& Input::operator[](int index)
{
	if (index < maxInputs)
		return pointers[index];
	return pointers[maxInputs - 1];
}
bool Input::Pointer::GetSingleTouch()
{
	return singleTouch;
}
int Input::Pointer::GetID()
{
	return id;
}
 glm::vec2 Input::Pointer::GetPos()
{
	return pos;
}
 glm::vec2 Input::Pointer::GetStartPos()
{
	return sPos;
}
 bool Input::Pointer::IsTouching()
 {
	 return touching;
 }

 bool Input::UpdatePointer(int uniqueID, Input::Pointer& touch)
 {
	 for (int i = 0; i < maxInputs; i++)
	 {
		 if (pointers[i].GetID() == uniqueID)
		 {
			 touch = pointers[i];
			 return true;
		 }
	 }
	//pointer not found...
	touch = Pointer();
	return false;
 }

	 /**** Below are static functions used in Application.cpp ****/

void Input::InputEventAccelerometer(float x, float y, float z)
{
	accelerometer.x = x;
	accelerometer.y = y;
	accelerometer.z = z;
}

void Input::Update()
{

	for (int i = 0; i < maxInputs; i++)
	{

		if (!pointers[i].touching)
			for (unsigned int j = i; j < maxInputs - 1; j++)
			{
				pointers[j].index = pointers[j + 1].index;
				pointers[j].sPos = pointers[j + 1].sPos;
				pointers[j].id = pointers[j + 1].id;
				pointers[j].singleTouch = false;
			}
	}

}