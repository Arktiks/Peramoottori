#ifndef TEXTRESOURCE_H
#define TEXTRESOURCE_H

#include <resources\Resource.h>

namespace pm
{

	/** \brief
	*
	* Long description.
	*
	* \ingroup Resources
	*/

	class TextResource : public Resource
	{
		friend class Text;
		friend class Shader;
		friend class ResourceManager;
		friend class TextureFactory;

		TextResource() = delete;

		TextResource(std::string data) : textData(data) {};

		/** \brief Return content of text as string. */
		~TextResource() {};
	private:
		///
		///Constructor
		///		\param data : string of the text data
		///
		


		///
		/// Returns test data as a string
		///		\return text data as string
		///
		std::string GetTextData() { return textData; }

	

		std::string textData;

	};
}

#endif //!TEXTRESOURCE_H