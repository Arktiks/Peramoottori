#ifndef COLOR_H
#define COLOR_H

#include <scene\Component.h>
#include <glm\vec4.hpp>

namespace pm
{
	/// Color component that GameEntity uses to get different color entities.

	class Color : public Component
	{
	public:

		/// Default constructor.
		Color();

		/// Constructor.
		Color(glm::vec4 color);

		/// Sets the color with glm float vec4 rgba.
		void SetColor(glm::vec4 newColor);

		/// Returns glm vec4 that has the rgba values in float.
		glm::vec4 GetColor();

	private:

		glm::vec4 color;
	};
}

#endif //COLOR_H