/// The core Application system.
/**
	Handles most of the communication with java side.
*/
class Application
{

public:
	/// Struct that holds information and can be stored on java side.
	struct Engine {
		struct android_app* app;
		struct saved_state state;

		AAssetManager* assetManager;

		EGLDisplay display;
		EGLSurface surface;
		EGLContext context;

		int width;
		int height;
	}
	/// Struct that holds saved states within Engine struct
	struct saved_state{
		float x;
		float y;
	};

	/// Default Constructor.
	void application();

	/// Initializing the Application.
	/**
		\param application takes in the android_app
	*/
	static void init(android_app* application);

	/// The core update loop.
	/**
		TODO
	*/
	static void update();

private:
	/// Processes command events.
	/**
		\param command the command event number
	*/
	static void processCommand(int command);

	/// Called when APP_CMD_TERM_WINDOW is received by processCommand.
	/**
	*/
	static void terminateDisplay();

	/// Called when APP_CMD_INIT_WINDOW is received by processCommand.
	/**
	*/
	static int initializeDisplay();

	/// Given to android_app for handling input.
	/**
		\return Returns 0 on success, -1 if failed.
	*/
	static int handleInput(AInputEvent* event);

	/// Handles swapping buffers if the display is initialized.
	/**
		\param event input event received on java side
		\return Returns 1 if input is received, 0 if not.
	*/
	static void drawFrame();

	struct Engine engine;

};