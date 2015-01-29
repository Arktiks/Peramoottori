#if defined WIN32

#ifndef WINDOWSCONTEXT_H
#define WINDOWSCONTEXT_H

#include <Windows.h>
#include "lodepng.h"

#include "Game.h"

namespace PORT
{
	class Context
	{
	public:

		Context();
		~Context(){ UnregisterClass(L"WindowClass", hInstance); }
		void update();

	private:

		Game* game;

		HWND hWnd;
		HDC hdc;
		HGLRC hglrc;
		HINSTANCE hInstance;
		MSG msg;
	};
}

#endif
#endif