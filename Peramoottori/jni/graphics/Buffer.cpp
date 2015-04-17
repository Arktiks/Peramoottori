#include "Buffer.h"
#include <core\Log.h>

using namespace pm;

void Buffer::CreateBuffer(bufferType type)
{
	(this->type) = type; // Set buffer type.
	glGenBuffers(1, &index); // Generate buffer object names.

	if (type == VERTEX)
		InitializeVertexData();
	else if (type == INDEX)
		InitializeIndexData();
	else
		DEBUG_WARNING(("Trying to create unknown buffer type (%i).", type));
}

// glBufferData creates new data store for the buffer object currently bound to target.
// Any pre-existing data store is DELETED.

void Buffer::InitializeVertexData()
{
	glBindBuffer(GL_ARRAY_BUFFER, index);
	glBufferData(GL_ARRAY_BUFFER, 4096u, nullptr, GL_STATIC_DRAW);

	//DEBUG_WARNING(("glGetError Buffer line 28: %i", glGetError()));
	DEBUG_GL_ERROR();

	glBindBuffer(GL_ARRAY_BUFFER, 0u);
}

void Buffer::InitializeIndexData()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4096u, nullptr, GL_STATIC_DRAW);

	//DEBUG_WARNING(("glGetError Buffer line 37: %i", glGetError()));
	DEBUG_GL_ERROR();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
}

void Buffer::BindBufferData(unsigned size, void *data)
{
	if (type == VERTEX)
		BindVertexData(size, data);
	else if (type == INDEX)
		BindIndexData(size, data);
	else
		DEBUG_WARNING(("Trying to bind buffer data of unknown type."));
}

void Buffer::BindVertexData(unsigned size, void *data)
{
	glBindBuffer(GL_ARRAY_BUFFER, index);
	glBufferSubData(GL_ARRAY_BUFFER, 0u, size * sizeof(GLfloat), data);

	//DEBUG_WARNING(("glGetError Buffer line 55: %i", glGetError()));
	DEBUG_GL_ERROR();
}

void Buffer::BindIndexData(unsigned size, void *data)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0u, size*sizeof(GLushort), data);

	//DEBUG_WARNING(("glGetError Buffer line 61: %i", glGetError()));
	DEBUG_GL_ERROR();
}

Buffer::~Buffer()
{
	// Handle cleaning up the buffers.
}