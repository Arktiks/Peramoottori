#include "Buffer.h"


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
	glBufferData(GL_ARRAY_BUFFER, 0u, nullptr, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
	// 
}
void Buffer::BindIndexNullptr()
{
	// NOT SURE IF NEEDED
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0u, nullptr, GL_STATIC_DRAW);
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
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
}
void Buffer::BindIndexData(unsigned size, void *data)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size*sizeof(GLuint), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);

}
Buffer::~Buffer()
{
}
