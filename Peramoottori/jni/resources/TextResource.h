#ifndef TEXTRESOURCE_H
#define TEXTRESOURCE_H

#include <resources\Resource.h>

namespace pm
{
	class TextResource : public Resource
	{
	public:

		///Constructor
		TextResource(std::string data) :
			textData(data)
		{
			SetName("text");
		};
		/// returns test data as a string
		std::string GetTextData() { return textData; }

		~TextResource() {};

	private:

		std::string textData;

	};
}

#endif //!TEXTRESOURCE_H