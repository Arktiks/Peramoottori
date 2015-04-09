#include "RenderSystem.h"


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
	shaderProgram.RunProgram();

	glActiveTexture(GL_TEXTURE0);	// MAY NOT BE NEEDED
	glEnable(GL_TEXTURE_2D);		// MAY NOT BE NEEDED, DONE IN Initialize()

	glUniform1i(shaderProgram.samplerLoc, 0);
	glBindTexture(GL_TEXTURE_2D, batch.textureIndex);

	glDrawElements(GL_TRIANGLES, batch.totalIndexData.size(), GL_UNSIGNED_INT,
		reinterpret_cast<GLvoid*>(0));
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

	DEBUG_INFO(("Shaders done!."));
}