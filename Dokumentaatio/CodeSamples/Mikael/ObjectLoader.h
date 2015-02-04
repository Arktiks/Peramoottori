#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#if defined WIN32
#include "GL/glew.h"

#elif defined ANDROID
#include <EGL\egl.h>
#include <GLES2\gl2.h>

#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "NativeSample", __VA_ARGS__)
#endif

#include "glm/glm.hpp"
#include "FileLoader.h"
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>




namespace PORT
{
	class ObjectLoader
	{
	public:

		static ObjectLoader* getInstance();

		void loadObject(std::string filePath, std::vector<GLfloat> &vertices, std::vector<GLushort> &vertexIndices);

	private:
		ObjectLoader(){};
		~ObjectLoader(){};
	
		static ObjectLoader* instance;
	
	};
}

#endif