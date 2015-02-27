#include "Shader.h"
#include <resources\ResourceManager.h>
#include <system\PMdebug.h>
#include <string>
using namespace pm;

Shader::Shader()
{
	shader = NULL;
}

Shader::Shader(GLuint tempShader)
{
	shader = tempShader;
}

Shader Shader::LoadShader(const char* filePath, GLenum ShaderType)
{
	ResourceManager* r = ResourceManager::GetInstance();
	std::string tempString = r->ReadText(*filePath);
	tempString.at(tempString.end()) = '\0';

	GLuint tempShader;
	tempShader = glCreateShader(ShaderType); // määrittää shaderin tyypin

	if (tempShader == 0)
	{
		PMdebug::MsgWarning("%s", "shader not created");
		return Shader();
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

			PMdebug::MsgInfo("%s", info);

			free(info);
		}

		glDeleteShader(shader);

		return Shader();
	}

	return Shader(tempShader);
}

Shader::~Shader()
{
}

/*unsigned int Shader::AddShader(GLuint programObject)
{
	glAttachShader(shader, programObject);
}*/