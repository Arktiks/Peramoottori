#ifndef INPUT_H
#define INPUT_H

#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <vector>
#include "core\Pointer.h"

namespace pm
{
	/** \brief %Input is a static class for handling Input received from Android Api.
	* Basic functions work for the primary pointer, if you want to implement multitouch,
	* you will have to use the pointers and handle them separately.
	* \ingroup Core
	*/

	class Input
	{
	public:

		Input() {};

		~Input() {};

		/** \brief Returns current touch coordinates of primary pointer.
		* \return Last known touch coordinate of primary pointer as glm::vec2.
		*/
		static glm::vec2 GetTouchCoordinates();

		/** \brief Returns accelerometer data.
		* \return Accelerometer data as glm::vec3.
		*/
		static glm::vec3 GetAccelerometerData();
		
		/** \brief Returns current state of primary pointer's touch.
		* \return true if touching.
		* \return false if not touching. 
		*/
		static bool Touch();

		/** \brief Get the unhandled pointers.
		*
		*/
		static std::vector<Pointer*> GetPointers();

		/** @name Restricted Static Public Member Functions
		* Following static functions have already been implemented in Application class. User is not recommended
		* use of them unless he is 100% confident of their purpose.
		*/
		///@{
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


		/////////////////////////////////////
		///*Everything done for the rework*//
		/////////////////////////////////////

		/** \brief Check if the pointer exists by the ID.
		* \param id Pointer ID from AMotionEvent_getPointerId.
		* \return true if pointer exists.
		* \return false if pointer does not exist. 
		*/
		static bool CheckPointer(int id);

		/** \brief Create a new pointer.
		* \param id Pointer ID from AMotionEvent_getPointerId.
		* \param float x - position on x axis
		* \param float y - position on y axis
		*/
		static void NewPointer(int id, float x, float y);

		/** \brief Check if the pointer exists by the ID.
		* \param id Pointer ID from AMotionEvent_getPointerId.
		*/
		static void RemovePointer(int id);

		/** \brief Check if the pointer exists by the ID.
		* \param id Pointer ID from AMotionEvent_getPointerId.
		*/
		static void NoPointers();

		/** \brief Check if the pointer exists by the ID.
		* \param id Pointer ID from AMotionEvent_getPointerId.
		* \param x
		* \param y
		*/
		static void MovePointer(int id, float x, float y);

	private:

		static glm::vec3 accelerometer;
	
		static std::vector<Pointer*> pointers;

	};
}

#endif