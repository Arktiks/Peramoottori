#ifndef INPUT_H
#define INPUT_H

#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <vector>
#include <android/input.h>

namespace pm
{
	/** \brief %Input is a static class for handling Input received from Android Api.
	* Basic functions work for the primary pointer, if you want to implement multitouch,
	* you will have to use the pointers and handle them separately.
	* \ingroup Core
	*/

	class Input
	{

	private:

		class Pointer
		{
			friend class Input;
		private:
			int index;
			glm::vec2 sPos;
			glm::vec2 pos;
			bool tap;
			bool singleTouch;
			bool touch;

		public:
			int GetID();
			bool GetSingleTouch();
			glm::vec2 GetPos();
			glm::vec2 GetStartPos();
		};
		static const int maxInputs = 8;
		static Pointer pointers[maxInputs];
		static int pointerCount;

		static glm::vec3 accelerometer;

	public:


		const Pointer& operator[](int id) const;

		/** @name Restricted Static Public Member Functions
		* Following static functions have already been implemented in Application class. User is not recommended
		* use of them unless he is 100% confident of their purpose.
		*/
		///@{
		/** \brief Handles the aEvent received from android API
		* \param aEvent the android input event received from android API.
		*/
		static void AndroidEventHandler(AInputEvent* aEvent);

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
	};
}

#endif