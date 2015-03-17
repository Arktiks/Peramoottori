#ifndef SHADER_H
#define SHADER_H

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <string>

class Shader
{
public:

	Shader() : shader(0), compiled(0) {};
	Shader(GLuint shader);
	~Shader() {};

	Shader LoadShader(std::string filePath, GLenum shaderType);
	GLuint GetShader();

private:

	GLuint shader;
	GLint compiled;

};

#endif