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
	std::vector<Sprite> drawables;// Saadaanko spritet lis�tty� automaattisesti t�h�n listaan?
};

