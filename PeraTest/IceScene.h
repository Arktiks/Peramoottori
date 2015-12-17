#ifndef ICESCENE_H
#define ICESCENE_H
#include "pmScene.h"

class GameEntityFactory;

class IceScene:public pmScene
{
public:
	
	IceScene();
	~IceScene();

	void Update();
	void InitializeResources();
	void InitializeGameEntities();
	void UpdateGameEntities(float time);
};

#endif