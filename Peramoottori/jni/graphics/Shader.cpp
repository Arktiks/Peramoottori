#include "Shader.h"
#include <GLES2\gl2.h>
#include <string>
#include <resources\ResourceManager.h>
#include <core\Log.h>
#include <core\Passert.h>
using namespace pm;


Shader::Shader(GLuint shader)
{
	this->shader = shader;
}

bool Shader::LoadShader(std::string filePath, GLenum ShaderType)
{
	if (!created)
	{
		shader = glCreateProgram();
		created = true;
	}

	ResourceManager* r = ResourceManager::GetInstance();
	std::string tempString = r->ReadText(filePath);
	tempString.push_back('\0');
	const char *charString = tempString.c_str(); // muuttaa Stringin char*:ksi 

	GLuint tempShader;
	tempShader = glCreateShader(ShaderType); // määrittää shaderin tyypin

	glShaderSource(tempShader, 1, &charString, nullptr);// antaa shaderille ladatun shaderfilen

	glCompileShader(tempShader);
	
	glGetShaderiv(tempShader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLint msg = 0;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &msg);
		if (msg > 1)
		{
			char info[200];
			glGetShaderInfoLog(shader, 200, NULL, info);

			DEBUG_INFO(("%s", info));

			free(info);
		}
		glDeleteShader(shader);
		DEBUG_WARNING(("Shader not created!"));
		return false;
	}
	glAttachShader(shader, tempShader);
	return true;
}

bool Shader::LinkProgram()
{
	GLint linkCheck = NULL;
	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &linkCheck);

	ASSERT_EQUAL(linkCheck, GL_TRUE);

	return true;
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
