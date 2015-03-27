#include "TextResource.h"

pm::TextResource::TextResource()
{
}

pm::TextResource::TextResource(std::string data)
{
	textData = data;
}

std::string pm::TextResource::getTextData()
{
	return textData ;
}

pm::TextResource::~TextResource()
{
}
