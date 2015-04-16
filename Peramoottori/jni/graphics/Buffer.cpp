#include "Buffer.h"
#include "core\Log.h"

Buffer::Buffer()
{
	
}
void Buffer::createBuffer(bufferType type)
{
	this->type = type;
	glGenBuffers(1, &index);

	if (this->type == VERTEX)
	{
		BindVertexNullptr();
	}
	if (this->type == INDEX)
	{
		BindIndexNullptr();
	}
}

void Buffer::BindVertexNullptr()
{
	// NOT SURE IF NEEDED
	glBindBuffer(GL_ARRAY_BUFFER, index);
	glBufferData(GL_ARRAY_BUFFER, 4096u, nullptr, GL_STATIC_DRAW);
	DEBUG_WARNING(("glGetError Buffer line 28: %i", glGetError()));
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
	// 
}
void Buffer::BindIndexNullptr()
{
	// NOT SURE IF NEEDED
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4096u, nullptr, GL_STATIC_DRAW);
	DEBUG_WARNING(("glGetError Buffer line 37: %i", glGetError()));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
	// 
}

void Buffer::BindBufferData(unsigned size, void *data)
{
	if (type == VERTEX)
	{
		BindVertexData(size, data);
	}
	if (type == INDEX)
	{
		BindIndexData(size, data);
	}
}
void Buffer::BindVertexData(unsigned size, void *data)
{
	glBindBuffer(GL_ARRAY_BUFFER, index);
	glBufferSubData(GL_ARRAY_BUFFER, 0u, size * sizeof(GLfloat), data);
	DEBUG_WARNING(("glGetError Buffer line 55: %i", glGetError()));
}
void Buffer::BindIndexData(unsigned size, void *data)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0u, size*sizeof(GLushort), data);
	DEBUG_WARNING(("glGetError Buffer line 61: %i", glGetError()));

}
Buffer::~Buffer()
{
}
