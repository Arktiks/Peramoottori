#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include <vector>
#include <map>
#include <string>
#include <GLES2\gl2.h>
#include <core\Log.h>
#include <scene\Texture.h>
#include <resources\ResourceManager.h>

#include <glm\common.hpp>

namespace pm
{
	class TextureFactory
	{

	public:

		static pm::Texture* CreateTexture(std::string fileName);


	private:
		~TextureFactory();
		static std::map<std::string, Texture*> generatedTextures;

	};
}
#endif
