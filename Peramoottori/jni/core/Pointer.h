#pragma once
#include <glm\vec2.hpp>
namespace pm
{
	class Pointer
	{
	public:
		//glm::vec2 form Getters for the pointer.

		Pointer();
		Pointer(int _id, float _x, float _y) { int id = _id; x = _x; y = _y; sx = _x; sy = _y; lx = _x; ly = _y; };
		~Pointer();


		//Getters
		int GetID() { return id; }; //Return the id given to the pointer from Android API AMotionEvent_getPointerId().
		glm::vec2 GetPos() { return glm::vec2(x, y); }; //Return current position of the pointer in glm::vec2 form.
		glm::vec2 GetStartPos() { return glm::vec2(sx, sy); };//Return starting position of the pointer in glm::vec2 form.
		glm::vec2 GetLastPos() { return glm::vec2(lx, ly); };//Return previous position of the pointer in glm::vec2 form.

		//Setters
		void SetPos(float _x, float _y) { x = _x; y = _y; }; //Set current position of the pointer in glm::vec2 form.
		void SetStartPos(float _x, float _y) { sx = _x; sy = _y; };//Set starting position of the pointer in glm::vec2 form.
		void SetLastPos(float _x, float _y) { lx = _x; ly = _y; };//Set previous position of the pointer in glm::vec2 form.

		void SetId(int _id){ id = _id; }; //Set the ID of the pointer, use only when creating a pointer with default constructor. The value should come from Android API AMotionEvent_getPointerId().

	private:
		int id; //Android API id from AMotionEvent_getPointerId();
		float x, y; //Most recent touch cordinates,
		float sx, sy; //Starting position of the pointer.
		float lx, ly; // Previous position of the pointer
	};
}