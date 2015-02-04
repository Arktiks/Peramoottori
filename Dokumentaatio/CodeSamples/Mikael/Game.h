#ifndef GAME_H
#define GAME_H

#if defined WIN32
#include "GL/glew.h"

#elif defined ANDROID
#include <EGL\egl.h>
#include <GLES2\gl2.h>

#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "NativeSample", __VA_ARGS__)
#endif

#include "Shader.h"
#include "Buffer.h"
#include "ObjectLoader.h"
#include "Texture.h"
#include <vector>

namespace PORT
{
	class Game
	{
	public:

		void update();

		static Game* instance();

	private:
		Game();
		~Game();
		
		Buffer vbufferi;
		Buffer ibufferi;

		Shader* shader;
		static Game* gameInstance;

		std::string filePath;
		std::vector<GLfloat> vertices;
		std::vector<GLushort> indices;
		Texture* testi;
	};

}

#endif