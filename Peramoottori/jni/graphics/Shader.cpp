#include "Shader.h"
#include <resources\ResourceManager.h>
#include <core\Log.h>
#include <core\Passert.h>

using namespace pm;

bool Shader::AddShader(std::string filePath, GLenum ShaderType)
{
	if (!created)
	{
		shaderProgram = glCreateProgram();
		created = true;
	}

	GLuint tempShader = 0;
	tempShader = glCreateShader(ShaderType); // määrittää shaderin tyypin

	std::string loadedString = LoadShader(filePath);
	const char* charArray = loadedString.c_str();
	glShaderSource(tempShader, 1, &charArray, nullptr); // antaa shaderille ladatun shaderfilen
	
	glCompileShader(tempShader);

	GLint compiled = 0;
	glGetShaderiv(tempShader, GL_COMPILE_STATUS, &compiled);
	
	if (!compiled)
	{
		GLint length = 0;
		glGetShaderiv(tempShader, GL_INFO_LOG_LENGTH, &length);

		if (length > 0)
		{
			GLint infoLength = 0;
			char* infoBuf = (char*) malloc(sizeof(char) * length);

			glGetShaderInfoLog(tempShader, length, &infoLength, infoBuf);

			DEBUG_INFO(("%s", infoBuf));

			//free(infoBuf);
			delete infoBuf;
		}

		glDeleteShader(tempShader);
		//created = false;
		DEBUG_WARNING(("Shader not created!"));

		return false;
	}

	glAttachShader(shaderProgram, tempShader);
	return true;
}
std::string Shader::LoadShader(std::string filePath)
{
	std::string tempString = ResourceManager::GetInstance()->ReadText(filePath);
	tempString.push_back('\0');

	return tempString;
}

bool Shader::LinkProgram()
{
	GLint linkCheck = GL_FALSE;

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkCheck);

	ASSERT_EQUAL(linkCheck, GL_TRUE);

	return true;
}

bool Shader::GetLinkStatus()
{
	GLint linkCheck = GL_FALSE;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkCheck);
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
	glUseProgram(shaderProgram);
}

GLuint Shader::GetAttribLocation(std::string attributeName)
{
	return glGetAttribLocation(shaderProgram, attributeName.c_str());
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

