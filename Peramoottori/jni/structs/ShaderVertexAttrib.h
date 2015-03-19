#ifndef SHADERVERTEXATTRIB_H
#define SHADERVERTEXATTRIB_H
#include <GLES2\gl2.h>
#include <string>
struct ShaderVertexAttrib
{
	std::string attributeName;
	GLint size;
	GLsizei stride;
	GLint offset;

	ShaderVertexAttrib()
	{
		attributeName = "";
		size = 0;
		stride = 0;
		offset = 0;
	}
};

#endif