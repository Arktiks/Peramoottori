#include "FontResource.h"


pm::FontResource::FontResource()
{
}

pm::FontResource::FontResource(const unsigned char data)
{
	fontData = data;
}

const unsigned char pm::FontResource::getFontData()
{
	return fontData;
}

pm::FontResource::~FontResource()
{
}
