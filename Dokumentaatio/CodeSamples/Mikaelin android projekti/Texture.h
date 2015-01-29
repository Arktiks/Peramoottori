#ifndef TEXTURE_H
#define TEXTURE_H

#if defined WIN32
#include "GL/glew.h"

#elif defined ANDROID
#include <EGL\egl.h>
#include <GLES2\gl2.h>

#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "NativeSample", __VA_ARGS__)
#endif

#include "FileLoader.h"
#include "lodepng.h"
#include <string>

namespace PORT
{
	class Texture
	{
	public:
		Texture(std::string filePath);
		GLuint getIndex(){ return index; };
	private:
		GLuint index;
		unsigned width, height;

	};
}

#endif