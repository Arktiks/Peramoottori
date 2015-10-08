#ifndef INPUT_H
#define INPUT_H

#include <glm\vec2.hpp>
#include <glm\vec3.hpp>

namespace pm
{
	/** \brief %Input objects are used to access the input data provided by Android API.
	*
	* Only functionality that requires multiple input objects are separate checks for single touch.
	* The engine uses static functions to deliver input data from API to all input objects.
	* You can use these static functions to force feed specific input data to the input objects.
	* This should be used with extreme caution since it can interfere with other Input functionalities.
	*
	* \ingroup Core
	*/
	struct Pointer
	{
		int id, x, y, sx, sy, lx, ly;
	};

	class Input
	{
	public:

		Input() : dragX(0), dragY(0) {};

		~Input() {};

		/** \brief Returns current touch coordinates.
		* \return Last known touch coordinate as glm::vec2.
		*/
		glm::vec2 GetTouchCoordinates();
		
		/** \brief Returns length vector from start of the drag to current touch position.
		* \return Drag vector that happened between last main loops as glm::vec2.
		*/
		glm::vec2 GetDragVector();

		/** \brief Returns accelerometer data.
		* \return Accelerometer data as glm::vec3.
		*/
		glm::vec3 GetAccelerometerData();

		/** \brief Checks if its the first time calling GetSingleTouch during touch.
		*
		* Single touch will return true the first time called between touch down and touch up event.
		* Automatically resets the state when touch up is called by the Android API.
		* \return true if called first time after registered touch down event and before touch up event.
		*/
		bool GetSingleTouch();
		
		/** \brief Returns current state of touch.
		* \return true if touching.
		* \return false if not touching. 
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
		* \param accelerometer Accelerometer data to be given to Input.
		*/
		static void InputEventAccelerometer(float x, float y, float z);
		///@}


		/////////////////////////////////////
		///*Everything done for the rework*//
		/////////////////////////////////////

		/** \brief Check if the pointer exists by the ID.
		* \param id Pointer ID from AMotionEvent_getPointerId.
		*/
		static bool CheckPointer(int id);

		static void NewPointer(int id, int x, int y);

		static void RemovePointer(int id);

		static void NoPointers();

		static void MovePointer(int id, int x, int y);

	private:

		/// Private variables, of multiple input systems if wanted.
		float dragX, dragY;

		/// Static member variables.
		static bool touch, singleTouch, startOfDrag;
		static float startOfDragX, startOfDragY, _x, _y, lx, ly;
		static glm::vec3 accelerometer;
	
		/*Refactoring work*/

		static std::vector<Pointer*> pointers;

	};
}

#endif