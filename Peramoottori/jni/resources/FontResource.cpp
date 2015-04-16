#include "FontResource.h"


pm::FontResource::FontResource()
{
}

pm::FontResource::FontResource(FT_Library lib, FT_Face fa)
{
	library = lib;
	face = fa;
}

pm::FontResource::~FontResource()
{
}
