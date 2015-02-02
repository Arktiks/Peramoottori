#include "WindowsContext.h"


using namespace PORT;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

Context::Context()
{
	WNDCLASSEX window;

	window.cbSize = sizeof(window);
	window.style = CS_OWNDC;
	window.lpfnWndProc = WindowProc;
	window.cbClsExtra = 0;
	window.cbWndExtra = 0;
	window.hInstance = GetModuleHandle(nullptr);
	window.hIcon = NULL;
	window.hCursor = NULL;
	window.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);
	window.lpszMenuName = NULL;
	window.lpszClassName = L"WindowClass";
	window.hIconSm = NULL;

	if (!RegisterClassEx(&window))
	{
		MessageBox(NULL, L"FAIL rekisteri", L"rekisteriFAIL", NULL);
	}

	RECT gameWindow;

	gameWindow.top = 40;
	gameWindow.left = 60;
	gameWindow.right = 480;
	gameWindow.bottom = 720;

	AdjustWindowRectEx(&gameWindow, WS_CAPTION, false, WS_EX_LEFT);

	hWnd = CreateWindowEx(WS_EX_LEFT, L"WindowClass", L"akkuna", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, gameWindow.left, gameWindow.top, gameWindow.right, gameWindow.bottom, NULL, NULL, window.hInstance, NULL);

	ShowWindow(hWnd, SW_SHOWNORMAL);


	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
		24,                       //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                       //Number of bits for the depthbuffer
		8,                        //Number of bits for the stencilbuffer
		0,                        //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};


	hdc = GetDC(hWnd);

	int iPixelCode = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, iPixelCode, &pfd);

	hglrc = wglCreateContext(hdc);

	wglMakeCurrent(hdc, hglrc);


	glewInit();

	Shader* shader = Shader::getInstance();
	shader->newShader();

	game = Game::instance();
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

void Context::update()
{

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
	{
		if (msg.message == WM_QUIT)
		{
			break;
		}
		DispatchMessage(&msg);
	}

	game->update();

	SwapBuffers(hdc);
}