#include "Application.h"
#include <core/Log.h>
#include <core/Passert.h>
#include <core/Memory.h>

#include <core/CommandCenter.h>
#include <core/Input.h>

#include <resources/ResourceManager.h>
#include <graphics/RenderSystem.h>
#include <graphics/SpriteBatch.h>

using namespace std;
using namespace pm;

Application* Application::instance = nullptr;

Application* Application::GetInstance()
{
	if(instance == nullptr) // If instance has not been initialized yet.
		instance = NEW Application;
	return instance;
}

void Application::DestroyInstance()
{
	application->userData = nullptr; // Remove reference to this class.

	ResourceManager::GetInstance()->DestroyInstance();
	CommandCenter::Clean();
	RenderSystem::GetInstance()->DestroyInstance();

	delete instance;
	instance = nullptr;
	DEBUG_INFO(("Application instance deleted."));
}

void Application::Initialize(android_app* application)
{
	DEBUG_INFO(("Starting Application initialization."));
	ASSERT_NEQUAL(application, nullptr); // Make sure application pointer is legit.
	app_dummy(); // Ensures glue code isn't stripped.
	(this->application) = application; // Save application pointer for later use.
	application->userData = static_cast<void*>(this); // Store our Application class to native glue.

	DEBUG_INFO(("Starting CommandCenter initialization."));
	CommandCenter::Initialize(application);
	application->onAppCmd = CommandCenter::ProcessCommand; // What function is referred on application calls.
	application->onInputEvent = CommandCenter::HandleInput; // What function is referred on input calls.
	DEBUG_INFO(("CommandCenter done."));

	DEBUG_INFO(("Looping until device context is done."));
	Wait();
	DEBUG_INFO(("Device context constructed."));

	DEBUG_INFO(("Initializing other Peramoottori modules."));
	ResourceManager::GetInstance()->Initialize(application->activity->assetManager); // Initialize ResourceManager with AAssetManager.
	DEBUG_INFO(("ResourceManager done."));

	RenderSystem::GetInstance()->Initialize();
	DEBUG_INFO(("RenderSystem done."));
	DEBUG_INFO(("Application has been initialized."));
}

bool Application::Update()
{
	int tempIdent = 0; // See what looper is calling.
	android_poll_source* tempEventSource = nullptr; // Contains reference to executable command.

	while((tempIdent = ALooper_pollAll(0, nullptr, nullptr, reinterpret_cast<void**>(&tempEventSource))) >= 0)
	{
		CommandCenter::UpdateSensors(tempIdent);

		if(tempEventSource != nullptr)
			tempEventSource->process(application, tempEventSource);

		if(application->destroyRequested != 0) // When application is losing focus or being destroyed.
			return false;
	}

	return true;
}

void Application::Draw()
{
	if(Warning(__func__))
		return;

	SpriteBatch::GetInstance()->Draw();
	window.SwapBuffers();
}

bool Application::IsReady()
{
	if(application != nullptr && window.HasContext()) // Application has been initialized and device context is ready.
		return true;
	else
		return false;
}

void Application::Wait()
{
	while(!IsReady()) // Could be useful in game loops when Application is resumed.
		Update();
}

bool Application::Warning(string function)
{
	if(!IsReady())
	{
		DEBUG_WARNING(("Application has not been initialized or device context is not ready - ending %s prematurely.", function.c_str()));
		return true;
	}
	else
		return false;
}