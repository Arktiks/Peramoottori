#include "Input.h"
using namespace pm;

Input::Input()
{
}

Input::~Input()
{
}

bool Input::IsTouching()
{
	return touch;
}

bool Input::SingleTouch()
{
	return singleTouch;
}

/// Static functions used in Application.cpp 
void Input::InputEvent(float X, float Y)
{
	touch = true;
	x = X;
	y = Y;
}

void Input::Update()
{
	if (touch == true)
		singleTouch = false;
	else
		singleTouch = true;

	touch = false;

	lx = x; 
	ly = y;
}