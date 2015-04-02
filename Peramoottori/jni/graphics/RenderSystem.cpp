#include "RenderSystem.h"


RenderSystem::RenderSystem()
{
}


RenderSystem::~RenderSystem()
{
}

void RenderSystem::Draw(Batch batch)
{
	glActiveTexture(GL_TEXTURE0);	// MAY NOT BE NEEDED
	glEnable(GL_TEXTURE_2D);		// MAY NOT BE NEEDED

	glUniform1i(shaderProgram.samplerLoc, 0);
	glBindTexture(GL_TEXTURE_2D, batch.textureIndex);

	glDrawElements(GL_TRIANGLES, batch.totalIndexData.size(), GL_UNSIGNED_INT,
		reinterpret_cast<GLvoid*>(0));
	glBindTexture(GL_TEXTURE_2D, 0u);
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