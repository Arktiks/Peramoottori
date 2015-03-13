#include "ShaderProgram.h"


ShaderProgram::ShaderProgram()
{
}

ShaderProgram::ShaderProgram(Shader tempvertexShader, Shader tempfragmentShader)
{
	vertexShader = tempvertexShader;

	fragmentShader = tempfragmentShader;
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::AttachShaders(GLuint program)
{
	GLuint tempVertexShader = vertexShader.GetShader();
	GLuint tempFragmentShader = fragmentShader.GetShader();

	glAttachShader(program, tempVertexShader);
	glAttachShader(program, tempVertexShader);
}
void ShaderProgram::SetVertexShader(Shader tempVertexShader)
{
	vertexShader = tempVertexShader;
}

void ShaderProgram::SetFragmentShader(Shader tempFragmentShader)
{
	fragmentShader = tempFragmentShader;
}