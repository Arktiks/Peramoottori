#ifndef ENGINE_H
#define ENGINE_H

#include <android_native_app_glue.h>
#include <EGL/egl.h>

struct Engine
{
public:
	android_app* app;
	AAssetManager* assetManager;

	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;

	float x;
	float y;
	int width;
	int height;

	Engine() : app(nullptr), assetManager(nullptr),
		display(EGL_NO_DISPLAY), surface(EGL_NO_SURFACE), context(EGL_NO_DISPLAY),
		x(0.0f), y(0.0f), width(0), height(0) {};
};

#endif