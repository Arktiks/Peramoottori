#ifndef TEXTRESOURCE_H
#define TEXTRESOURCE_H

#include <resources\Resource.h>

namespace pm
{
	/** \internal Class description should be written with more detail. */
	/** \brief Text resource containing text data.
	*
	* Inengine use only.
	*
	* \ingroup Resources
	*/

	class TextResource : public Resource
	{
		friend class Text;
		friend class Shader;
		friend class ResourceManager;
		friend class TextureFactory;

	protected:

		TextResource() = delete;

		TextResource(std::string data) : textData(data) {};

		~TextResource() {};


		std::string GetTextData() { return textData; }
		void SetTextData(std::string data) { textData = data; }
		std::string textData;

	};
}

#endif //!TEXTRESOURCE_H