#include "Pointer.h"

using namespace pm;


Pointer::Pointer(int _id, float _x, float _y)
{ 
	int id = _id;
	x = _x; y = _y; 
	sx = _x; sy = _y; 
	lx = _x; ly = _y;
	singleTouch, firstTouch = true;
}
Pointer::Pointer()
{
	int id = 0;
	x = 0; y = 0;
	sx = 0; sy = 0;
	lx = 0; ly = 0;
	singleTouch, firstTouch = true;
	
}
bool Pointer::GetSingleTouch()
{
	if (singleTouch)
	{
		singleTouch = false;
		return true;
	}
	return false;
}