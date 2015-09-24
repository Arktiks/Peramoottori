#ifndef BUFFER_H
#define BUFFER_H

#include <GLES2\gl2.h>

namespace pm
{
	/** Different types of OpenGL buffer objects. */
	enum bufferType
	{
		NONE, ///< Type has not been set.
		VERTEX, ///< GL_ARRAY_BUFFER
		INDEX ///< GL_ELEMENT_ARRAY_BUFFER
	};

	/** \brief Class that works as OpenGL buffer object necessary for rendering.
	*
	* Buffer Objects are an OpenGL feature that provides methods for uploading
	* vertex data (position, normal vector, color, etc.) to the video device for non-immediate-mode rendering.
	*
	* Most likely developer does not need to create his own buffers and should instead
	* use the functions found in SpriteBatch class.
	*
	* \note Current buffer sizes are hard coded which should lead to unexcpected behavior if
	* enough GameEntities are set to be drawn. This will be fixed on future Perämoottori version.
	*/

	class Buffer
	{
	public:

		/** \brief Construct Buffer with unset type. */
		Buffer() : index(0), type(NONE) {};

		/** \brief Initialize buffer of chosen type.
		*
		* \param[in] type 
		*/
		void CreateBuffer(bufferType type);

		void BindBufferData(unsigned size, void *data);

		bufferType GetType() { return type; }

		GLuint GetIndex() { return index; }

		~Buffer();

	private:

		/// Used to initialize data storage for buffers.
		void InitializeVertexData();

		void InitializeIndexData();

		void BindVertexData(unsigned size, void *data);

		void BindIndexData(unsigned size, void *data);

		GLuint index;
		bufferType type;
	};
}

#endif