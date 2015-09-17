#ifndef TEXTRESOURCE_H
#define TEXTRESOURCE_H

#include <resources\Resource.h>

namespace pm
{
	class TextResource : public Resource
	{
		friend class Text;
		friend class Shader;
		friend class ResourceManager;
		friend class TextureFactory;

	private:
		///
		///Constructor
		///		\param data : string of the text data
		///
		TextResource(std::string data) :
			textData(data)
		{
			SetName("text");
		};


		///
		/// Returns test data as a string
		///		\return text data as string
		///
		std::string GetTextData() { return textData; }

		~TextResource() {};

		std::string textData;

	};
}

#endif //!TEXTRESOURCE_H