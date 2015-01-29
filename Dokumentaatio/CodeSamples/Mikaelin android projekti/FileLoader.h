#ifndef FILELOADER_H
#define FILELOADER_H

#if defined WIN32
#include <fstream>

#elif defined ANDROID
#include <android/asset_manager.h>

#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "NativeSample", __VA_ARGS__)
#endif
#include <string>


namespace PORT
{
	class FileLoader
	{
	public:
		std::string loadFile(std::string filePath);
		static FileLoader* getInstance();

#if defined WIN32

#elif defined ANDROID
		void setAssetManager(AAssetManager *assMan) { manager = assMan; };
#endif

	private:
		FileLoader(){};
		~FileLoader(){};

		static FileLoader* instance;

#if defined WIN32

#elif defined ANDROID
		AAssetManager* manager;
#endif
	};
}

#endif