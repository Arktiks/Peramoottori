#pragma once
#include "Texture.h"

// TODO: Käyttäjälle tapa spriteen muokata erimuotoisia kappaleita, esim ympyrää, kolmiota, viivaa tai omaa.
// Koordinaatit omille indekseille omassa koordinaatistossaan, sitten sitä voi skaalailla, asettaa tekstuurin jotenkin..
// Tämä kustomoitavissa moottorin kautta? Vai pitääkö piirtää vaan sille sopiva? 
// Verrattuna grafiikkamoottoriin täytyy luoda erikokoisia taulukkoja -> siirrytään vektoriin?
class Sprite
{
public:
	Sprite();
	~Sprite();
private:
	Texture texture;

	// false construktorissa, muutetaan trueksi tekstuurin asettamisen jälkeen
	// Jos keksitään joku tapa katsoa onko tekstuuria olemassa (tai piiretäänkö se) voidaan poistaa tämä.
	// Tämä siis sen takia että spritebathchissa voidaan piirtää teksuurottomia spritejä.
	bool hasTexture;
	
};

