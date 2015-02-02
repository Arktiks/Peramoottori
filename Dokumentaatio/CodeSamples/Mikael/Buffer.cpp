#include "Buffer.h"

using namespace PORT;

unsigned Buffer::bSize = 128;

Buffer::~Buffer()
{
	glDeleteBuffers(1, &index);
}

void Buffer::createBuffer(bufferType type)
{
	this->type = type;

	glGenBuffers(1, &index);

	if (this->type == PORTVERTEX)
	{
		glBindBuffer(GL_ARRAY_BUFFER, index);
		glBufferData(GL_ARRAY_BUFFER, bSize * 28 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0u);
	}
	if (this->type == PORTINDEX)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, bSize * 6 * sizeof(GLushort), nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
	}
}

void Buffer::pushData(unsigned size, void *data)
{
	if (type == PORTVERTEX)
	{
		glBindBuffer(GL_ARRAY_BUFFER, index);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);

		if (glGetError() == GL_INVALID_VALUE)
		{
			this->bSize *= 2;
			glDeleteBuffers(1, &index);
			createBuffer(type);
			glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0u);
	}
	if (type == PORTINDEX)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);

		if (glGetError() == GL_INVALID_VALUE)
		{
			this->bSize *= 2;
			glDeleteBuffers(1, &index);
			createBuffer(type);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
	}
}