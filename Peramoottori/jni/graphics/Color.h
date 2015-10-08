#ifndef COLOR_H
#define COLOR_H

#include <scene\Component.h>
#include <glm\vec4.hpp>

namespace pm
{

	/** \brief Color component that GameEntity uses to create color for entities.
	*
	* Description.
	*
	* \ingroup Scene
	*/

	class Color : public Component
	{
	public:

		/** \brief
		*
		* Default color is (0, 0, 0, 0) [RGBA].
		*/
		Color();
		
		/** \brief
		*
		* \param[in] color as glm::vec4 [Red, Green, Blue, Alpha].
		*/
		Color(glm::vec4 color);

		/** \brief Set color.
		*
		* \param[in] newColor as glm::vec4 [Red, Green, Blue, Alpha].
		*/
		void SetColor(glm::vec4 newColor);

		/** \brief Return color.
		*
		* \return glm::vec4 [Red, Green, Blue, Alpha].
		*/
		glm::vec4 GetColor();

	private:

		glm::vec4 color;
	};
}

#endif // COLOR_H