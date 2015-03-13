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

	Shader() : created(false), shader(0) {};
	Shader(GLuint shader);
	~Shader();

	Shader LoadShader(const char* filePath, GLenum ShaderType);
	bool LinkProgram();
	bool GetLinkStatus();
	void RunProgram();
	GLuint GetAttribLocation(std::string attributeName);
	GLuint GetShaderProgramLocation(){ return shader; };
	void AddVertexAttribPointer(std::string attributeName, GLint size, GLsizei stride, GLint offset);
	//unsigned int AddShader(Shader shader, GLuint program);

private:

	std::vector<ShaderVertexAttrib> ShaderVertexAttribs;
	GLuint shader;
	GLint compiled;
	bool created;

};

#endif