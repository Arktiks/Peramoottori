#ifndef SPRITEOBJECT_H
#define SPRITEOBJECT_H

#include <scene\GameEntity.h>
#include <scene\Texture.h>
#include <glm\common.hpp>
#include <string>

namespace pm
{ 
	/** \brief GameEntity that has wrapped graphical drawing components.
	*
	* SpriteObject is a GameEntity that holds components and has wrapped drawing functions for easy use. 
	*
	* \ingroup Scene
	*/
	class SpriteObject:public GameEntity
	{

	public:

		/** \brief Default constructor that adds drawing components.
		*
		* Adds these components: Transformable, TextureCoordinates, Rectangle, Drawable, Color.
		*
		*/
		SpriteObject();
		
		/** \brief Constructor that uses texture as source for draw-components
		*
		* Adds these components: Texture, Transformable, TextureCoordinates, Rectangle, Drawable, Color.
		* \param[in] texture pm::Texture*.
		* Default TextureCoordinates size is Texture's size.
		*/
		SpriteObject(pm::Texture* texture);

		/** \brief Constructor that loads texture using filename for draw-components.
		*
		* Adds these components: Texture, Transformable, TextureCoordinates, Rectangle, Drawable, Color.
		* \param[in] filename Loads Texture using filename.
		* Default TextureCoordinates size is Texture's size.
		*/
		SpriteObject(std::string filename);

		/** \brief Destructor for SpriteObject. Destroys all components added.
		*
		* if components are used multiple times, this will cause crashes upon object deletion
		*
		*/
		~SpriteObject();

		/** \brief Update function for updating different components
		*
		* Has to be created to define updates for components.
		* \param[in] deltaTime Time that can be used for component updates. 
		*
		*/
		virtual void Update(float deltaTime); 

		/** \brief Function for setting position of SpriteObject (x, y).
		*
		* \param[in] position glm::vec2 Used to set SpriteObject's position (x, y).
		*
		*/
		void SetPosition(glm::vec2 position);

		/** \brief Function for setting position of SpriteObject (x, y)
		*
		* \param[in] positionX Used to set SpriteObject's x position.
		* \param[in] positionY Used to set SpriteObject's y position.
		*
		*/
		void SetPosition(float positionX, float positionY);

		/** \brief Function for setting size of SpriteObject.
		*
		* \param[in] size Used to set size (width, height).
		*
		*/
		void SetSize(glm::vec2 size);

		/** \brief Function for setting size of SpriteObject.
		*
		* \param[in] width Used to set width.
		* \param[in] height Used to set height.
		*
		*/
		void SetSize(float width, float height);

		/** \brief Function for setting scale of SpriteObject.
		*
		* Scale multiplies widht and/or height.
		* \param[in] scale Sets scale multiplier (width, height).
		*
		*/
		void SetScale(glm::vec2 scale);

		/** \brief Function for setting scale of SpriteObject.
		*
		* Scale multiplies widht and/or height.
		* \param[in] scaleX Sets scale multiplier for width.
		* \param[in] scaleY Sets scale multiplier for height.
		*
		*/
		void SetScale(float scaleWidth, float scaleHeight);

		/** \brief Sets origin of SpriteObject
		*
		* \param[in] origin x- and y-coordinate for drawing.
		* Can be used for example to rotate from certain point.
		*
		*/
		void SetOrigin(glm::vec2 origin);

		/** \brief Sets origin of SpriteObject
		*
		* \param[in] originX x-coordinate for origin
		* \param[in] float originY y-coordinate for origin
		*
		*/
		void SetOrigin(float originX, float originY);

		/** \brief Set rotation for SpriteObject
		*
		* \param[in] rotation Set rotation for object.
		* Rotation is in degrees.
		*
		*/
		void SetRotation(float rotation);

		/** \brief Set draw depth of SpriteObject
		*
		* \param[in] depth larger numbers are drawn in front
		*  This is used to draw objects on different layers
		*
		*/
		void SetDepth(float depth);

		/** \brief Set Color of SpriteObject
		*
		* \param[in] color takes values as in order: red, blue, green, alpha
		* Alpha is used to set how transparent object is.
		*
		*/
		void SetColor(glm::vec4 color);

		/** \brief Sets if SpriteObject will be drawn.
		*
		* \param[in] state True = drawn.
		* Useful if object is created but does not want to be drawn just yet.
		*
		*/
		void SetDrawState(bool state);

		/** \brief Sets Texture for SpriteObject
		*
		* \param[in] texture Uses given texture. 
		* Old texture pointer will be deleted.
		* Always create new texture for GameEntity, using same texture will cause crashes upon GameObject destruction \ while setting new texture
		* 
		*/
		void SetTexture(pm::Texture* texture);

		/** \brief loads texture for SpriteObject
		*
		* \param[in] filename Loads texture from given filename
		* Old texture pointer will be deleted.
		*
		*/
		void SetTexture(std::string filename);

		/** \brief set textureCoordinates for SpriteObject
		*
		* \param[in] glm::vec4 Sets textureCoordinates from given glm::vec4
		* 
		*
		*/
		void SetTextureCoordinates(glm::vec4 textureCoordinates);

		/** \brief set textureCoordinates for SpriteObject
		*
		* \param[in] glm::vec2 top left coordinate 
		* \param[in] glm::vec2 bottom right coordinate
		* takes two coordinates and makes a rectangle out of them to use as texture rectangle
		* 
		*/
		void SetTextureCoordinates(glm::vec2 leftTop, glm::vec2 rightBottom);

		/** \brief set textureCoordinates for SpriteObject
		*
		* \param[in] float left coordinate
		* \param[in] float top coordinate
		* \param[in] float right coordinate
		* \param[in] float bottom coordinate
		* takes four float values to form a rectangle 
		* as x1, y1, x2, y2
		*/
		void SetTextureCoordinates(float left, float top, float right, float bottom);

		/** \brief set texture dimensions for SpriteObject
		*
		* \param[in] glm::vec4 Sets texture dimensions from given glm::vec4
		* takes the coordinates 
		* 
		*/
		void SetTextureDimensions(glm::vec4 textureDimensions);

		/** \brief set texture dimensions for SpriteObject
		*
		* \param[in] glm::vec2 top left coordinate
		* \param[in] glm::vec2 width and height of the rectangle
		* takes one coordinate, width and height and makes a rectangle out of them to use as texture dimensions
		*
		*/
		void SetTextureDimensions(glm::vec2 leftTop, glm::vec2 widthHeight);

		/** \brief set textureCoordinates for SpriteObject
		*
		* \param[in] float left coordinate
		* \param[in] float top coordinate
		* \param[in] float width
		* \param[in] float height
		* takes four float values to form a rectangle
		* as x1, y1, widht, height
		* textCoord0 = x1;
		* textCoord1 = y1 + height;
		* textCoord2 = x1 + width;
		* textCoord3 = y1;
		*/
		void SetTextureDimensions(float left, float top, float width, float height);

		/* \brief returns position of SpriteObject
		*
		* \return glm::vec2
		* returns the position of the SpriteObject in xy-coordinates
		*
		*/
		glm::vec2 GetPosition();

		/* \brief returns size of SpriteObject
		*
		* \return glm::vec2
		* returns the size of the SpriteObject
		* default is 1,1 values greater than 1 increase the size and lower than 1 decrease
		* lower than 0 may flip the spriteObject
		*/
		glm::vec2 GetSize();

		/* \brief returns origin of SpriteObject
		*
		* \return glm::vec2
		* returns the origin of the SpriteObject in xy-coordinates 
		* default is 0,0 that defaults to the top-left corner of the sprite
		*/
		glm::vec2 GetOrigin();

		/* \brief returns color of SpriteObject
		*
		* \return glm::vec4
		* returns the color of the Sprite object
		* Values between 0.0f-1.0f.
		*/
		glm::vec4 GetColor();

		/* \brief returns rotation of the SpriteObject
		*
		* \return GLfloat
		* returns the rotation in degrees
		* 
		*/
		GLfloat GetRotation();

	};
}

#endif
