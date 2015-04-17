#ifndef BUFFER_H
#define BUFFER_H

#include <GLES2\gl2.h>

namespace pm
{
	enum bufferType
	{
		NONE,
		VERTEX,
		INDEX
	};

	// Needs commentating!

	class Buffer
	{
	public:
		Buffer() : index(0), type(NONE) {};

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