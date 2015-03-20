#ifndef SHADER_H
#define SHADER_H

#include <structs/ShaderVertexAttrib.h>
#include <EGL/egl.h>
#include <vector>
#include <string>

class Shader
{
public:

	Shader() : created(false), shaderProgram(0) {};
	Shader(GLuint shader) : created(false), shaderProgram(shader) {};
	~Shader() {};

	bool AddShader(std::string filePath, GLenum shaderType);

	bool LinkProgram();
	bool GetLinkStatus();
	void RunProgram();
	GLuint GetAttribLocation(std::string attributeName);
	void AddVertexAttribPointer(std::string attributeName, GLint size, GLsizei stride, GLint offset);

	GLuint GetShaderProgramLocation() { return shaderProgram; };

private:

	std::string LoadShader(std::string filePath);

	std::vector<ShaderVertexAttrib> ShaderVertexAttribs;
	GLuint shaderProgram;
	bool created;

};

#endif