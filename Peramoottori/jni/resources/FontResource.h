#ifndef FONTRESOURCE_H
#define FONTRESOURCE_H

#include <resources\Resource.h>
#include <vector>

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

		/** \brief Return color of font.
		*
		* \return vector<float> that contains colors in RGBA order.
		*/
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
	
		std::vector<FT_Byte> ttfData;
		std::vector<float> color;
		std::vector<Texture*> texture;
		std::string fileName;
		
	};
}

#endif //!FONTRESOURCE_H