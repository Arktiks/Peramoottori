#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include <map>
#include <vector>
#include <string>
#include <scene\Texture.h>


namespace pm
{
	class Text;
	class TextureFactory
	{

		friend class CommandCenter;

	public:

		/// Creates a texture.
		static Texture* CreateTexture(std::string fileName);


		static void SaveText(Text* savedText);

	private:

		///	Function used in creating a texture 
		static void CreateOGLTexture(std::string fileName, Texture* pointer);

		/// recreates OPENGL values after the application get focus again.
		static void RecreateOGLTextures();

		/// Clears OPENGL data on application losing focus
		static void DestroyOGLTextures();

		TextureFactory() {};

		~TextureFactory();

		static std::map<std::string, Texture*> generatedTextures;
		static std::map<std::string, Text*> savedTexts;
	};
}

#endif