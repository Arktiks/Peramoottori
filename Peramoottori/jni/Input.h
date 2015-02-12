#ifndef INPUT_H
#define INPUT_H

#include "Application.h"
#include "glm\vec2.hpp"
namespace PM
{
	class Input
	{
	public:
		Input();
		~Input();
		void Initialize(Application::Engine* engineHandle);

		glm::vec2 ReturnTouchCoords();
		glm::vec2 ReturnLastTouchCoords();
		glm::vec2 GetDragVector();
		bool IsTouching();
		bool SingleTouch();

	private:
		Application::Engine* engine;
		bool singleTouch;
		
	};
}
#endif