#include "Game.h"
#include <vector>

using namespace PORT;

Game* Game::gameInstance = nullptr;

Game::Game()
{
	filePath = "pottu.obj";

	ObjectLoader::getInstance()->loadObject(filePath, vertices, indices);

#if defined ANDROID
	for (int i = 0; i < indices.size(); i++)
	{
		LOG("Index: %i", indices.at(i));
		LOG("VertexBuffer: %f %f %f\n%f %f %f\n%f %f", vertices.at(i*8+0),vertices.at(i*8+1), vertices.at(i*8+2), vertices.at(i*8+3), vertices.at(i*8+4), vertices.at(i*8+5), vertices.at(i*8+6), vertices.at(i*8+7));
	}
#endif

	shader = Shader::getInstance();

	vbufferi.createBuffer(PORTVERTEX);
	ibufferi.createBuffer(PORTINDEX);
	
	testi = new Texture("pslogo.png");

	vbufferi.pushData(sizeof(GLfloat)*vertices.size(), vertices.data());
	ibufferi.pushData(sizeof(GLushort)*indices.size(), indices.data());
}


Game::~Game()
{
}

Game* Game::instance()
{
	if (gameInstance == nullptr)
		gameInstance = new Game();

	return gameInstance;
}
void Game::update()
{
	glUseProgram(*shader->getProgram());
	
	glBindTexture(GL_TEXTURE_2D, testi->getIndex());

	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);

	glBindBuffer(GL_ARRAY_BUFFER, vbufferi.getIndex());

	shader->useShader();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibufferi.getIndex());

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0u);

	glUseProgram(0u);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
	glBindTexture(GL_TEXTURE_2D, 0u);
}