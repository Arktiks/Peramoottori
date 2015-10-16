#pragma once
#include <glm\vec2.hpp>
namespace pm
{
	class Pointer
	{
	public:

		/***********************************************************************************************/
		///Tors
		/***********************************************************************************************/
		//Default constructor
		Pointer();
		//Setter constructor, you should use this in most cases.
		Pointer(int _id, float _x, float _y);
		//Default destructor
		~Pointer();


		/***********************************************************************************************/
		//Getters
		/***********************************************************************************************/
		//Return the id given to the pointer from Android API AMotionEvent_getPointerId().
		int GetID() { return id; }; 
		//Return current position of the pointer in glm::vec2 form.
		glm::vec2 GetPos() { return glm::vec2(x, y); }; 
		//Return starting position of the pointer in glm::vec2 form.
		glm::vec2 GetStartPos() { return glm::vec2(sx, sy); };
		//Return previous position of the pointer in glm::vec2 form.
		glm::vec2 GetLastPos() { return glm::vec2(lx, ly); };

		//Returns true if this has not been called before for the pointer.
		bool GetSingleTouch(); 
		//Returns true if the pointer was put down in last frame.
		bool GetFirstTouch() { return firstTouch; }; 

		/***********************************************************************************************/
		///Setters, dont use these unless you are certain you want to override the Android set positions.
		/***********************************************************************************************/
		//Set current position of the pointer in glm::vec2 form.
		void SetPos(float _x, float _y) { x = _x; y = _y; }; 
		void SetPos(glm::vec2 pos){ x = pos.x; y = pos.y; };
		//Set starting position of the pointer in glm::vec2 form.
		void SetStartPos(float _x, float _y) { sx = _x; sy = _y; };
		void SetStartPos(glm::vec2 pos){ sx = pos.x; sy = pos.y; };
		//Set previous position of the pointer in glm::vec2 form.
		void SetLastPos(float _x, float _y)  { lx = _x; ly = _y; };
		void SetLastPos(glm::vec2 pos){ lx = pos.x; ly = pos.y; };

		/***********************************************************************************************/
		//System Setters, should not be used outside of the engine.
		/***********************************************************************************************/
		//Set the ID of the pointer, use only when creating a pointer with default constructor. The value should come from Android API AMotionEvent_getPointerId().
		void SetId(int _id){ id = _id; }; 
		//Setter used in Input::Update, updates firstTouch condition.
		void SetFirstTouch(){ firstTouch = false; };
		
	private:

		/***********************************************************************************************/
		///Private variables
		/***********************************************************************************************/
		//Android API id from AMotionEvent_getPointerId();
		int id; 
		//Most recent touch cordinates,
		float x, y; 
		//Starting position of the pointer.
		float sx, sy; 
		//Previous position of the pointer
		float lx, ly; 
		//Variables to check different touch conditions for the pointers.
		bool singleTouch, firstTouch;
	};
}