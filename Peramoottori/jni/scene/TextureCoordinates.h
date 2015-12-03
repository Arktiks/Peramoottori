#ifndef TEXTURECOORDINATES_H
#define TEXTURECOORDINATES_H

#include <GLES2\gl2.h>
#include <glm\vec4.hpp>
#include <glm\vec2.hpp>
#include <scene\Component.h>
#include <vector>

namespace pm
{

	/** \brief Used to define what part of a texture is rendered.
	*
	* TextureCoordinates is used to define what part of texture is rendered.
	* Useful for texture atlas, and for animating from sprite sheets.
	*/

	class TextureCoordinates : public Component
	{
	public:

		/** \brief Constructor for TextureCoordinates
		* Sets each coordinate as 0
		*/
		TextureCoordinates();
		
		/** \brief Constructor for TextureCoordinates with coordinates as parameters
		*
		* Creates TextureCoordinates with given parameters
		* \param[in] left first x-coordinate
		* \param[in] top first y-coordinate
		* \param[in] right second x-coordinate
		* \param[in] bottom second y-coordinate
		*/
		TextureCoordinates(float left, float top, float right, float bottom);
		
		
		/** \brief Constructor for TextureCoordinates with vec2 as parameters.
		*
		* Creates TextureCoordinates with given parameters
		* \param[in] leftTop first x and y coordinates
		* \param[in] rightBottom second x and y coordinates
		*/
		TextureCoordinates(glm::vec2 leftTop, glm::vec2 rightBottom);
		
		/** \brief Constructor for TextureCoordinates with vec4 as parameter.
		*
		* Creates TextureCoordinates with given parameters
		* \param[in] TextureCoordinates All TextureCoordinates needed in order: left(x), top(y), right(x), bottom(y)
		*/
		TextureCoordinates(glm::vec4 textureCoordinates);
		
		/* \brief
		*
		* Overloaded Component class function. Sets a parent GameEntity for the TextureCoordinates 
		* Component and has other functionality compared to default.
		*/
		void SetParent(GameEntity* entity);
		
		/** \brief Sets TextureCoordinates with coordinates as parameters
		* 
		* Sets TextureCoordinates with given parameters
		* \param[in] left first x-coordinate
		* \param[in] top first y-coordinate
		* \param[in] right second x-coordinate
		* \param[in] bottom second y-coordinate
		*/
		void SetTextureCoordinates(float left, float top, float right, float bottom);
		
		/** \brief Sets TextureCoordinates with vec2 as parameters.
		*
		* Sets TextureCoordinates with given parameters
		* \param[in] leftTop first x and y coordinates
		* \param[in] rightBottom second x and y coordinates
		*/
		void SetTextureCoordinates(glm::vec2 leftTop, glm::vec2 rightBottom);
		
		/** \brief Sets TextureCoordinates with with vec4 as parameter.
		*
		* \param[in] leftTopRightBottom All TextureCoordinates needed in order: left(x), top(y), right(x), bottom(y)
		*
		*/
		void SetTextureCoordinates(glm::vec4 leftTopRightBottom);
		
		/** \brief Sets TextureCoordinates with leftTop coordinate and texture width and height
		*
		* Sets TextureCoordinates with given parameters
		* \param[in] left x-coordinate
		* \param[in] top y-coordinate
		* \param[in] width of the texture area
		* \param[in] height of the texture area
		*/
		void SetTextureDimensions(float left, float top, float width, float height);
		
		/** \brief Sets TextureCoordinates with leftTop coordinate and texture width and height
		*
		* Sets TextureCoordinates with given parameters
		* \param[in] leftTop first x and y coordinates
		* \param[in] widthHeight width and height of the texture area
		*/
		void SetTextureDimensions(glm::vec2 leftTop, glm::vec2 widthHeight);
		
		/** \brief Sets TextureCoordinates with leftTop coordinate and texture width and height
		*
		* Sets TextureCoordinates with given parameters
		* \param[in] leftTopWidthHeight All TextureDimensions in order: left(x), top(y), width(x), height(y)
		*/
		void SetTextureDimensions(glm::vec4 leftTopWidthHeight);
		
		/** \brief returns textureCoordinates as vector<GLfloat>
		*
		* Return textureCoordinates in order left(x), top(y), right(x), bottom(y)
		* \return All textureCoordinates as std::vector<GLfloat>
		*/
		std::vector<GLfloat> GetTextureCoordinates() { return textureCoordinates; };
		
		/** \brief returns textureCoordinates glm::vec4
		*
		* Return textureCoordinates in order left(x), top(y), right(x), bottom(y)
		* \return All textureCoordinates as glm::vec4
		*/
		glm::vec4 GetTextureCoordinatesVec4()
		{
			glm::vec4 coordinates = glm::vec4(textureCoordinates[0], textureCoordinates[1], textureCoordinates[2], textureCoordinates[3]);
			return coordinates;
		}
		
	private:
		/** \brief
		*
		*  Container for textureCoordinates
		*/
		std::vector<GLfloat> textureCoordinates;
		
	};
}

#endif //TEXTURECOORDINATES_H
