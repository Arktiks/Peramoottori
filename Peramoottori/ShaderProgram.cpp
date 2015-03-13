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

void ShaderProgram::UseProgram()
{
	
}
