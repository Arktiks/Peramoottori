#include "Buffer.h"
#include <core\Log.h>

using namespace pm;
unsigned Buffer::bufferSize = 50;

Buffer::Buffer(BUFFER_TYPE type) : index(0), type(BUFFER_TYPE::NONE)
{
	this->type = type;
	CreateBuffer();
}

void Buffer::CreateBuffer()
{
	DEBUG_GL_ERROR_CLEAR();

	glGenBuffers(1, &index); // Generate buffer object names.
	DEBUG_GL_ERROR();

	if (type == VERTEX)
		InitializeVertexData();
	else if (type == INDEX)
		InitializeIndexData();
	else
		DEBUG_WARNING(("Trying to create unknown buffer type (%i).", type));
}

void Buffer::BindBufferData(unsigned size, void *data)
{
	if (bufferSize * type < size)
		ResizeBuffer(size);

	if (type == VERTEX)
		BindVertexData(size, data);
	else if(type == INDEX)
		BindIndexData(size, data);
	else
		DEBUG_WARNING(("Trying to bind buffer data of unknown type."));
}

// glBufferData creates new data store for the buffer object currently bound to target.
// Any pre-existing data store is DELETED.
// Need to modify hardcoded buffer sizes.

void Buffer::InitializeVertexData()
{
	DEBUG_GL_ERROR_CLEAR();

	glBindBuffer(GL_ARRAY_BUFFER, index);
	DEBUG_GL_ERROR();

	glBufferData(GL_ARRAY_BUFFER, bufferSize * 36 * sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW);
	DEBUG_GL_ERROR();

	glBindBuffer(GL_ARRAY_BUFFER, 0u);
	DEBUG_GL_ERROR();
}

void Buffer::InitializeIndexData()
{
	DEBUG_GL_ERROR_CLEAR();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	DEBUG_GL_ERROR();

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize * 6 * sizeof(GLushort), nullptr, GL_DYNAMIC_DRAW);
	DEBUG_GL_ERROR();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
	DEBUG_GL_ERROR();
}

void Buffer::BindVertexData(unsigned size, void *data)
{
	DEBUG_GL_ERROR_CLEAR();

	glBindBuffer(GL_ARRAY_BUFFER, index);
	DEBUG_GL_ERROR();

	glBufferSubData(GL_ARRAY_BUFFER, 0u, size * sizeof(GLfloat), data);
	DEBUG_GL_ERROR();
}

void Buffer::BindIndexData(unsigned size, void *data)
{
	DEBUG_GL_ERROR_CLEAR();
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	DEBUG_GL_ERROR();

	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0u, size*sizeof(GLushort), data);
	DEBUG_GL_ERROR();
}

void Buffer::ResizeBuffer(unsigned size)
{
	while (bufferSize * type < size)
		bufferSize *= 2;

	DeleteBuffer();
	CreateBuffer();
}

void Buffer::DeleteBuffer()
{
	switch (type)
	{
		case VERTEX:
			glBindBuffer(GL_ARRAY_BUFFER, 0u);
			break;
		case INDEX:
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
			break;
	}
	glDeleteBuffers(1, &index);
}

Buffer::~Buffer()
{
	// Handle cleaning up the buffers.
	DeleteBuffer();
}