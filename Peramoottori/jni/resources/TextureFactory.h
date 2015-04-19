#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include <map>
#include <string>
#include <scene\Texture.h>

namespace pm
{
	class TextureFactory
	{

	public:

		static Texture* CreateTexture(std::string fileName);

	private:

		TextureFactory() {};

		~TextureFactory();

		static std::map<std::string, Texture*> generatedTextures;

	};
}

#endif