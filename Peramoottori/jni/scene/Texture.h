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

		/** \cond HIDDEN_SYMBOLS */
		/// enum translucency (translucent/opaque)
		enum TRANSLUCENCY
		{
			TRANSLUCENT = 0,
			OPAQUE = 1
		};
		/** \endcond */

		/** \brief Default constructor 
		*/
		Texture();

		/** \brief Custom constructor
		/* \param[in] path file path of the texture
		*/
		Texture(std::string path);

		/** \brief Set size of Texture.
		*
		* \param[in] textureSize glm::uvec2 [width, height].
		*/
		void SetTextureSize(glm::uvec2 textureSize);

		/** \brief Set the true size of Texture.
		*
		* \param[in] textureSize glm::uvec2 [width, height].
		*/
		void SetTrueSize(glm::uvec2 textureSize);

		/** \brief Return texture ID OpenGL has assigned for Texture.
		*
		* \return 0 if ID has not been assigned.
		*/
		GLuint GetId();

		/** \brief Return size of texture.
		*
		* This is the size of the openGL texture in memory.
		* If the original texture dimensions were not a power of two, this differs from "true size".
		*
		* \return glm::uvec2(0.0f, 0.0f) if size has not been set.
		*/
		glm::uvec2 GetTextureSize();

		/** \brief Return the loaded size of texture.
		*
		* True size is always the original size of the texture (file) that was loaded to memory.
		* 
		* \return 
		*/
		glm::uvec2 GetTrueSize();
		
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

		/** \brief Set translucency.
		*
		* Approriate OpenGL should be called before assigning enum.
		*
		* \param[in] translucency new translucency assigned.
		*/
		void SetTranslucency(TRANSLUCENCY translucency){};

		/** \brief Get translucency.
		*
		* Get the translucency of texture.
		*
		* \return translucency assigned.
		*/
		TRANSLUCENCY GetTranslucency(){ this->translucency = translucency; };
		
		/** \brief Get the file path this Texture was created from
		* \return File path of the file
		*/
		std::string GetFile(){ return file; };


	private:

		GLuint textureIndex;

		glm::uvec2 textureSize;
		glm::uvec2 trueSize;

		uint textureGroup;

		std::string file;

		TRANSLUCENCY translucency;




	};
}

#endif