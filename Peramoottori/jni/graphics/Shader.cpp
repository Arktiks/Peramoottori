#include "Shader.h"
#include <resources\ResourceManager.h>
#include <core\Log.h>
#include <core\Passert.h>

using namespace pm;
using namespace std;

bool Shader::AddShader(string filePath, GLenum ShaderType)
{
	if (!created) // Shader program has not been created.
	{
		shaderProgram = glCreateProgram();
		ASSERT_NEQUAL(shaderProgram, 0); // Function returns 0 if an error occurs creating the program object.
		created = true;
	}

	GLuint tempShader = 0; // Empty shader object reference.
	tempShader = glCreateShader(ShaderType); // Generate value it can be reference upon.
	DEBUG_GL_ERROR();
	ASSERT_NEQUAL(tempShader, 0);

	string loadedString = LoadShader(filePath); // LoadShader has error checking.
	const GLchar* charArray = loadedString.c_str(); // NOTE: Couldn't you use string directly?

	glShaderSource(tempShader, 1, &charArray, nullptr); // Replace source code in shader object.
	DEBUG_GL_ERROR();

	glCompileShader(tempShader);
	DEBUG_GL_ERROR();

	DEBUG_GL_SHADER_ERROR((tempShader)); // Test compile status and log possible errors.

	/*GLint compiled = 0;
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
	}*/

	glAttachShader(shaderProgram, tempShader); // Attach shader object to program object.

	//glDetachShader(shaderProgram, tempShader); // Decrement reference.
	//glDeleteShader(tempShader);

	return true;
}

bool Shader::LinkProgram()
{
	GLint linkCheck = GL_FALSE;

	glLinkProgram(shaderProgram);
	DEBUG_GL_ERROR();

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkCheck);
	DEBUG_GL_ERROR();
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

	if (linkCheck == GL_TRUE)
		return true;
	else
		return false;
}

void Shader::UseVertexAttribs()
{
	for (int i = 0; i < ShaderVertexAttribs.size(); i++)
	{
		GLint tempLocation = GetAttribLocation(ShaderVertexAttribs[i].attributeName); // Return location of attribute variable.
		ASSERT_NEQUAL(tempLocation, -1);

		glVertexAttribPointer( // Define array of generic vertex attribute data.
			tempLocation,
			ShaderVertexAttribs[i].size,
			GL_FLOAT,
			GL_FALSE,
			ShaderVertexAttribs[i].stride * sizeof(GLfloat),
			reinterpret_cast<GLvoid*>((ShaderVertexAttribs[i].offset) * sizeof(GLfloat)));

		glEnableVertexAttribArray(tempLocation); // Enables generic vertex attribute array specified by index.
		DEBUG_GL_ERROR();
	}
}

void Shader::UseProgram()
{
	glUseProgram(shaderProgram);
}

GLuint Shader::GetAttribLocation(std::string attributeName)
{
	GLint tempCheck = glGetAttribLocation(shaderProgram, attributeName.c_str());

	if (tempCheck < -1)
	{
		DEBUG_WARNING(("Couldn't find attribute location for %s.", attributeName.c_str()));
		return 0;
	}
	else
		return tempCheck;
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

Shader::~Shader()
{
	glDeleteProgram(shaderProgram);
}

std::string Shader::LoadShader(std::string filePath)
{
	std::string tempString = ResourceManager::GetInstance()->ReadText(filePath);

	if (tempString.empty())
		DEBUG_WARNING(("LoadShader failed, could not open: (%s).", filePath.c_str()));

	tempString.push_back('\0');

	return tempString;
}

/*void Shader::AddSamplerLocation(std::string samplerName)
{
DEBUG_WARNING(("glGetError Shader line 111: %i", glGetError()));
samplerLoc = glGetUniformLocation(shaderProgram, samplerName.c_str());
DEBUG_WARNING(("glGetError Shader line 113: %i", glGetError()));
}*/