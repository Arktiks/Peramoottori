#include "Input.h"

using namespace PM;

Input::Input()
{
	engine = nullptr;
	singleTouch = false;
}
Input::~Input()
{
}
void Input::Initialize(Application::Engine* engineHandle)
{
	engine = engineHandle;
}
glm::vec2 Input::ReturnTouchCoords()
{
	return glm::vec2(engine->x, engine->y);
}
glm::vec2 Input::ReturnLastTouchCoords()
{
	return glm::vec2(engine->lx, engine->ly);
}
bool Input::IsTouching()
{
	return engine->touch;
}
glm::vec2 Input::GetDragVector()
{
	float dx = engine->x - engine->lx;
	float dy = engine->y - engine->ly;

	return glm::vec2(dx, dy);
}
bool Input::SingleTouch()
{
	if (engine->touch && !singleTouch)
	{
		singleTouch = true;
		return true;
	}
	else if (!engine->touch && singleTouch)
	{
		singleTouch = false;
	}
	return false;
}