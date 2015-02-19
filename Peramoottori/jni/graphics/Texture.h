#ifndef TEXTURE_H

#define TEXTURE_H
#include "glm\common.hpp"
class Texture
{
public:
	Texture(int atlas, glm::vec2 texturePosition, glm::vec2 textureSize);
	Texture();
	~Texture();

	void setSourceRectSize(glm::vec2);
	void setSourceRectPosition(glm::vec2);

	glm::vec2 getSourceRectSize();
	glm::vec2 getSourceRectPosition();

	glm::vec2 getTexturePosition();
	glm::vec2 getTextureSize();
	int getAtlasID();
private:

	int atlasIndex; // index tekstuuriatlaksen sijainnille.
	glm::vec2 texturePosition; // Texture position on atlas.
	glm::vec2 textureSize;

};

#endif