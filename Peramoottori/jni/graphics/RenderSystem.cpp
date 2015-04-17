#include "core\Log.h"
#include "egl\egl.h"
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
	vertexBuffer.CreateBuffer(VERTEX);
	indexBuffer.CreateBuffer(INDEX);

	CreateShaders();

	GLint projectionLocation = glGetUniformLocation(shaderProgram.GetShaderProgramLocation(), "unifProjectionTransform");
	Vector2<int> resolution = Game::GetInstance()->GetResolution();
	float right = resolution.x;
	float top = resolution.y;
	glm::mat4 projectionMatrix = glm::ortho(0.0f, right, top, 0.0f);
	
	for (int i = 0; i < 4; i++)
		for (int n = 0; n < 4; n++)
			DEBUG_INFO(("%f", projectionMatrix[i][n]));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	//DEBUG_GL_ERROR();

	DEBUG_INFO(("RenderSystem initialize finished."));
}

void RenderSystem::Draw(Batch batch)
{
	shaderProgram.UseProgram();
	BindBuffers(batch.GetVertexData(), batch.GetIndexData()); 
	shaderProgram.UseVertexAttribs();
//	if (shaderProgram.GetLinkStatus())

	glActiveTexture(GL_TEXTURE0);	// MAY NOT BE NEEDED
	//glEnable(GL_TEXTURE_2D);		// MAY NOT BE NEEDED, DONE IN Initialize()

	//glUniform1i(shaderProgram.samplerLoc, 0);
	glBindTexture(GL_TEXTURE_2D, batch.textureIndex);

	DEBUG_WARNING(("glGetError RenderSystem line 60: %i", glGetError()));
	

	GLint transformMatrixLocation = glGetUniformLocation(shaderProgram.GetShaderProgramLocation(), "transformable");


	for (int i = 0; i < batch.transformMatrixVector.size(); i++)
	{
		int tempInt = 6 * i;
	
		glUniformMatrix4fv(transformMatrixLocation, 1, GL_FALSE, value_ptr(batch.transformMatrixVector.at(i)));

		DEBUG_WARNING(("glGetError RenderSystem line 71: %i", glGetError()));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, reinterpret_cast<GLvoid*>(tempInt));
	}
	glBindTexture(GL_TEXTURE_2D, 0u);
}

void RenderSystem::BindBuffers(std::vector<GLfloat> vertexData, std::vector<GLushort> indexData)
{
	vertexBuffer.BindBufferData(vertexData.size(), vertexData.data());
	indexBuffer.BindBufferData(indexData.size(), indexData.data());
}
void RenderSystem::CreateShaders()
{
	bool tempCheck = false;
	DEBUG_WARNING(("glGetError RenderSystem line 84: %i", glGetError()));

	tempCheck = shaderProgram.AddShader("TestVertexShader.txt", GL_VERTEX_SHADER);
	ASSERT(tempCheck);
	DEBUG_WARNING(("glGetError RenderSystem line 88: %i", glGetError()));
	tempCheck = shaderProgram.AddShader("TestFragmentShader.txt", GL_FRAGMENT_SHADER);
	ASSERT(tempCheck);

	shaderProgram.AddVertexAttribPointer("attrPosition", 3, 8, 0);
	shaderProgram.AddVertexAttribPointer("attrColor", 3, 8, 3);
	shaderProgram.AddVertexAttribPointer("texPosition", 2, 8, 6);
	//shaderProgram.AddSamplerLocation("image");
	shaderProgram.LinkProgram();
	shaderProgram.UseProgram();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLint tempLocation = glGetUniformLocation(shaderProgram.GetShaderProgramLocation(), "image");
	glUniform1i(tempLocation, 0);

	DEBUG_WARNING(("glGetError RenderSystem line 98: %i", glGetError()));
	
	DEBUG_WARNING(("glGetError RenderSystem line 101: %i", glGetError()));
	DEBUG_WARNING(("glGetError RenderSystem line 104: %i", glGetError()));

	DEBUG_WARNING(("glGetError RenderSystem line 107: %i", glGetError()));
	DEBUG_INFO(("Shaders done!."));
}