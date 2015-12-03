#ifndef COLOR_H
#define COLOR_H

#include <scene\Component.h>
#include <glm\vec4.hpp>

namespace pm
{

	/** \brief Color component that GameEntity uses to create color for entities.
	*
	* Uses RGBA-colors. Use values between 0.0f-1.0f.
	*
	* \ingroup Scene
	*/

	class Color : public Component
	{
	public:

		/** \brief Default Constructor
		*
		* Default color is (1.0f, 1.0f, 1.0f, 1.0f) [RGBA].
		*/
		Color();
		
		/** \brief Custom constructor
		*
		* \param[in] color as glm::vec4 [Red, Green, Blue, Alpha].
		*/
		Color(glm::vec4 color);

		/** \brief Custom constructor
		*
		* \param[in] color as four float values.
		*/

		Color(float red, float green, float blue, float alpha);

		/** \brief Set color.
		*
		* \param[in] newColor as glm::vec4 [Red, Green, Blue, Alpha].
		*/
		void SetColor(glm::vec4 newColor);

		/** \brief Set color.
		*
		* \param[in] color as four float values.
		*/

		void SetColor(float red, float green, float blue, float alpha);

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