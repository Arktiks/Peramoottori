#ifndef BUFFER_H
#define BUFFER_H
#if defined WIN32
#include "GL\glew.h"
#elif defined ANDROID
#include <EGL\egl.h>
#include <GLES2\gl2.h>

#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "NativeSample", __VA_ARGS__)
#endif
namespace PORT
{
	enum bufferType
	{
		PORTVERTEX,
		PORTINDEX
	};

	class Buffer
	{		
	public:
		
		~Buffer();

		void createBuffer(bufferType type);
		void pushData(unsigned size, void *data);

		bufferType getType(){ return type; }
		GLuint getIndex(){ return index; }

	protected:

		GLuint index;
		bufferType type;

		static unsigned bSize;

	};
}
#endif