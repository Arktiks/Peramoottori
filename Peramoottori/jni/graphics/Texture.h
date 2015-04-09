#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <vector>
#include <GLES2\gl2.h>
#include <resources\ResourceManager.h>
#include <glm\common.hpp>
#include "lodepng.h"
namespace pm
{
	class Texture
	{
	public:

		Texture();
		void SetId(GLuint ui);
		void SetTextureSize(glm::uvec2 v2);
		GLuint getId();
		glm::uvec2 getTextureSize();
		glm::uvec2 getTexturePosition(){ return glm::vec2(0, 0); }; // atlas position, fix later
		~Texture();

	private:

		GLuint textureIndex;
		glm::uvec2 textureSize;

	};
}

#endif