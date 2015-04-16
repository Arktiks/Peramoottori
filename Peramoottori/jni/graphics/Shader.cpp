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

	const GLchar* charArray = loadedString.c_str();

	glShaderSource(tempShader, 1, &charArray, nullptr); // antaa shaderille ladatun shaderfilen

	glCompileShader(tempShader);

	GLint errorEnum = 0;
	errorEnum = glGetError();
	DEBUG_WARNING(("glGetError: %i", errorEnum));

	GLint compiled = 1;
	glGetShaderiv(tempShader, GL_COMPILE_STATUS, &compiled);
	
	if (!compiled)
	{
		GLsizei length = 0;
		glGetShaderiv(tempShader, GL_INFO_LOG_LENGTH, &length);

		if (length > 0)
		{
			GLsizei infoLength = 0;
			GLchar* infoBuf = (char*) malloc(sizeof(char) * length);	// Testaa joskus rikkoa shaderit

			glGetShaderInfoLog(tempShader, length, &infoLength, infoBuf);

			DEBUG_INFO(("%s", infoBuf));

			 free(infoBuf);
			//delete infoBuf;
		}

		glDeleteShader(tempShader);
		//created = false;
		DEBUG_WARNING(("Shader not created!"));

		return false;
	}

	glAttachShader(shaderProgram, tempShader);
	return true;
}

bool Shader::LinkProgram()
{
	GLint linkCheck = GL_FALSE;

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkCheck);

	ASSERT_EQUAL(linkCheck, GL_TRUE);

//	for (int i = 0; i < ShaderVertexAttribs.size(); i++)
//	{
//		GLint tempLocation = GetAttribLocation(ShaderVertexAttribs[i].attributeName);
//		glVertexAttribPointer(
//			tempLocation,
//			ShaderVertexAttribs[i].size,
//			GL_FLOAT,
//			GL_FALSE,
//			ShaderVertexAttribs[i].stride * sizeof(GLfloat),
//			reinterpret_cast<GLvoid*>((ShaderVertexAttribs[i].offset)* sizeof(GLfloat))
//			);
//		glEnableVertexAttribArray(tempLocation);
//	}

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

void Shader::UseVertexAttribs()
{
	for (int i = 0; i < ShaderVertexAttribs.size(); i++)
	{
		GLint tempLocation = GetAttribLocation(ShaderVertexAttribs[i].attributeName);
		ASSERT(tempLocation != -1);
		glVertexAttribPointer(
			tempLocation,
			ShaderVertexAttribs[i].size,
			GL_FLOAT,
			GL_FALSE,
			ShaderVertexAttribs[i].stride * sizeof(GLfloat),
			reinterpret_cast<GLvoid*>((ShaderVertexAttribs[i].offset)* sizeof(GLfloat))
			);
		DEBUG_WARNING(("glGetError Shader line 112: %i", glGetError()));
		glEnableVertexAttribArray(tempLocation);
		DEBUG_WARNING(("glGetError Shader line 114: %i", glGetError()));

	}
}

void Shader::UseProgram()
{
	glUseProgram(shaderProgram);
}

GLuint Shader::GetAttribLocation(std::string attributeName)
{
	return glGetAttribLocation(shaderProgram, attributeName.c_str());
}

void Shader::AddSamplerLocation(std::string samplerName)
{
	DEBUG_WARNING(("glGetError Shader line 111: %i", glGetError()));
	samplerLoc = glGetUniformLocation(shaderProgram, samplerName.c_str());
	DEBUG_WARNING(("glGetError Shader line 113: %i", glGetError()));
}


void Shader::AddVertexAttribPointer(std::string attributeName, GLint size, GLsizei stride, GLint offset)
{
	ShaderVertexAttrib tempAttrib;

	tempAttrib.attributeName = attributeName;
	tempAttrib.size = size;
	tempAttrib.stride = stride;
	tempAttrib.offset = offset;

	ShaderVertexAttribs.push_back(tempAttrib);
}

std::string Shader::LoadShader(std::string filePath)
{
	std::string tempString = ResourceManager::GetInstance()->ReadText(filePath);
	tempString.push_back('\0');

	return tempString;
}
