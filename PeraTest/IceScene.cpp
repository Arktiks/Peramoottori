#include "IceScene.h"


IceScene::IceScene()
{
}


IceScene::~IceScene()
{
}


void IceScene::Update()
{}
void IceScene::InitializeResources()
{}
void IceScene::InitializeGameEntities()
{
	pm::GameEntity* gameEntity = gameEntityFactory->CreateWaves(glm::vec2(0,300), 6, 0);

}
void IceScene::UpdateGameEntities(float time)
{}