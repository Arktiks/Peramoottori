#include "Texts.h"
#include <resources\ResourceManager.h>
#include <graphics\SpriteBatch.h>
#include <core\Application.h>
#include <core\Memory.h>

#define Resources pm::ResourceManager::GetInstance()
#define SB pm::SpriteBatch::GetInstance()
#define APP pm::Application::GetInstance()

Texts::Texts() : Scene("Texts")
{
	const unsigned int WIN_X = APP->window.GetResolution().x;
	const unsigned int WIN_Y = APP->window.GetResolution().y;

	auto arial = Resources->LoadAsset("Arial.ttf");
	auto sans = Resources->LoadAsset("ComicSans.ttf");
	auto t1 = Resources->LoadAsset("T1.txt");
	auto t2 = Resources->LoadAsset("T2.txt");
	auto t3 = Resources->LoadAsset("T3.txt");

	texts.push_back(NEW pm::Text(arial, t1, WIN_X * 0.1f, WIN_Y * 0.2f, // Location
		32.f, 32.f)); // Dimensions

	texts.push_back(NEW pm::Text(sans, t2, WIN_X * 0.1f, WIN_Y * 0.5f, // Location
		32.f, 32.f)); // Dimensions

	texts.push_back(NEW pm::Text(arial, t3, WIN_X * 0.1f, WIN_Y * 0.8f, // Location
		32.f, 32.f)); // Dimensions
}

Texts::~Texts()
{
	for (auto it = texts.begin(); it != texts.end(); it++)
		delete (*it);
}

void Texts::Update()
{
	for (auto& text : texts)
		SB->AddText(text);
}