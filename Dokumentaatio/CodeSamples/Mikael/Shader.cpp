#include "Shader.h"


using namespace PORT;
using namespace glm;
using namespace std;

Shader* Shader::instance = nullptr;


static const GLchar*  VERTEX_SOURCE =
"attribute vec3 attrPosition;\n"
"attribute vec3 attrColor;\n"
"attribute vec2 attrTexture;\n"

"varying vec3 varyColor;\n"
"varying vec2 textureCoords;\n"

"uniform mat4 unifWorld;\n"
"uniform mat4 unifProjection;\n"
"uniform mat4 unifView;\n"

"void main(void)\n"
"{\n"
"	textureCoords = attrTexture;\n"

"	//varyColor = attrColor;\n"
"	gl_Position = unifProjection * unifView * unifWorld * vec4(attrPosition, 1.0);\n"
"}\n";

static const GLchar*  FRAGMENT_SOURCE =
"varying vec3 varyColor;\n"

"varying vec2 textureCoords;\n"
"uniform sampler2D sampleri;\n"

"void main (void)\n"
"{\n"
"	gl_FragColor =  texture2D(sampleri, textureCoords);\n"
"}\n";

Shader* Shader::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Shader();
	}
	return instance;
}

int Shader::newShader()
{
	program = glCreateProgram();
	

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1u, &VERTEX_SOURCE, nullptr);
	glCompileShader(vertexShader);
	
	GLint compileResult;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileResult);


	glAttachShader(program, vertexShader);
	

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1u, &FRAGMENT_SOURCE, nullptr);
	glCompileShader(fragmentShader);
	
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileResult);


	glAttachShader(program, fragmentShader);
	
	glLinkProgram(program);

	GLint testResult;

	glGetProgramiv(program, GL_LINK_STATUS, &testResult);
		if (testResult != GL_TRUE)
			return 1;

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &testResult);
		if (testResult != GL_TRUE)
			return 1;

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &testResult);
		if (testResult != GL_TRUE)
			return 1;

		positionIndex = glGetAttribLocation(program, "attrPosition");
		if (positionIndex < 0)
			return 1;
		
		texIndex = glGetAttribLocation(program, "attrTexture");
		if (texIndex < 0);


		projectionLocation = glGetUniformLocation(program, "unifProjection");
		if (projectionLocation < 0)
			return 1;
		
		viewIndex = glGetUniformLocation(program, "unifView");
		if (viewIndex < 0)
			return 1;
		
		worldIndex = glGetUniformLocation(program, "unifWorld");
		if (worldIndex < 0)
			return 1;
		
	glUseProgram(program);
	
	glEnableVertexAttribArray(positionIndex);




	glEnableVertexAttribArray(texIndex);



	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	projection = glm::perspective(20.0f, 480.0f / 720.0f, 0.01f, 1000.0f);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, reinterpret_cast<float*>(&projection));

	mat4 tempView = translate(vec3(0.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(viewIndex, 1, GL_FALSE, reinterpret_cast<float*>(&tempView));

	
	glUseProgram(0u);

	return 0;
}

GLuint* Shader::getProgram()
{
	return &program;
}
static float muuttuja = 0;

void Shader::useShader()
{
	muuttuja += 0.03;

	mat4 tempWorld = translate(vec3(0.0f, -5.0f, -50.0f)) * rotate(muuttuja, vec3(1, 1, 1));
	glUniformMatrix4fv(worldIndex, 1, GL_FALSE, reinterpret_cast<float*>(&tempWorld));

	glVertexAttribPointer(positionIndex, 3u, GL_FLOAT, GL_FALSE, 32u, reinterpret_cast<GLvoid*>(0u));
	glVertexAttribPointer(texIndex, 2u, GL_FLOAT, GL_FALSE, 32u, reinterpret_cast<GLvoid*>(24u));
}
