#ifndef TEXTURECOORDINATES_H
#define TEXTURECOORDINATES_H

#include <GLES2\gl2.h>
#include <glm\vec4.hpp>
#include <glm\vec2.hpp>
#include <scene\Component.h>
#include <vector>

namespace pm
{

	/** \brief Used to define what part of Texture component is rendered.
	*
	* Useful for texture atlas and for animating from spritesheets.
	*/

	class TextureCoordinates : public Component
	{
	public:

		/** \brief Constructor for TextureCoordinates.
		*
		* By default sets each coordinate to 0.
		*/
		TextureCoordinates();
		
		/** \brief Constructor for TextureCoordinates with coordinates as parameters.
		*
		* \param[in] left start x-coordinate.
		* \param[in] top start y-coordinate.
		* \param[in] right end x-coordinate.
		* \param[in] bottom end y-coordinate.
		*/
		TextureCoordinates(float left, float top, float right, float bottom);
		
		/** \brief Constructor for TextureCoordinates with glm::vec2 as parameters.
		*
		* \param[in] leftTop start x and y coordinates.
		* \param[in] rightBottom start x and y coordinates.
		*/
		TextureCoordinates(glm::vec2 leftTop, glm::vec2 rightBottom);
		
		/** \brief Constructor for TextureCoordinates with glm::vec4 as parameter.
		*
		* \param[in] textureCoordinates All texture coordinates needed in order: left(x), top(y), right(x), bottom(y).
		*/
		TextureCoordinates(glm::vec4 textureCoordinates);
		
		/* \brief Sets parent GameEntity for TextureCoordinates component. */
		void SetParent(GameEntity* entity);
		
		/** \brief Sets texture coordinates with coordinates as parameters.
		* 
		* \param[in] left start x-coordinate.
		* \param[in] top start y-coordinate.
		* \param[in] right end x-coordinate.
		* \param[in] bottom end y-coordinate.
		*/
		void SetTextureCoordinates(float left, float top, float right, float bottom);
		
		/** \brief Sets texture coordinates with glm::vec2 as parameters.
		*
		* \param[in] leftTop start x and y coordinates.
		* \param[in] rightBottom end x and y coordinates.
		*/
		void SetTextureCoordinates(glm::vec2 leftTop, glm::vec2 rightBottom);
		
		/** \brief Sets texture coordinates with with glm::vec4 as parameter.
		*
		* \param[in] leftTopRightBottom All texture coordinates needed in order: left(x), top(y), right(x), bottom(y).
		*/
		void SetTextureCoordinates(glm::vec4 leftTopRightBottom);
		
		/** \brief Sets texture coordinates with leftTop coordinate and texture width and height.
		*
		* \param[in] left start x-coordinate.
		* \param[in] top start y-coordinate.
		* \param[in] width of the texture area.
		* \param[in] height of the texture area.
		*/
		void SetTextureDimensions(float left, float top, float width, float height);
		
		/** \brief Sets texture coordinates with leftTop coordinate and texture width and height.
		*
		* \param[in] leftTop start x and y coordinates.
		* \param[in] widthHeight width and height of the texture area.
		*/
		void SetTextureDimensions(glm::vec2 leftTop, glm::vec2 widthHeight);
		
		/** \brief Sets texture dimensions with leftTop coordinate and texture width and height.
		*
		* \param[in] leftTopWidthHeight All texture coordinates in order: left(x), top(y), width(x), height(y).
		*/
		void SetTextureDimensions(glm::vec4 leftTopWidthHeight);
		
		/** \brief Returns texture coordinates as std::vector<GLfloat>.
		*
		* \return std::vector<GLfloat> All texture coordinates in order left(x), top(y), right(x), bottom(y).
		*/
		std::vector<GLfloat> GetTextureCoordinates() { return textureCoordinates; };
		
		/** \brief Returns texture coordinates as glm::vec4.
		*
		* \return glm::vec4 All texture coordinates in order left(x), top(y), right(x), bottom(y).
		*/
		glm::vec4 GetTextureCoordinatesVec4();
		
	private:

		std::vector<GLfloat> textureCoordinates; // Container for texture coordinates.
		
	};
}

#endif //TEXTURECOORDINATES_H