#ifndef ATLAS_H

#define ATLAS_H
#include <GLES2\gl2.h>
#include "Texture.h"
#include "glm\common.hpp"
#include "resources\ResourceReader.h"
#include <string>
class Atlas : public Texture
{
public:
	Atlas(std::string fileName);
	~Atlas();
	GLuint atlasIndex;
	glm::vec2 atlasSize;
};

#endif