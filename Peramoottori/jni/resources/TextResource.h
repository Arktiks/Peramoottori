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
	public:

		TextResource() = delete;

		TextResource(std::string data) : textData(data) {};

		/** \brief Return content of text as string. */
		std::string GetTextData() { return textData; }

		~TextResource() {};

	private:

		std::string textData;

	};
}

#endif //!TEXTRESOURCE_H