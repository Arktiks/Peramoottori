#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include <map>
#include <vector>
#include <string>
#include <scene\Texture.h>

namespace pm
{
	class Text; // Circular dependencies ouch.

	/** \brief Makes all necessary OpenGL calls to create textures.
	*
	* Long description.
	*
	* \ingroup Resources
	*/

	class TextureFactory
	{

		friend class CommandCenter;

	public:

		/** \brief Create texture based on its filename.
		*
		* \param[in] fileName
		*/
		static Texture* CreateTexture(std::string fileName);

		/** \brief
		*
		* \param[in] savedText
		*/
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
		static std::map<std::string, Text*> savedFonts;
	};
}

#endif