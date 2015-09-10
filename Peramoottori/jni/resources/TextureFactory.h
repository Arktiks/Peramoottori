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

		/// Creates a texture.
		static Texture* CreateTexture(std::string fileName);

		/// Creates a texture.
		/// @param unsigned char* buffer
		/// used for text
		//static Texture* CreateTexture(unsigned char* buffer, char character, int x, int y);

	private:

		///	Function used in creating a texture 
		static void CreateOGLTexture(std::string fileName, Texture* pointer);

		///	Function used in creating a texture 
		static void CreateOGLTexture(std::string fileName, Texture* pointer, unsigned char* buffer, int x,int y);

		/// recreates OPENGL values after the application get focus again.
		static void RecreateOGLTextures();

		/// Clears OPENGL data on application losing focus
		static void DestroyOGLTextures();

		TextureFactory() {};

		~TextureFactory();

		static std::map<std::string, Texture*> generatedTextures;

	};
}

#endif