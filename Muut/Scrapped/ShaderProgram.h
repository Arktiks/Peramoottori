#pragma once
#include "graphics\Shader.h"
class ShaderProgram
{
public:
	ShaderProgram();

	/**
	*ShaderProgram 
	*
	*
	*/
	ShaderProgram(Shader vertexShader, Shader fragmentShader);

	~ShaderProgram();

	Shader GetVertexShader(){ return vertexShader; };
	void SetVertexShader(Shader vertexShader);

	Shader GetFragmentShader(){ return fragmentShader; };
	void SetFragmentShader(Shader fragmentShader);

	void AttachShaders(GLuint program);

private:

	Shader vertexShader, fragmentShader;

};

