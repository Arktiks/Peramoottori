#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include <map>
#include <vector>
#include <string>
#include <scene\Texture.h>

namespace pm
{
	/** \brief Makes all necessary OpenGL calls to create textures.
	*
	* Long description.
	*
	* \ingroup Resources
	*/

	struct TextureStruct
	{
		GLuint ti; // GL textureIndex
		uint sx; // texture size x
		uint sy; // texture size y
		uint tg; // texture group 
	};
	class TextureFactory
	{

		friend class CommandCenter;

	public:

		/** \brief Create texture based on its filename.
		*
		* \param[in] fileName
		*/
		static Texture* CreateTexture(std::string fileName);

		static void RemoveTextureGroup(uint textureGroupToRemove);

		static void RemoveTexture(std::string);

	private:

		///	Function used in creating a texture 
		static void CreateOGLTexture(std::string fileName, Texture* pointer);

		static void CreateOGLTexture(std::string fileName, pm::TextureStruct* tempTS);

		/// recreates OPENGL values after the application get focus again.
		static void RecreateOGLTextures();

		/// Clears OPENGL data on application losing focus
		static void DestroyOGLTextures();

		TextureFactory() {};

		~TextureFactory();

		static std::map<std::string, pm::TextureStruct*> generatedTextures;
	};
}
#endif