#ifndef ENGINE_H
#define ENGINE_H

#include <android_native_app_glue.h>
#include <EGL/egl.h>

struct Engine
{
	android_app* app;
	AAssetManager* assetManager;

	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;

	float x;
	float y;
	int width;
	int height;
};

#endif