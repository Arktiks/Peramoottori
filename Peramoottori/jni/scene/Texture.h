#ifndef TEXTURE_H
#define TEXTURE_H

#include <GLES2\gl2.h>
#include <scene\Component.h>
#include <glm\common.hpp>


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


	private:

		GLuint textureIndex;
		glm::uvec2 textureSize;

	};
}

#endif