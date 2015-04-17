#ifndef TEXTURERECTANGLE_H
#define TEXTURERECTANGLE_H

#include <scene\Component.h>
#include <glm\vec4.hpp>

namespace pm
{
	class TextureRectangle : public Component
	{
	public:

		TextureRectangle();
		TextureRectangle(float left, float top, float right, float bottom);

		void SetTextureRectangle(float newLeft, float newTop, float newRight, float newBottom);

		glm::vec4 GetTextureRectangle();

	private:
		
		glm::vec4 rectangle;
	};
}

#endif