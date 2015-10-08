#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <string>
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
		Texture();

		Texture(std::string path);

		/// Sets the texture size.
		void SetTextureSize(glm::uvec2 textureSize);

		/// Return GLuint textureID.
		GLuint GetId();

		/// Returns glm uvec2 size of the texture.
		glm::uvec2 GetTextureSize();

		/// Sets the textureID.
		void SetId(GLuint textureId);

	private:

		GLuint textureIndex;
		glm::uvec2 textureSize;
	};
}

#endif