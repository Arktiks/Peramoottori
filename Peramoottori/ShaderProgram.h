#pragma once
#include "graphics\Shader.h"
class ShaderProgram
{
public:
	ShaderProgram();

	ShaderProgram(Shader vertexShader, Shader fragmentShader);

	~ShaderProgram();

	Shader GetVertexShader();

	Shader GetFragmentShader();

	void UseProgram();

private:

	Shader vertexShader, fragmentShader;

};

