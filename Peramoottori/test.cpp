void android_main(android_app* application)
{


	Application* app = Application::GetInstance(); // For ease of use.
	app->Initialize(application); // Contains loop which makes sure to initialize OpenGL and all modules.

	if (GameClass::first == false) // Initialize our game class only once.
	{
		GameClass* game = NEW GameClass;
		app->saveData = (void*)game; // Application holds reference into our game for later use.
		GameClass::first = true;
	}

	while (app->Update()) // Start updating engine.
	{
		GameClass* access = (GameClass*)app->saveData; // Use the game class we created earlier.

		if (app->IsFocused()) // User is currently using our application.
		{
			if (access->paused == true) // If we were previously paused, unpause the application.
				access->Unpause();

			access->Update(); // Update game normally.
			app->window.Clear(); // Clear application screen.
			app->Draw(); // Draw current state of game.
		}
		else // Application has been sent to background.. 
		{
			if (access->paused == false)
				access->Pause(); // ..so lets pause our game.

			std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Prevent logcat from being cluttered.
			DEBUG_INFO(("Game is not focused."));
		}
	}
}