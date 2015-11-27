#include "RenderSystem.h"

#include <core\Log.h>
#include <core\Memory.h>
#include <core\Passert.h>
#include <core\Vector2.h>
#include <core\Application.h> // Only needed for resolution at the moment.

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\mat4x4.hpp>

using namespace pm;
using namespace std;

RenderSystem* RenderSystem::instance = nullptr;
bool RenderSystem::initialized = false;

RenderSystem* RenderSystem::GetInstance()
{
	if (instance == nullptr)
		instance = NEW RenderSystem();
	return instance;
}

void RenderSystem::DestroyInstance()
{
	delete instance;
	instance = nullptr;
	initialized = false;
}

void RenderSystem::Initialize()
{
	DEBUG_GL_ERROR_CLEAR();
	
	glm::vec2 resolution = Application::GetInstance()->window.GetResolution(); // Get resolution of display.
	float right = resolution.x; // Calculate limits.
	float top = resolution.y;
	glm::mat4 projectionMatrix = glm::ortho(0.0f, right, top, 0.0f, 1.0f, 0.0f);

	vertexBuffer.CreateBuffer(VERTEX);
	indexBuffer.CreateBuffer(INDEX);

	CreateShaders();

	transformMatrixLocation = glGetUniformLocation(shaderProgram.GetShaderProgramLocation(), "transformable");
	DEBUG_GL_ERROR();

	cameraMatrixLocation = glGetUniformLocation(shaderProgram.GetShaderProgramLocation(), "camera");
	DEBUG_GL_ERROR();

	projectionLocation = glGetUniformLocation(shaderProgram.GetShaderProgramLocation(), "unifProjectionTransform");
	DEBUG_GL_ERROR();

	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	DEBUG_GL_ERROR();

	initialized = true;
	DEBUG_INFO(("RenderSystem initialize finished."));

	//cameraSystem = CameraSystem::GetInstance();
}

void RenderSystem::CreateShaders()
{
	DEBUG_GL_ERROR_CLEAR();

	bool tempCheck = shaderProgram.AddShader("DEF_VERTEX_SHADER.txt", GL_VERTEX_SHADER); // Create default vertex shader.
	DEBUG_GL_ERROR();
	//ASSERT(tempCheck);

	tempCheck = shaderProgram.AddShader("DEF_FRAGMENT_SHADER.txt", GL_FRAGMENT_SHADER); // Create default fragment shader.
	DEBUG_GL_ERROR();
	//ASSERT(tempCheck);

	shaderProgram.AddVertexAttribPointer("attrPosition", 3, 9, 0); // Vertex attributes defined by default shaders.
	shaderProgram.AddVertexAttribPointer("attrColor", 4, 9, 3);
	shaderProgram.AddVertexAttribPointer("texPosition", 2, 9, 7);

	shaderProgram.LinkProgram();
	shaderProgram.UseProgram();

	glEnable(GL_BLEND);
	DEBUG_GL_ERROR();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	DEBUG_GL_ERROR();

	glEnable(GL_DEPTH_TEST);
	glClearDepthf(1.0);

	glDepthFunc(GL_LEQUAL);
	DEBUG_GL_ERROR();

	GLint tempLocation = glGetUniformLocation(shaderProgram.GetShaderProgramLocation(), "image");
	DEBUG_GL_ERROR();

	glUniform1i(tempLocation, 0);
	DEBUG_GL_ERROR();

	DEBUG_INFO(("Default shaders done!"));
}

void RenderSystem::Draw(Batch* batch)
{
	Draw(batch, &shaderProgram);
}

void RenderSystem::Draw(Batch* batch, Shader* shader)
{
	shader->UseProgram();

	BindBuffers(batch);

	shader->UseVertexAttribs();

	glActiveTexture(GL_TEXTURE0);
	DEBUG_GL_ERROR();

	glBindTexture(GL_TEXTURE_2D, batch->textureIndex);
	DEBUG_GL_ERROR();
	
	glUniformMatrix4fv(cameraMatrixLocation, 1, GL_FALSE, value_ptr(CameraSystem::GetInstance()->GetActiveCamera()->GetCameraMatrix()));
	DEBUG_GL_ERROR();


	for (int i = 0; i < batch->GetTransformMatrixPointer()->size(); i++)
	{
		int tempInt = 6 * i * sizeof(GLushort);
	
		glUniformMatrix4fv(transformMatrixLocation, 1, GL_FALSE, value_ptr(batch->GetTransformMatrixPointer()->at(i)));
		DEBUG_GL_ERROR();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, reinterpret_cast<GLvoid*>(tempInt));
		DEBUG_GL_ERROR();
		
	}

	glBindTexture(GL_TEXTURE_2D, 0u);
	DEBUG_GL_ERROR();
}

bool RenderSystem::IsInitialized()
{
	return initialized;
}

void RenderSystem::BindBuffers(Batch* batch)
{
	vertexBuffer.BindBufferData(batch->GetVertexDataPointer()->size(), batch->GetVertexDataPointer()->data());
	indexBuffer.BindBufferData(batch->GetIndexDataPointer()->size(), batch->GetIndexDataPointer()->data());
}

RenderSystem::~RenderSystem()
{
}