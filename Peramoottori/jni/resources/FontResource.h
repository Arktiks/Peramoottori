#ifndef FONTRESOURCE_H
#define FONTRESOURCE_H

#include <resources\Resource.h>
//#include <GLES2\gl2.h>

#include <include\ft2build.h>
#include FT_FREETYPE_H

namespace pm
{
	class FontResource : public Resource
	{
	public:

		//FontResource();

		FontResource(FT_Library lib, FT_Face face) :
			library(lib), face(face) {};

		FT_Library GetLibrary() { return library; }

		FT_Face GetFace() { return face; }

		~FontResource() {};
		
	private:
	
		FT_Library library;

		FT_Face face;

	};
}

#endif //!FONTRESOURCE_H