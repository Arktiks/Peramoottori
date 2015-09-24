//#pragma once
#include "SpriteObject.h"
#include <vector>
#include <scene\Texture.h>
class Enemy :
	public SpriteObject
{
public:
	Enemy();	
	~Enemy();

	void Update(float deltaTime);
	void ChangeCurrentTexture();
	void UpdateTextureIndex();
	void AddTexture(pm::Texture* texture);
	void SetTextureVector(std::vector<pm::Texture*> textures);
private:
	bool justCreated;
	pm::Texture* currentTexture;
	float timer;
};

