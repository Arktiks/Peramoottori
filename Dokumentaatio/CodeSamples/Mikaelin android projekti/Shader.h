#ifndef SHADER_H
#define SHADER_H
#define GLM_FORCE_RADIANS

#if defined WIN32
#include "GL\glew.h"


#elif defined ANDROID
#include <EGL\egl.h>
#include <GLES2\gl2.h>
#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "NativeSample", __VA_ARGS__)
#endif

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

namespace PORT
{
	class Shader
	{
	public:

		static Shader* getInstance();

		int newShader();


		GLuint* getProgram();
		void useShader();

	private:

		Shader(){};
		~Shader(){};

		static Shader* instance;

		GLuint program;
		GLint positionIndex;
		GLint colorIndex;
		GLint texIndex;
		GLint projectionLocation;

		GLint viewIndex;
		GLint worldIndex;

		glm::mat4 projection;
	};
}

#endif