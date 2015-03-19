#include "TextResource.h"

using namespace pm;

TextResource::TextResource()
{
}

TextResource::TextResource(std::string data)
{
	textData = data;
}

std::string TextResource::getTextData()
{
	return textData ;
}

TextResource::~TextResource()
{
}
