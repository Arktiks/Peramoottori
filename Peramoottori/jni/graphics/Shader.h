#ifndef SHADER_H
#define SHADER_H

#include "structs\ShaderVertexAttrib.h"
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <vector>
#include <string>
class Shader
{
public:

	Shader() : created(false), shaderProgram(0) {};
	Shader(GLuint shader);
	~Shader() {};

	bool AddShader(std::string filePath, GLenum shaderType);

	bool LinkProgram();
	bool GetLinkStatus();
	void RunProgram();
	GLuint GetAttribLocation(std::string attributeName);
	GLuint GetShaderProgramLocation(){ return shaderProgram; };
	void AddVertexAttribPointer(std::string attributeName, GLint size, GLsizei stride, GLint offset);

private:

	std::vector<ShaderVertexAttrib> ShaderVertexAttribs;
	GLuint shaderProgram;
	const char* LoadShader(std::string filePath);
	bool created;

};

#endif