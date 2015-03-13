#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H

#include <EGL/egl.h>
#include <android_native_app_glue.h>

class WindowHandler
{
public:
	WindowHandler() : display(EGL_NO_DISPLAY), surface(EGL_NO_SURFACE), context(EGL_NO_CONTEXT), width(0), height(0) {};
	~WindowHandler() {};

	void LoadDisplay(android_app* application);
	void CloseDisplay();

	//void ChangeClearColor();


	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;

	int width;
	int height;

private:

};

#endif