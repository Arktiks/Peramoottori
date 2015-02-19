#ifndef INPUT_H
#define INPUT_H

#include "glm\vec2.hpp"
namespace pm
{
	class Input
	{
	public:
		Input();
		~Input();

		/// Change to suitable vec2?
		void GetTouchCoordinates();

		bool IsTouching();


		/// Works only once per loop reliably per input system.
		bool SingleTouch();

		/// Static member functions

		/// Updates the static parts at start of main loop. /-> Application.cpp
		static void Update();
		/// Called when android touch event is received on android side. /-> Application.cpp
		static void InputEvent(float X, float Y);

	private:
		/// Private variables(of multiple input systems if wanted)
		
		/// Static member variables
		static bool touch;
		static bool singleTouch;
		static float x, y, lx, ly;
	};
}
#endif