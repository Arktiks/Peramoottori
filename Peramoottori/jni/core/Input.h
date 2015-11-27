#ifndef INPUT_H
#define INPUT_H

#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <vector>
#include <android/input.h>

namespace pm
{
	//Backbutton override function
	typedef void(*BackFunction)();

	/** \brief %Input is static class for handling input received from Android API.
	*
	* Basic functions work for the primary pointer. If you want to implement multitouch
	* you will have to use the pointers and handle them separately.
	*
	* \ingroup Core
	*/

	class Input
	{
	public:
		/** \internal Nolla comments nolla nothing.
		*/
		class Pointer
		{
			friend class Input;
		private:
			int index; //Current index of pointer.
			int id; //Unique ID of pointer
			glm::vec2 sPos; // Start position
			glm::vec2 pos; 
			bool singleTouch;
			bool touching;

		public:
			int GetID();
			bool GetSingleTouch();
			bool IsTouching();
			glm::vec2 GetPos();
			glm::vec2 GetStartPos();
			
			Pointer() : index(0), id(0), sPos(0, 0), pos(0, 0), singleTouch(false), touching(false) {};
		};

	private:
		static const int maxInputs = 8;
		static Pointer pointers[maxInputs];
		static int pointerCount;
		static int incrPointerID;
		static glm::vec3 accelerometer;

		static BackFunction backFunction;

	public:

		static bool UpdatePointer(int uniqueID, Input::Pointer& touch);
		/** \brief Returns the amount of currently active pointers.
		*
		* \return Number of active pointers.
		*/
		static int GetPointerCount();

		/** \brief Operator[] overload for accessing pointers.
		*
		* \param index Index of the pointer you want to access.
		* \return Returns the pointer in the param index.
		*/
		Pointer& operator[](int index);

		/** @name Restricted Static Public Member Functions
		* Following static functions have already been implemented in Application class. User is not recommended
		* use of them unless he is 100% confident of their purpose.
		*/
		///@{
		/** \brief Handles the aEvent received from android API
		*
		* \param aEvent the android input event received from android API.
		*/
		static int32_t AndroidEventHandler(AInputEvent* aEvent);

		/** \brief Updates touchState conditions at start of each engine main loop.
		* 
		* Used in Application class at start of each main loop.
		*/
		static void Update();

		/** \brief Called in Application::Update() to receive accelerometer data. 
		*
		* \param accelerometer Accelerometer data to be given to Input.
		*/
		static void InputEventAccelerometer(float x, float y, float z);
		///@}

		/** \brief Set function pointer to override Back Button functionality. 
		* \param BackFunction pointer to the override function.
		*/
		static void setBackFunction(void(*BackFunction)()) { backFunction = BackFunction; };
	};
}

#endif