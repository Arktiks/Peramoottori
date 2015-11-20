#ifndef SPRITE_H
#define SPRITE_H
#include "Component.h"
#include <string>

namespace pm
{
	/* \brief Sprite component that automatically adds new components to its parent GameEntity.
	*
	* When adding a Sprite component to a GameEntity, Sprite automatically creates 
	* the following components: Drawable, Rectangle, Transformable, Color.
	* Also, if you give a texture filePath string to the Sprite component constructor,
	* following components will be added: Texture, TextureCoordinates.
	* 
	* \ingroup Scene
	*/
	class Sprite : public Component
	{
	public:
		/* \brief
		*
		* Default constructor for Sprite component. Following components will be added:
		* Drawable 
		* Rectangle
		* Transformable
		* Color
		*/
		Sprite();
		
		/* \brief
		*
		* Constructor for Sprite component. Following components will be added:
		* Drawable 
		* Rectangle
		* Transformable
		* Color
		* Texture
		* TextureCoordinates
		*/
		Sprite(std::string filePath);

		/* \brief
		*
		* Destructor for Sprite component.
		*/
		~Sprite();

		/* \brief
		*
		* Overloaded Component class function. Sets a parent GameEntity for the Sprite 
		* Component and adds the other components for the parent GameEntity.
		*/
		void SetParent(GameEntity* entity);

	private:
		std::string fP;
	};
}

#endif // SPRITE_H