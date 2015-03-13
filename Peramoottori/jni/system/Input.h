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

		/// Updates the static parts at start of main loop. /-> Application.cpp
		/**
			\return Returns the last known touch coordinates as glm vec2.
		*/
		glm::vec2 GetTouchCoordinates();
		
		/// Updates the static parts at start of main loop. /-> Application.cpp
		/**
			\return Returns the drag vector that happened between last main loops as glm vec2.
		*/
		glm::vec2 GetDragVector();

		/// Checks if its the first time calling GetSingleTouch during touch.
		/**
			Single touch, will return true the first time called between touch down and touch up event.
			Resets the state when touch up is called.
			\return Returns true if called first time after a registered touch down event and before touch up event.
		*/
		bool GetSingleTouch();
		
		/// Updates the static parts at start of main loop. /-> Application.cpp
		/**
			\return Returns the current state of touch (up/down). Touching = true, not touching = false.
		*/
		bool IsTouching();


		/// Static member functions

		/// Updates the static parts at start of main loop. /-> Application.cpp
		/**
			Used in application class at start of each main loop. Dont use elsewhere.
		*/
		static void Update();
		/// Called when android touch event (AKEY_EVENT_ACTION_UP) is received on android side. /-> Application.cpp
		/**
			Given to the HandleInput communicating with android. Dont use elsewhere.
		*/
		static void InputEventKeyUp();
		/// Called when android touch event (AKEY_EVENT_ACTION_DOWN) is received on android side. /-> Application.cpp
		/**
			Given to the HandleInput communicating with android.  Dont use elsewhere.

		*/
		static void InputEventKeyDown();
		/// Called when android touch event (AINPUT_EVENT_TYPE_MOTION) is received on android side. /-> Application.cpp
		/**
			Given to the HandleInput communicating with android.  Dont use elsewhere.
			\param x The touch coordinate in X received from android.
			\param y The touch coordinate in Y received from android.
		*/
		static void InputEventMovement(float x, float y);

	private:
		/// Private variables(of multiple input systems if wanted)
		float dragX, dragY;
		/// Static member variables
		static bool touch, singleTouch, startOfDrag;
		static float startOfDragX, startOfDragY, _x, _y, lx, ly;
	};
}
#endif