#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <GLES2\gl2.h>
#include <scene\Component.h>
#include <glm\vec2.hpp>


namespace pm
{
	class Texture : public Component
	{
	public:

		Texture() : Component() {};

		void SetTextureSize(glm::uvec2 textureSize);

		/// Set texture vertices for full size texture.
		void SetTextureVertices();

		/// Take specific part of the texture in pixels.
		void SetTextureVertices(glm::vec2 leftTop, glm::vec2 rightBottom);

		std::vector<GLfloat> GetTextureVertices() { return textureVertex; };


		void SetId(GLuint textureId);

		GLuint GetId();

		glm::uvec2 GetTextureSize();


	private:

		GLuint textureIndex;

		std::vector<GLfloat> textureVertex;

		glm::uvec2 textureSize;

	};
}

#endif