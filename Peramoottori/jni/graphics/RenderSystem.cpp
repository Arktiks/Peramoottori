#include "RenderSystem.h"
#include "glm\gtc\matrix_transform.hpp"

using namespace pm;

RenderSystem* RenderSystem::instance = nullptr;

RenderSystem* RenderSystem::GetInstance()
{
	if (instance == nullptr)
	{
		instance = NEW RenderSystem();
	}
	return instance;
}

void RenderSystem::DestroyInstance()
{
	delete instance;
	instance = nullptr;
}


RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::Initialize()
{
	glEnable(GL_TEXTURE_2D);
	vertexBuffer.createBuffer(VERTEX);
	indexBuffer.createBuffer(INDEX);
	CreateShaders();
	DEBUG_INFO(("RenderSystem initialize finished."));
}

void RenderSystem::Draw(Batch batch)
{
	BindBuffers(batch.totalVertexData, batch.totalIndexData);

	if (shaderProgram.GetLinkStatus())
	shaderProgram.UseProgram();

	glActiveTexture(GL_TEXTURE0);	// MAY NOT BE NEEDED
	//glEnable(GL_TEXTURE_2D);		// MAY NOT BE NEEDED, DONE IN Initialize()

	glUniform1i(shaderProgram.samplerLoc, 0);
	glBindTexture(GL_TEXTURE_2D, batch.textureIndex);
	GLint transformMatrixLocation = glGetUniformLocation(shaderProgram.GetShaderProgramLocation(), "transformable");
	for (int i = 0; i < batch.transformMatrixVector.size(); i++)
	{
		glUniformMatrix4fv(transformMatrixLocation, 1, GL_FALSE, value_ptr(batch.transformMatrixVector.at(i)));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,
		reinterpret_cast<GLvoid*>(6 * i));
	}
	glBindTexture(GL_TEXTURE_2D, 0u);
}

void RenderSystem::BindBuffers(std::vector<GLfloat> vertexData, std::vector<GLuint> indexData)
{
	vertexBuffer.BindBufferData(vertexData.size(), vertexData.data());
	indexBuffer.BindBufferData(indexData.size(), indexData.data());
}
void RenderSystem::CreateShaders()
{
	bool tempCheck = false;

	tempCheck = shaderProgram.AddShader("TestVertexShader.txt", GL_VERTEX_SHADER);
	ASSERT(tempCheck);

	tempCheck = shaderProgram.AddShader("TestFragmentShader.txt", GL_FRAGMENT_SHADER);
	ASSERT(tempCheck);

	shaderProgram.AddVertexAttribPointer("attrPosition", 3, 8, 0);
	shaderProgram.AddVertexAttribPointer("attrColor", 3, 8, 3);
	shaderProgram.AddVertexAttribPointer("texPosition", 2, 8, 6);
	shaderProgram.AddSamplerLocation("image");
	shaderProgram.LinkProgram();

	GLint projectionLocation = glGetUniformLocation(shaderProgram.GetShaderProgramLocation(), "unifProjectionTransform");
	Vector2<int> resolution = Game::GetInstance()->GetResolution();
	glm::mat4 projectionMatrix = glm::ortho(0, resolution.x, resolution.y, 0);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projectionMatrix));
	DEBUG_INFO(("Shaders done!."));
}