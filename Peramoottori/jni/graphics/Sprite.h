#pragma once
#include "Texture.h"

// TODO: K�ytt�j�lle tapa spriteen muokata erimuotoisia kappaleita, esim ympyr��, kolmiota, viivaa tai omaa.
// Koordinaatit omille indekseille omassa koordinaatistossaan, sitten sit� voi skaalailla, asettaa tekstuurin jotenkin..
// T�m� kustomoitavissa moottorin kautta? Vai pit��k� piirt�� vaan sille sopiva? 
// Verrattuna grafiikkamoottoriin t�ytyy luoda erikokoisia taulukkoja -> siirryt��n vektoriin?
class Sprite
{
public:
	Sprite();
	~Sprite();
private:
	Texture texture;

	// false construktorissa, muutetaan trueksi tekstuurin asettamisen j�lkeen
	// Jos keksit��n joku tapa katsoa onko tekstuuria olemassa (tai piiret��nk� se) voidaan poistaa t�m�.
	// T�m� siis sen takia ett� spritebathchissa voidaan piirt�� teksuurottomia spritej�.
	bool hasTexture;
	
};

