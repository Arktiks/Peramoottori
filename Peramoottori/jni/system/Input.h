#ifndef INPUT_H
#define INPUT_H

#include "glm\vec2.hpp"
namespace pm
{
	/// Need to decide wether we will make this class partialy or completely static
	class Input
	{
	public:
		Input();
		~Input();

		glm::vec2 GetTouchCoordinates();
		bool IsTouching();


		/// Static member functions

		/// Updates the static parts at start of main loop. /-> Application.cpp
		static void Update();
		/// Called when android touch event (AKEY_EVENT_ACTION_UP) is received on android side. /-> Application.cpp
		static void InputEventKeyUp();
		/// Called when android touch event (AKEY_EVENT_ACTION_DOWN) is received on android side. /-> Application.cpp
		static void InputEventKeyDown();
		/// Called when android touch event (AINPUT_EVENT_TYPE_MOTION) is received on android side. /-> Application.cpp
		static void InputEventMovement(float x, float y);

	private:
		/// Private variables(of multiple input systems if wanted)
		float dragX, dragY;

		/// Static member variables
		static bool touch;
		static float startOfDragX, startOfDragY, _x, _y, lx, ly;
	};
}
#endif