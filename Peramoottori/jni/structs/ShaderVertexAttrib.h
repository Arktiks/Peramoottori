#ifndef SHADERVERTEXATTRIB_H
#define SHADERVERTEXATTRIB_H

#include <GLES2\gl2.h>
#include <string>

namespace pm
{
	struct ShaderVertexAttrib
	{
		std::string attributeName;
		GLint size;
		GLsizei stride;
		GLint offset;

		ShaderVertexAttrib() : size(0), stride(0), offset(0) {};

		ShaderVertexAttrib(std::string attributeName,
			GLint size, GLsizei stride, GLint offset) :
			attributeName(attributeName),
			size(size),
			stride(stride),
			offset(offset) {};
	};
}

#endif