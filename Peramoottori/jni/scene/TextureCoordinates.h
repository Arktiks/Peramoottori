#ifndef TEXTURECOORDINATES_H
#define TEXTURECOORDINATES_H

#include <GLES2\gl2.h>
#include <glm\vec4.hpp>
#include <glm\vec2.hpp>
#include <scene\Component.h>
#include <vector>

namespace pm
{

	class TextureCoordinates : public Component
	{
	public:

		TextureCoordinates(float left, float top, float right, float bottom);
		TextureCoordinates(glm::vec2 leftTop, glm::vec2 rightBottom);
		TextureCoordinates(glm::vec4 textureCoordinates);

		/// Set texture Coordinates.
		void SetTextureCoordinates(float left, float top, float right, float bottom);

		/// Set texture coordinates.
		void SetTextureCoordinates(glm::vec2 leftTop, glm::vec2 rightBottom);

		/// Set texture coordinates.
		void SetTextureCoordinates(glm::vec4 leftTopRightBottom);

		/// Returns texture vertices as float vector 4x2 values .
		std::vector<GLfloat> GetTextureCoordinates() { return textureCoordinates; };

	private:
		std::vector<GLfloat> textureCoordinates;
	};
}

#endif //TEXTURECOORDINATES_H