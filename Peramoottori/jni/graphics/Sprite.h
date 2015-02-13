#pragma once
#include "Texture.h"
#include "graphics\Rectangle.h"

// TODO: K‰ytt‰j‰lle tapa spriteen muokata erimuotoisia kappaleita, esim ympyr‰‰, kolmiota, viivaa tai omaa.
// Koordinaatit omille indekseille omassa koordinaatistossaan, sitten sit‰ voi skaalailla, asettaa tekstuurin jotenkin..
// T‰m‰ kustomoitavissa moottorin kautta? Vai pit‰‰kˆ piirt‰‰ vaan sille sopiva? 
// Verrattuna grafiikkamoottoriin t‰ytyy luoda erikokoisia taulukkoja -> siirryt‰‰n vektoriin?
class Sprite : public Rectangle 
{
public:

	Sprite();
	Sprite(Texture texture);
	Sprite(Texture texture, float x, float y, float widht, float heigth);
	~Sprite();

	glm::vec2 getSourceRectSize();
	glm::vec2 getSourceRectPosition();

	void setSourceRectSize(glm::vec2 sourceRectSize);
	void setSourceRectPosition(glm::vec2 sourceRectPosition);
	void setSourceRect(glm::vec4 sourceRect);

	glm::vec2 getSourceRectSize();
	glm::vec2 getSourceRectPosition();
	glm::vec4 getSourceRect();

private:

	Texture texture;
	bool hasTexture;
	
	glm::vec4 sourceRect;


	// false construktorissa, muutetaan trueksi tekstuurin asettamisen j‰lkeen
	// Jos keksit‰‰n joku tapa katsoa onko tekstuuria olemassa (tai piiret‰‰nkˆ se) voidaan poistaa t‰m‰.
	// T‰m‰ siis sen takia ett‰ spritebathchissa voidaan piirt‰‰ tekstuurittomia spritej‰.

};

