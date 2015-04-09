#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <GLES2\gl2.h>
#include <scene\Component.h>
#include <glm\common.hpp>


namespace pm
{
	class Texture : public Component
	{
	public:

		Texture();

		void SetId(GLuint textureId);
		void SetTextureSize(glm::uvec2 textureSize);
		//Set Texture Vertices for full size texture.
		void SetTextureVertices();
		//Take a specific part of the texture in pixels
		void SetTextureVertices(glm::vec2 leftTop, glm::vec2 rightBottom);

		std::vector<GLfloat> GetTextureVertices() { return textureVertex; };
	
		GLuint GetId();
		glm::uvec2 GetTextureSize();


	private:

		GLuint textureIndex;
		std::vector<GLfloat> textureVertex;
		glm::uvec2 textureSize;

	};
}

#endif