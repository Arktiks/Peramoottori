#ifndef FONTRESOURCE_H
#define FONTRESOURCE_H

#include <resources\Resource.h>
#include <vector>
#include <map>

#include <core\Log.h>
#include <core\Memory.h>
#include <GLES2\gl2.h>
#include <include\ft2build.h>
#include <scene\Texture.h>
#include FT_FREETYPE_H

namespace pm
{

	/** \internal Functions should be described with more detail. */

	/** \brief
	*
	* Long description.
	*
	* \ingroup Resources
	*/

	class FontResource : public Resource
	{
		struct fontData
		{
			Texture* tex;
			float cw, ch;
		};

	public:

		FontResource() = delete;

		/** \brief
		*
		* \param[in] ttfData 
		*/
		FontResource(std::vector<FT_Byte> ttfData) :
			ttfData(ttfData)
		{
			SetColor(1, 0, 1, 0);
			CharTexture(ttfData);
		};

		/** \brief
		*
		* \return Vector<FT_Byte> data of the font.
		*/
		std::vector<FT_Byte> GetTTFData() { return ttfData; }

		/** \brief Change color of the font. */
		void ChangeColor(float red, float green, float blue, float alpha)
		{
			color.at(0) = red;
			color.at(1) = green;
			color.at(2) = blue;
			color.at(3) = alpha;
		};

		Texture* GetTexture(char c)
		{
			if (dataMap.find(c) != dataMap.end())
				return dataMap[c].tex;
			else
				return NEW Texture;
		}
		float Getasd(char c)
		{
			if (dataMap.find(c) != dataMap.end())
				return dataMap[c].cw;
			else
				return 1;
		}

		float Getasda(char c)
		{
			if (dataMap.find(c) != dataMap.end())
				return dataMap[c].ch;
			else
				return 1;
		}

		std::vector<float> GetColor() { return color; };

		/** \brief Set name of file that contains TTF data.
		*
		* \param[in] newName
		*/
		void SetFileName(std::string newName) { fileName = newName; };

		/** \brief Return name of file.
		*
		* \return string Name of file.
		*
		*/
		std::string GetFileName() { return fileName; };
		
		~FontResource() {};
		
	private:

		/// Sets color of the font.
		void SetColor(float red, float green, float blue, float alpha)
		{
			color.push_back(red);
			color.push_back(green);
			color.push_back(blue);
			color.push_back(alpha);
		};
		void CharTexture(std::vector<FT_Byte> ttfData)
		{
			FT_Library  library;
		
			FT_Error error = FT_Init_FreeType(&library);
			if (error)
				DEBUG_INFO(("Failed to initialize freetype library!"));
		
			std::vector<FT_Byte> ttf = ttfData;
		
			

			FT_UInt glyph_index;
	
			std::string str("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUWXYZ1234567890!'#¤%&/()=?,.;:-^_{}|[]~@£$");

			for (int i = 0; i < str.size(); i++)
			{                                                      
				error = FT_New_Memory_Face(library,
					&ttf[0],
					ttf.size(),
					0,
					&face);
				if (error == FT_Err_Unknown_File_Format)
				{
					DEBUG_INFO(("The font file could be opened and read, but it appears that its font format is unsupported"));
				}
				else if (error)
				{
					DEBUG_INFO(("Font file could not be opened or read, or it is broken"));
				}
		
				FT_GlyphSlot  slot = face->glyph;
				
				error = FT_Set_Char_Size(
					face,						/* handle to face object           */
					0,							/* char_width in 1/64th of points  */
					32 * 64,					/* char_height in 1/64th of points */
					1280,						/* horizontal device resolution    */
					720);						/* vertical device resolution      */
		
		
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

				glyph_index = FT_Get_Char_Index(face, str.at(i));

				glGenTextures(1, &textId);
				glActiveTexture(textId);
				glBindTexture(GL_TEXTURE_2D, textId);
		
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
				float ux = slot->bitmap_left;
				float uy = slot->bitmap_top;
		

				

				FT_Load_Glyph(face, glyph_index, FT_LOAD_RENDER);
				
				FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);
		
				glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, slot->bitmap.width, slot->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, slot->bitmap.buffer);

				float uw = slot->bitmap.width;
				float uh = slot->bitmap.rows;


		
				Texture *textTexture = NEW Texture();
				textTexture->SetId(textId);
				textTexture->SetTextureSize(glm::vec2(slot->bitmap.width, slot->bitmap.rows));
				fontData fd;
				fd.tex = textTexture;
				fd.cw = uw;
				fd.ch = uh;
				dataMap[str.at(i)] = fd;
			}
		};


	
		std::vector<FT_Byte> ttfData;
		std::vector<float> color;
		std::map<char, fontData> dataMap;
		std::string fileName;
		FT_Face face;
		GLuint textId;
		
	};
}

#endif //!FONTRESOURCE_H