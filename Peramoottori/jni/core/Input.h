#ifndef INPUT_H
#define INPUT_H

#include <glm\vec2.hpp>
#include <glm\vec3.hpp>

namespace pm
{
	/// Input objects are used to access the input data provided by Android API.
	/**
	* Only functionality that requires multiple input objects are separate checks for Single Touch.
	* The engine uses the static functions to deliver input data from the API to all input objects.
	* You can use these static functions to force feed specific input data to the input objects.
	* This should be used with extreme caution since it can interfere with other Input functionalities.
	*/

	class Input
	{
	public:

		Input() : dragX(0), dragY(0) {};
		~Input() {};

		/// Returns the current touch coordinates.
		/**
			\return Returns the last known touch coordinates as glm vec2.
		*/
		glm::vec2 GetTouchCoordinates();
		
		/// Returns the length vector from start of the drag to current touch position.
		/**
			\return Returns the drag vector that happened between last main loops as glm vec2.
		*/
		glm::vec2 GetDragVector();

		/// Returns accelerometer data
		/**
			\return Returns accelerometer data as glm vec3.
		*/
		glm::vec3 GetAccelerometerData();

		/// Checks if its the first time calling GetSingleTouch during touch.
		/**
			Single touch will return true the first time called between touch down and touch up event.
			Automatically resets the state when touch up is called by the Android API.
			\return Returns true if called first time after a registered touch down event and before touch up event.
		*/
		bool GetSingleTouch();
		
		/// Returns the current state of touch.
		/**
			\return Returns the current state of touch (up/down). Touching = true, not touching = false.
		*/
		bool IsTouching();

		/** @name Restricted Static Public Member Functions
		* Following static functions have already been implemented in Application class. User is not recommended
		* use of them unless he is 100% confident of their purpose.
		*/
		///@{
		/** \brief Updates static variables at start of each engine main loop.
		*
		* Used in Application class at start of each main loop.
		*/
		static void Update();

		/** \brief Called when android touch event (AKEY_EVENT_ACTION_UP) is received on android side.
		*
		* Given to the HandleInput communicating with android.
		*/
		static void InputEventKeyUp();

		/** \brief Called when android touch event (AKEY_EVENT_ACTION_DOWN) is received on android side.
		*
		* Given to the HandleInput communicating with android.
		*/
		static void InputEventKeyDown();

		/** \brief Called when android touch event (AINPUT_EVENT_TYPE_MOTION) is received on android side.
		*
		* Given to the HandleInput communicating with android.
		* \param x The touch coordinate in X received from android.
		* \param y The touch coordinate in Y received from android.
		*/
		static void InputEventMovement(float x, float y);

		/** \brief Called in Application::Update() to receive accelerometer data. 
		*
		* \param accelerometer The accelerometer data to be given to Input.
		*/
		static void InputEventAccelerometer(float x, float y, float z);
		///@}

	private:

		/// Private variables, of multiple input systems if wanted.
		float dragX, dragY;

		/// Static member variables.
		static bool touch, singleTouch, startOfDrag;
		static float startOfDragX, startOfDragY, _x, _y, lx, ly;
		static glm::vec3 accelerometer;
	};
}

#endif