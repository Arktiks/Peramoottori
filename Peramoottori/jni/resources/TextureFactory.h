#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include <map>
#include <string>
#include <scene\Texture.h>

namespace pm
{
	class TextureFactory
	{

		friend class CommandCenter;

	public:

		static Texture* CreateTexture(std::string fileName);

	private:

		static void CreateOGLTexture(std::string fileName, Texture* pointer);
		static void RecreateOGLTextures();
		static void DestroyOGLTextures();

		TextureFactory() {};

		~TextureFactory();

		static std::map<std::string, Texture*> generatedTextures;

	};
}

#endif