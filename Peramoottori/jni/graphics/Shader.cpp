#include "Shader.h"
#include <GLES2\gl2.h>
#include <string>
#include <resources\ResourceManager.h>
#include <core\Log.h>
using namespace pm;


Shader::Shader(GLuint shader)
{
	this->shader = shader;
}

Shader Shader::LoadShader(std::string filePath, GLenum ShaderType)
{
	if (!created)
	{
		shader = glCreateProgram();
		created = true;
	}

	ResourceManager* r = ResourceManager::GetInstance();
	std::string tempString = r->ReadText(filePath);
	tempString.push_back('\0');
	//tempString.at(tempString.end()) = '\0';

	GLuint tempShader;
	tempShader = glCreateShader(ShaderType); // määrittää shaderin tyypin

	if (tempShader == 0)
	{
		DEBUG_WARNING(("Shader not created!"));
		return tempShader;
	}

	const char *charString = tempString.c_str(); // muuttaa Stringin char*:ksi 

	glShaderSource(tempShader, 1, &charString, NULL);// antaa shaderille ladatun shaderfilen

	glCompileShader(tempShader);
	
	glGetShaderiv(tempShader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLint msg = 0;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &msg);
		if (msg > 1)
		{
			char* info;
			glGetShaderInfoLog(shader, msg, NULL, info);

			DEBUG_INFO(("%s", info));

			free(info);
		}

		glDeleteShader(shader);
		DEBUG_WARNING(("Shader not created!"));
		return tempShader;
	}
	shader = tempShader;
}

bool Shader::LinkProgram()
{
	GLint linkCheck = NULL;
	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &linkCheck);

	if (linkCheck == GL_FALSE)
	{
		//PMdebug::MsgInfo("%s", "!!!! Linker fails - change this message to assert");
		return false;
	}
	else
	{
		return true;
	}
}
bool Shader::GetLinkStatus()
{
	GLint linkCheck = NULL;
	glGetProgramiv(shader, GL_LINK_STATUS, &linkCheck);
	if (linkCheck = GL_TRUE)
		return true;
	return false;
}

void Shader::RunProgram()
{
	for (int i = 0; i < ShaderVertexAttribs.size(); i++)
	{
		GLint tempLocation = GetAttribLocation(ShaderVertexAttribs[i].attributeName);
		glVertexAttribPointer(tempLocation, ShaderVertexAttribs[i].size, GL_FLOAT, GL_FALSE,
			ShaderVertexAttribs[i].stride * sizeof(GLfloat),
			reinterpret_cast<GLvoid*>((ShaderVertexAttribs[i].offset)* sizeof(GLfloat)));
		glEnableVertexAttribArray(tempLocation);
	}
	glUseProgram(shader);
}

GLuint Shader::GetAttribLocation(std::string attributeName)
{
	return glGetAttribLocation(shader, attributeName.c_str());
}



void Shader::AddVertexAttribPointer(std::string attributeName, GLint size, GLsizei stride, GLint offset)
{
	ShaderVertexAttrib tempAttrib;
	tempAttrib.attributeName = attributeName;
	tempAttrib.offset = offset;
	tempAttrib.size = size;
	tempAttrib.stride = stride;
	ShaderVertexAttribs.push_back(tempAttrib);
}
