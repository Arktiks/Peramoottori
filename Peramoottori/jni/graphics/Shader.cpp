#include "Shader.h"
#include <GLES2\gl2.h>
#include <string>
#include <resources\ResourceManager.h>
#include <core\Log.h>
using namespace pm;

Shader::Shader(GLuint shader)
{
	(this->shader) = shader;
}

Shader Shader::LoadShader(std::string filePath, GLenum ShaderType)
{
	ResourceManager* r = ResourceManager::GetInstance();
	std::string tempString = r->ReadText(filePath);
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

GLuint Shader::GetShader()
{
	return shader;
}