#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <GLES2\gl2.h>
#include <scene\Component.h>
#include <glm\vec2.hpp>

namespace pm
{
	/// Component for GameEntity stores texture vertices and textureID.

	class Texture : public Component
	{
	public:

		/// Default constructor.
		Texture() : Component() {};

		/// Sets the exture size.
		void SetTextureSize(glm::uvec2 textureSize);

		/// Set texture vertices for full size texture.
		void SetTextureVertices();

		/// Take specific part of the texture in pixels.
		void SetTextureVertices(glm::vec2 leftTop, glm::vec2 rightBottom);

		/// Returns texture vertices as float vector 4x2 values .
		std::vector<GLfloat> GetTextureVertices() { return textureVertex; };

		/// Return GLuint textureID.
		GLuint GetId();

		/// Returns glm uvec2 sixze of the texture.
		glm::uvec2 GetTextureSize();

		/// Sets the textureID.
		void SetId(GLuint textureId);

	private:

		GLuint textureIndex;

		std::vector<GLfloat> textureVertex;

		glm::uvec2 textureSize;
	};
}

#endif