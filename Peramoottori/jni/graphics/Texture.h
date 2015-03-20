#ifndef TEXTURE_H
#define TEXTURE_H
#include "resources\Image.h"
#include <glm\common.hpp>
#include <string>
#include <vector>
#include <GLES2\gl2.h>
#include "lodepng.h"
#include "resources\ResourceManager.h"
namespace pm
{
	class Texture
	{
	public:
		Texture(std::string fileName);
		Texture();
		GLuint getId();
		glm::vec2 getTextureSize();
		glm::vec2 getTexturePosition(){ return glm::vec2(0, 0); }; // atlas position, fix later
		void createTexture(std::string filename);
		~Texture();

	private:
		GLuint textureIndex;

		pm::Image LoadImage(std::string fileName);
		std::vector<unsigned char> DecodePNG(pm::Image image);
		void GenerateTexture(std::vector<unsigned char> decodedImage);
		glm::uvec2 textureSize;
	};
}

#endif