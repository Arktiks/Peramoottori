#ifndef COLOR_H
#define COLOR_H

#include <scene\Component.h>
#include <glm\vec4.hpp>

namespace pm
{
	///
	/// Color component that GameEntity uses to create color for entities.
	///
	class Color : public Component
	{
	public:
		///
		/// Default constructor. Sets Color to (0.0f, 0.0f, 0.0f, 0.0f) (rgba)
		///
		Color();
		
		///
		/// Constructor that sets color to given color (rgba).
		///
		Color(glm::vec4 color);

		///
		/// Sets the color to given color (rgba).
		///
		void SetColor(glm::vec4 newColor);

		///
		/// Returns set color (rgba).
		///
		glm::vec4 GetColor();

	private:

		glm::vec4 color;
	};
}

#endif //COLOR_H