#ifndef ATLASTEXTURE_H

#define ATLASTEXTURE_H
#include "glm\common.hpp"
#include <GLES2\gl2.h>
namespace pm
{
	class AtlasTexture
	{
	public:
		AtlasTexture(GLuint atlasIndex, glm::vec2 texturePosition, glm::vec2 textureSize);
		~AtlasTexture();

		glm::vec2 getTexturePosition();
		glm::vec2 getTextureSize();
		GLuint getAtlasIndex();
	private:

		GLuint atlasIndex;
		glm::vec2 texturePosition;
		glm::vec2 textureSize;
	};
}
#endif