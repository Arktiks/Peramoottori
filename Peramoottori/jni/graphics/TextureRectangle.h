#ifndef TEXTURERECTANGLE_H
#define TEXTURERECTANGLE_H

#include <scene\Component.h>
#include <glm\common.hpp>

namespace pm
{
	class TextureRectangle : public Component
	{
	public:
		TextureRectangle();
		TextureRectangle(float left, float top, float right, float bottom);

		void SetTextureRectangle(float newLeft, float newTop, float newRight, float newBottom);

	private:
		float left, top, right, bottom;
	};

}

#endif