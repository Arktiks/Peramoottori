#include "Shader.h"
#include <resources\ResourceManager.h>
#include <resources\TextResource.h>
#include <core\Log.h>
#include <core\Passert.h>

using namespace pm;
using namespace std;

bool Shader::AddShader(string filePath, GLenum ShaderType)
{
	DEBUG_GL_ERROR_CLEAR();

	if (!created) // Shader program has not been created.
	{
		shaderProgram = glCreateProgram(); // Function returns 0 if an error occurs creating the program object.
		ASSERT_NEQUAL(shaderProgram, 0); 
		created = true;
	}

	if (vertex != 0 && ShaderType == GL_VERTEX_SHADER)
	{
		DEBUG_WARNING(("ShaderProgram (%i) already has vertex shader!", shaderProgram));
		return false;
	}
	else if (fragment != 0 && ShaderType == GL_FRAGMENT_SHADER)
	{
		DEBUG_WARNING(("ShaderProgram (%i) already has fragment shader!", shaderProgram));
		return false;
	}

	GLuint tempShader = 0; // Empty shader object reference.
	tempShader = glCreateShader(ShaderType); // Generate value it can be reference upon.
	DEBUG_GL_ERROR();
	ASSERT_NEQUAL(tempShader, 0);

	string loadedString = LoadShader(filePath); // LoadShader has error checking.
	const GLchar* charArray = loadedString.c_str(); // ...

	glShaderSource(tempShader, 1, &charArray, nullptr); // Replace source code in shader object.
	DEBUG_GL_ERROR();

	glCompileShader(tempShader);
	DEBUG_GL_ERROR();

	bool compileStatus = CheckShaderCompile(tempShader); // Test compile status and log possible errors.
	ASSERT(compileStatus);
	
	glAttachShader(shaderProgram, tempShader); // Attach shader object to program object.

	if (ShaderType == GL_VERTEX_SHADER)
		vertex = tempShader;
	else if (ShaderType == GL_FRAGMENT_SHADER)
		fragment = tempShader;

	return true;
}

bool Shader::LinkProgram()
{
	glLinkProgram(shaderProgram);
	bool linkStatus = CheckProgramLink(shaderProgram);
	ASSERT(linkStatus);
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
	DEBUG_GL_ERROR_CLEAR();

	for (int i = 0; i < ShaderVertexAttribs.size(); i++)
	{
		GLint tempLocation = GetAttribLocation(ShaderVertexAttribs[i].attributeName); // Return location of attribute variable.
		DEBUG_GL_ERROR();
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
	DEBUG_GL_ERROR_CLEAR();
	glUseProgram(shaderProgram);
	DEBUG_GL_ERROR();
}

GLuint Shader::GetAttribLocation(string attributeName)
{
	DEBUG_GL_ERROR_CLEAR();
	GLint tempCheck = glGetAttribLocation(shaderProgram, attributeName.c_str());
	DEBUG_GL_ERROR();

	if (tempCheck <= -1)
	{
		DEBUG_WARNING(("Could not find attribute location for %s.", attributeName.c_str()));
		return 0;
	}
	else
		return tempCheck;
}

void Shader::AddVertexAttribPointer(string attributeName, GLint size, GLsizei stride, GLint offset)
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
	DEBUG_GL_ERROR_CLEAR();

	if (vertex != 0)
	{
		glDetachShader(shaderProgram, vertex);
		DEBUG_GL_ERROR();
		glDeleteShader(vertex);
		DEBUG_GL_ERROR();
	}

	if (fragment != 0)
	{
		glDetachShader(shaderProgram, fragment);
		DEBUG_GL_ERROR();
		glDeleteShader(fragment);
		DEBUG_GL_ERROR();
	}

	glDeleteProgram(shaderProgram);
	DEBUG_GL_ERROR();
}

string Shader::LoadShader(string filePath)
{
	TextResource* decodedText = (TextResource*) ResourceManager::GetInstance()->LoadAsset(filePath);
	std::string tempString = decodedText->GetTextData();

	if (tempString.empty())
		DEBUG_WARNING(("LoadShader failed, could not open: (%s).", filePath.c_str()));
	else
		tempString.push_back('\0');

	return tempString;
}

bool Shader::CheckShaderCompile(GLuint shader)
{
	DEBUG_GL_ERROR_CLEAR();
	GLint tempCompiled = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &tempCompiled); // Return parameter from shader object.
	DEBUG_GL_ERROR();

	if (tempCompiled == GL_FALSE) // Shader does not compile.
	{
		GLsizei tempLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tempLength); // Get length of error message.
		DEBUG_GL_ERROR();

		if (tempLength > 0)
		{
			string tempInfoLog;
			tempInfoLog.reserve(tempLength); // Reserve space for the message.

			glGetShaderInfoLog(shader, tempLength, nullptr, &tempInfoLog[0]); // Add message to string.

			DEBUG_WARNING(("Shader could not compile!"));
			DEBUG_WARNING(("%s", tempInfoLog.c_str()));

			return false; // Leave asserting for user.
		}
	}
	else
		return true;
}

bool Shader::CheckProgramLink(GLuint program)
{
	DEBUG_GL_ERROR_CLEAR();
	GLint tempLink = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &tempLink); // Check link status.
	DEBUG_GL_ERROR();

	if (tempLink == GL_FALSE)
	{
		GLsizei tempLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &tempLength);
		DEBUG_GL_ERROR();

		if (tempLength > 0)
		{
			string tempInfoLog;
			tempInfoLog.reserve(tempLength);

			glGetProgramInfoLog(program, tempLength, nullptr, &tempInfoLog[0]);

			DEBUG_WARNING(("Shader program could not link!"));
			DEBUG_WARNING(("%s", tempInfoLog.c_str()));
			return false;
		}
	}
	else
		return true;
}