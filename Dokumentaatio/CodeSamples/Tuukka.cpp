#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "NativeInfo", __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, "NativeWarn", __VA_ARGS__)

struct Engine // Sis‰lt‰‰ app-tilasta tietoa.
{
	struct android_app* app	= NULL; // Windowhandlen saa t‰t‰ kautta.
	EGLDisplay display		= EGL_NO_DISPLAY; // Wrapper-classeja android k‰yttˆˆn.
	EGLSurface surface		= EGL_NO_SURFACE;
	EGLContext context		= EGL_NO_CONTEXT;

	int shaderProgram	= 0; // K‰ytett‰v‰ shader-ohjelma.
	int width			= 0; // Ikkunan koko.
	int height			= 0;
	float x				= 0; // Viimeisin k‰ytt‰j‰n painallus.
	float y				= 0;
};


// Prosessoidaan painalluksia ja pistet‰‰n ne muistiin engineen.
static int ProcessInput(struct android_app* application, AInputEvent* inputEvent);

// Alustetaan androidia + engine struct.
static void Initialize(Engine* engine, struct android_app* application); 

// Alustetaan laitteen ikkuna.
static int InitDisplay(Engine* engine);

// Tuhotaan laitteen ikkuna.
static void KillDisplay(Engine* engine);

// Palauttaa tiedoston tekstin char-pointterina. Tiedoston pit‰‰ olla assets-kansiossa.
static char* FileReader(std::string fileName, Engine* engine);


void android_main(struct android_app* application)
{
	struct Engine engine; // Monitoroi applikaation tilaa.
	memset(&engine, 0, sizeof(engine));
	Initialize(&engine, application); // Alustetaan platformin mukaan.
	glViewport(0, 0, engine.width, engine.height);

	struct android_poll_source* eventSource;
	while(true)
	{
		while(ALooper_pollAll(0, nullptr, nullptr, reinterpret_cast<void**>(&eventSource)) >= 0)
		{
			if(eventSource != nullptr)
				eventSource->process(application, eventSource);

			if(application->destroyRequested != 0)
			{
				KillDisplay(&engine);
				return;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		eglSwapBuffers(engine.display, engine.surface);

	}
}

static void Initialize(Engine* engine, struct android_app* application)
{
	app_dummy();
	application->userData = engine; // The application can place a pointer to its own state object.
	application->onAppCmd = ProcessCommand;
	application->onInputEvent = ProcessInput;
	engine->app = application;
	LOGI("Android alusta alustettu.");
}

static int InitDisplay(Engine* engine)
{
	LOGI("InitDisplay alkaa.");
	const EGLint attribs[] =
	{
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_NONE
	};

	const EGLint attribList[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	EGLint		w, h, dummy;
	EGLint		numConfigs, format;
	EGLConfig	config; // EGLConfig abstraction allows cross platform portability.
	EGLSurface	surface; // Wrapper class for native EGLSurface objects.
	EGLContext	context; // Wrapper class for native EGLContext objects.
	EGLDisplay	display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	eglInitialize(display, 0, 0);
	eglChooseConfig(display, attribs, &config, 1, &numConfigs);
	eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);

	surface = eglCreateWindowSurface(display, config, engine->app->window, NULL);
	context = eglCreateContext(display, config, NULL, attribList);

	if(eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
	{
		LOGW("Ikkunan luominen ei onnistunut.");
		return -1;
	}

	eglQuerySurface(display, surface, EGL_WIDTH, &w); // Otetaan ikkunan koko muistiin.
	eglQuerySurface(display, surface, EGL_HEIGHT, &h);

	engine->display = display;
	engine->context = context;
	engine->surface = surface;
	engine->width = w;
	engine->height = h;

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

	LOGI("Ikkunan luominen onnistui.");
	return 0;
}

static void KillDisplay(Engine* engine)
{
	eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglDestroyContext(engine->display, engine->context);
	engine->context = EGL_NO_CONTEXT;

	eglDestroySurface(engine->display, engine->surface);
	engine->surface = EGL_NO_SURFACE;

	eglTerminate(engine->display);
	engine->display = EGL_NO_DISPLAY;

	LOGI("Ikkuna tapettu.");
}

char* FileReader(std::string fileName, Engine* engine)
{
	AAssetManager* assetManager = engine->app->activity->assetManager;
	AAsset* asset = AAssetManager_open(assetManager, fileName.c_str(), AASSET_MODE_UNKNOWN);
	if(asset)
	{
		size_t size = AAsset_getLength(asset);
		char* buffer = (char*)malloc(sizeof(char)*size + 1);
		AAsset_read(asset, buffer, size);
		buffer[size] = '\0';
		LOGI("Luettu tiedosto %s (%d).", fileName.c_str(), size);
		LOGI("%s", buffer);
		AAsset_close(asset);
		return buffer;
	}
	else
	{
		LOGW("Tiedoston %s lukeminen ei onnistunut.", fileName.c_str());
		return NULL;
	}
}

static void ProcessInput(struct android_app* application, AInputEvent* inputEvent)
{
	Engine* engine = (struct Engine*)application->userData;
	if(AInputEvent_getType(inputEvent) == AINPUT_EVENT_TYPE_MOTION)
	{
		engine->x = AMotionEvent_getX(inputEvent, 0);
		engine->y = AMotionEvent_getY(inputEvent, 0);
		LOGI("KOSKETUS @ (%f, %f)", engine->x, engine->y);
	}
}