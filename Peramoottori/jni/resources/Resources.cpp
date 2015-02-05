#include "Resources.h"
#include <lodepng.h>

char* Resources::TextReader(std::string fileName, Engine* engine)
{
	AAssetManager* assetManager = engine->app->activity->assetManager;
	AAsset* asset = AAssetManager_open(assetManager, fileName.c_str(), AASSET_MODE_UNKNOWN);
	if (asset)
	{
		size_t size = AAsset_getLength(asset);
		char* buffer = (char*)malloc(sizeof(char) * size + 1);
		AAsset_read(asset, buffer, size);
		buffer[size] = '\0';
		//LOGI("Luettu tiedosto %s (%d).", fileName.c_str(), size);
		//LOGI("%s", buffer);
		AAsset_close(asset);
		return buffer;
	}
	else
	{
		//LOGW("Tiedoston %s lukeminen ei onnistunut.", fileName.c_str());
		return nullptr;
	}
}

LoadedImage* Resources::PNGReader(std::string fileName, Engine* engine)
{
	//AAssetManager* assetManager = engine->app->activity->assetManager;
	//AAsset* asset = AAssetManager_open(assetManager, fileName.c_str(), AASSET_MODE_UNKNOWN);
	//http://www.learnopengles.com/loading-a-png-into-memory-and-displaying-it-as-a-texture-with-opengl-es-2-using-almost-the-same-code-on-ios-android-and-emscripten/
	// Kokeilla ensin LodePNG saada toimimaan, muuten pit‰‰ ehk‰ lukea bin‰‰rist‰ tai jotain.
}