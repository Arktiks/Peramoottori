#pragma once
#include "Sprite.h"
#include <vector>
class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();
	void Draw();
	
private:
	void Update();
	void CreateBufferData();
	void Sort();
	std::vector<Sprite> drawables;// Saadaanko spritet lisättyä automaattisesti tähän listaan?
};

