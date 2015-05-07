#ifndef BUFFER_H
#define BUFFER_H

#include <GLES2\gl2.h>

namespace pm
{
	enum BUFFER_TYPE
	{
		NONE = 0,
		VERTEX = 36,
		INDEX = 6
	};

	// Needs commentating!

	class Buffer
	{
	public:

		Buffer() : index(0), type(BUFFER_TYPE::NONE) {};

		Buffer(BUFFER_TYPE type);

		void CreateBuffer();

		void BindBufferData(unsigned size, void *data);

		BUFFER_TYPE GetType() { return type; }

		GLuint GetIndex() { return index; }

		~Buffer();

	private:

		/// Used to initialize data storage for buffers.
		static unsigned bufferSize;
		
		void InitializeVertexData();
		void InitializeIndexData();
		
		void BindVertexData(unsigned size, void *data);
		void BindIndexData(unsigned size, void *data);

		void ResizeBuffer(unsigned size);
		void DeleteBuffer();
		GLuint index;
		BUFFER_TYPE type;

	};
}

#endif