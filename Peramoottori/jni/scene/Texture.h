#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <string>
#include <GLES2\gl2.h>
#include <scene\Component.h>
#include <glm\vec2.hpp>


namespace pm
{

	/** \brief Component for storing texture vertices and textureID.
	*
	* Description.
	*
	* \ingroup Scene
	*/

	class Texture : public Component
	{
	public:

		Texture();

		Texture(std::string path);

		/** \brief Set size of Texture.
		*
		* \param[in] textureSize glm::uvec2 [width, height].
		*/
		void SetTextureSize(glm::uvec2 textureSize);

		/** \brief Return texture ID OpenGL has assigned for Texture.
		*
		* \return 0 if ID has not been assigned.
		*/
		GLuint GetId();

		/** \brief Return size of texture.
		*
		* \return glm::uvec2(0.0f, 0.0f) if size has not been set.
		*/
		glm::uvec2 GetTextureSize();

		/** \brief Set texture ID.
		*
		* Approriate OpenGL should be called before assigning index.
		*
		* \param[in] textureId new texture index assigned by OpenGL.
		*/
		void SetId(GLuint textureId);

		/** \brief Return Texturegroup.
		*
		* \return textureGroup that has been assigned.
		*/
		uint GetTextureGroup();

		/** \brief Set texture Group.
		*
		* Approriate OpenGL should be called before assigning index.
		*
		* \param[in] TextureGroup new texture group assigned.
		*/
		void SetTextureGroup(uint TextureGroup);



	private:

		GLuint textureIndex;

		glm::uvec2 textureSize;

		uint textureGroup;




	};
}

#endif