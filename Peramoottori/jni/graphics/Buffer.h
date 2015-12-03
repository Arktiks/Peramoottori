#ifndef BUFFER_H
#define BUFFER_H

#include <GLES2\gl2.h>

namespace pm
{
	/**
	* \brief Used to define what kind of buffer is generated
	*/
	enum BufferType
	{
		NONE,	///< Type has not been set.
		VERTEX,	///< GL_ARRAY_BUFFER
		INDEX	///< GL_ELEMENT_ARRAY_BUFFER
	};


	/** \brief Buffer class for holding vertex or index data
	* Class that holds the OpenGL buffers and is used for storing vertex or index data
	* \ingroup Graphics
	*/
	class Buffer
	{
		friend class RenderSystem;
		friend class SpriteBatch;

	private:

		Buffer() : index(0), type(BufferType::NONE), bufferSize(50) {};

		void CreateBuffer(enum BufferType type);

		void BindBufferData(unsigned size, void *data);

		BufferType GetType() { return type; }

		GLuint GetIndex() { return index; }

		~Buffer();



		void InitializeVertexData();
		void InitializeIndexData();

		void BindVertexData(unsigned size, void *data);
		void BindIndexData(unsigned size, void *data);

		void ResizeBuffer(unsigned size);
		void DeleteBuffer();
		
		GLuint index;
		BufferType type;
		unsigned int bufferSize;

	};
}

#endif