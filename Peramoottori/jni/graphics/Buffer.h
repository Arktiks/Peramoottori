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
	* %Buffer objects are an OpenGL feature that provides methods for uploading
	* vertex data (position, normal vector, color, etc.) to the video device for non-immediate-mode rendering.
	*
	* Most likely developer does not need to create his own pm::Buffer and should instead
	* use the functions found in SpriteBatch class.
	*
	* \note Current buffer sizes are hard coded which should lead to unexcpected behavior if
	* enough GameEntities are set to be drawn. This will be fixed on future Peramoottori version.
	*
	* \ingroup Graphics
	*/

	class Buffer
	{

		/** \internal Buffer class changed to private.
		* SpriteBatch and RenderSystem have been given friend status to accommodate.
		*/
		friend class RenderSystem;
		friend class SpriteBatch;

	private:

		/** \brief Construct pm::Buffer with unset type. */
		Buffer() : index(0), type(NONE) {};

		/** \brief Initialize OpenGL buffer object of chosen type.
		*
		* \param[in] type Defined by bufferType enum.
		*/
		void CreateBuffer(enum bufferType type);

		/** \brief Bind OpenGL buffer object to the specified binding point.
		*
		* Data store for the buffer object is also initialized.
		* \param[in] size in bytes of the data store region being replaced.
		* \param[in] data pointer to the new data that will be copied into the data store.
		*/
		void BindBufferData(unsigned size, void *data);

		/** \brief Return bufferType which this pm::Buffer was initialized as.
		* 
		* \return bufferType
		*/
		bufferType GetType() { return type; }

		/** \brief Return index which buffer object was assigned.
		*
		* \return 0 If pm::Buffer was not yet initialized.
		*/
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