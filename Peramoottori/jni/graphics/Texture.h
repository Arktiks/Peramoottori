#ifndef TEXTURE_H

#define TEXTURE_H
#include "glm\common.hpp"
#include <GLES2\gl2.h> // Need GLuint, better include?
class Texture
{
public:
	Texture(int atlas, glm::vec2 texturePosition, glm::vec2 textureSize);
	Texture();
	~Texture();

	void setSourceRectSize(glm::vec2);
	void setSourceRectPosition(glm::vec2);

	glm::vec2 getTexturePosition(); // Tarvitaanko tätä?
	glm::vec2 getTextureSize();
	GLuint getAtlasID();
private:

	GLuint atlasIndex; // index tekstuuriatlaksen sijainnille.
	glm::vec2 texturePosition; // Texture position on atlas.
	glm::vec2 textureSize;

};

#endif