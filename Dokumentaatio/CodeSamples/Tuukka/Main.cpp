//#define PLATFORM_WIN32
#define PLATFORM_ANDROID

#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <lodepng.h>


#if defined(PLATFORM_ANDROID) // Android alustalle spesifiset includet ja funktiot.
	#include <android/log.h>
	#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "NativeInfo", __VA_ARGS__)
	#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, "NativeWarn", __VA_ARGS__)

	#include <jni.h>
	#include <errno.h>

	#include <EGL/egl.h>
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>

	#include <android/asset_manager.h>
	#include <android/input.h>
	#include <android_native_app_glue.h>

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

	static int ProcessInput(struct android_app* application, AInputEvent* inputEvent);
	static void ProcessCommand(struct android_app* application, int command);
	static bool ObjectReader(std::string fileName, Engine* engine, std::vector<GLfloat> &vertexData, std::vector<GLint> &vertexIndex, std::vector<GLint> &textureIndex);



#elif defined(PLATFORM_WIN32) // Windows alustalle spesifiset includet ja funktiot.
	#define GLEW_STATIC
	#define WIN32_LEAN_AND_MEAN
	#define _CRT_SECURE_NO_WARNINGS
	#include <fstream>
	#include <windows.h>
	#include <tchar.h>
	#include "glew.h"

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	struct Engine
	{
		HWND	windowHandle; // Holds window handle.
		HDC		deviceContext; // Private GDI device context.
		HGLRC	renderingContext; // OpenGL rendering context.
		MSG		messages;

		int shaderProgram	= 0; // K‰ytett‰v‰ shader-ohjelma.
		int width			= 0; // Ikkunan koko.
		int height			= 0;
		float x				= 0; // Viimeisin k‰ytt‰j‰n painallus.
		float y				= 0;
	};
#endif


// Kummallakin alustalla toimivat funktiot.
static void Initialize(Engine* engine, struct android_app* application); // Alustetaan ohjelmaa platformin mukaan.
static int InitDisplay(Engine* engine); // Alustetaan laitteen ikkuna.
static void KillDisplay(Engine* engine); // Tuhotaan laitteen ikkuna.
static char* FileReader(std::string fileName, Engine* engine); // Palauttaa tiedoston tekstin char-pointterina. Tiedoston pit‰‰ olla assets-kansiossa.
static void CreateShaders(Engine* engine); // Luodaan shaderit.



void android_main(struct android_app* application)
{
	struct Engine engine; // Monitoroi applikaation tilaa.
	memset(&engine, 0, sizeof(engine));

	Initialize(&engine, application); // Alustetaan platformin mukaan.
	glViewport(0, 0, engine.width, engine.height);

	CreateShaders(&engine); // Luodaan ohjelman shaderit.
	glUseProgram(engine.shaderProgram);
	glUseProgram(0);

	float color = 0.0f;


#if defined(PLATFORM_WIN32) // Todistetaan ett‰ kontekstin luonti windowsille toimii myˆs.
	while(engine.messages.message != WM_QUIT)
	{
		while(PeekMessage(&engine.messages, NULL, 0, 0, PM_REMOVE)) // Ikkuna ottaa vastaan viestej‰.
		{
			TranslateMessage(&engine.messages);
			DispatchMessage(&engine.messages);
		}

		color += 0.01f;
		if (color > 1.0f)
			color = 0.0f;
		glClearColor(1.0f, color, color, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		SwapBuffers(engine.deviceContext);

		// T‰h‰n tulisi peli-logiikka.
		// Pelk‰n kontekstin luonnin pit‰isi toimia t‰ll‰.
	}


#elif defined(PLATFORM_ANDROID)
	struct android_poll_source* eventSource;
	bool contextCheck		= true;
	std::vector<GLfloat>	CUBE_VERTEX; // Vektorit tulevat sis‰lt‰m‰‰n ladatun objektin verteksit ja indeksit.
	std::vector<GLint>		CUBE_INDEX;
	std::vector<GLint>		TEXTURE_INDEX;
	GLuint vertexBuffer		= 0; // Buffer lokaatio.
	GLuint positionHandle	= 0; // Atribuutti lokaatioita.
	GLuint textureHandle	= 0;

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

		if (engine.display != EGL_NO_DISPLAY)
		{
			if (contextCheck) // Alustetaan asioita vasta kun konteksti on luotu.
			{
				// Etsit‰‰n shader attribuutit.
				GLuint positionHandle = glGetAttribLocation(engine.shaderProgram, "attrPosition");
				if(positionHandle < 0)
					LOGW("attrPosition ei lˆytynyt.");

				GLuint textureHandle = glGetAttribLocation(engine.shaderProgram, "textPosition");
				if(textureHandle < 0)
					LOGW("textPosition ei lˆytynyt.");

				// Ladataan objektille tekstuuri.
				std::vector<unsigned char> image;
				unsigned width, height;
				lodepng::decode(image, width, height, "texture.png");
				GLuint textureID;

				glGenTextures(1, &textureID);
				glBindTexture(GL_TEXTURE_2D, textureID);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
							 width,
							 height,
							 0, GL_RGBA, GL_UNSIGNED_BYTE,
							 image.data());

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

				// Asetetaan objektin arvot aikaisemmin luotuihin vektoreihin.
				ObjectReader("cube.obj", &engine, CUBE_VERTEX, CUBE_INDEX, TEXTURE_INDEX);

				glGenBuffers(1, &vertexBuffer);
				glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
				glBufferData(GL_ARRAY_BUFFER, CUBE_VERTEX.size() * sizeof(GLfloat), &CUBE_VERTEX[0], GL_STATIC_DRAW);

				LOGI("Aloitetaan main-loop.");
				contextCheck = false;
			}

			color += 0.01f;
			if (color > 1.0f)
				color = 0.0f;
			glClearColor(color, color, color, 1.0f);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			glUseProgram(engine.shaderProgram);

			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glVertexAttribPointer(positionHandle, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), &CUBE_VERTEX[0]);
			glVertexAttribPointer(textureHandle, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), &CUBE_VERTEX[3]);

			glDrawElements(GL_TRIANGLES, CUBE_INDEX.size(), GL_UNSIGNED_INT, &CUBE_INDEX[0]);

			glUseProgram(0);
			eglSwapBuffers(engine.display, engine.surface);
		}
	}
#endif
}

static void CreateShaders(Engine* engine)
{
	// Shaderien ja programin tarkistaminen ei vaan toimi.
	GLuint program = glCreateProgram();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	char* vertexSource = FileReader("vertex.txt", engine);
	glShaderSource(vertexShader, 1, (const char**)&vertexSource, NULL);
	glCompileShader(vertexShader);

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	char* fragmentSource = FileReader("fragment.txt", engine);
	glShaderSource(fragmentShader, 1, (const char**)&fragmentSource, NULL);
	glCompileShader(fragmentShader);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	engine->shaderProgram = program;
}



#if defined(PLATFORM_ANDROID)
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
		LOGI("InitDisplay begin.");
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

	static int ProcessInput(struct android_app* application, AInputEvent* inputEvent)
	{
		Engine* engine = (struct Engine*)application->userData;

		if(AInputEvent_getType(inputEvent) == AINPUT_EVENT_TYPE_MOTION)
		{
			engine->x = AMotionEvent_getX(inputEvent, 0);
			engine->y = AMotionEvent_getY(inputEvent, 0);
			LOGI("KOSKETUS @ (%f, %f)", engine->x, engine->y);
			return 1;
		}

		return 0;
	}

	static void ProcessCommand(struct android_app* application, int command)
	{
		Engine* engine = (struct Engine*)application->userData; // Konversio void-pointterista.

		switch(command)
		{
		case APP_CMD_INIT_WINDOW:
			LOGI("Luodaan ikkuna.");
			InitDisplay(engine);
			break;

		case APP_CMD_TERM_WINDOW:
			LOGI("Tuhotaan ikkuna.");
			KillDisplay(engine);
			break;

		case APP_CMD_PAUSE:
			LOGI("Pause.");
			break;

		case APP_CMD_RESUME:
			LOGI("Resume.");
			break;

		default:
			break;
		}
	}

	static bool ObjectReader(std::string fileName, Engine* engine, std::vector<GLfloat> &vertexData, std::vector<GLint> &vertexIndex, std::vector<GLint> &textureIndex)
	{
		// Tanenilta apua.
		AAssetManager* assetManager = engine->app->activity->assetManager;
		AAsset* asset = AAssetManager_open(assetManager, fileName.c_str(), AASSET_MODE_UNKNOWN);

		if(!asset)
		{
			LOGW("Objektin %s lukeminen ei onnistunut.", fileName.c_str());
			return false;
		}
		else
		{
			size_t size = AAsset_getLength(asset);
			char* buffer = (char*)malloc(sizeof(char)*size + 1);
			AAsset_read(asset, buffer, size);
			buffer[size] = '\0';
			LOGI("Luettu tiedosto %s (%d).", fileName.c_str(), size);
			LOGI("%s", buffer);

			std::string fileContent(buffer, size); // Tehd‰‰n muokkaaminen stringiss‰ - helpompaa.
			delete[] buffer;
			AAsset_close(asset);

			std::vector<std::string> coordinates;
			std::vector<GLfloat> tempVertex;
			std::vector<unsigned int> tempIndex;
			size_t position = 0, nextPosition = 0;
			int vertexCount = 0, textureCount = 0, indexCount = 0;

			while(nextPosition != std::string::npos) // Greatest possible value for an element of type size_t.
			{
				nextPosition = fileContent.find('\n', position); // Searches the string for the first occurrence of the sequence specified by its arguments.
				if(nextPosition != std::string::npos)
				{
					coordinates.push_back(fileContent.substr(position, nextPosition - position));
					position = nextPosition + 1;
				}
			}

			for(int i = 0; i < coordinates.size(); i++) // Lasketaan verteksien ja indeksien m‰‰r‰.
			{
				if((coordinates[i])[0] == '#')
					continue;
				else if((coordinates[i])[0] == 'v' && (coordinates[i])[1] == ' ')
					vertexCount++;
				else if((coordinates[i])[0] == 'v' && (coordinates[i])[1] == 't')
					textureCount++;
				else if((coordinates[i])[0] == 'f')
					indexCount++;
			}

			if(vertexCount == 0 || textureCount == 0 || indexCount == 0)
			{
				LOGW("Objekti %s on viallinen.", fileName.c_str());
				return false;
			}

			if(vertexCount < textureCount) // Varataan tarpeeksi tilaa objekti vektoreille.
				vertexData.reserve(textureCount * 6);
			else
				vertexData.reserve(vertexCount * 6);

			vertexIndex.reserve(indexCount * 3);
			textureIndex.reserve(indexCount * 3);

			for(int i = 0; i < vertexData.capacity(); i++) // Capacity on unsigned int.
				vertexData.push_back(0.0f); // Alustetaan vertexData vektori.

			int vertexJump = 0, textureJump = 0; // K‰ytet‰‰n laittamaan koordinaatit oikeaan paikkaan vektorissa.

			for(int i = 0; i < coordinates.size(); i++)
			{
				if((coordinates[i])[0] == '#') // Ignoretaan kommentit.
					continue;

				else if((coordinates[i])[0] == 'v' && (coordinates[i])[1] == ' ') // Vertexit.
				{
					float x, y, z; // V‰liaikaisesti otetaan koordinaatit ylˆs.
					sscanf(coordinates[i].c_str(), "v  %f %f %f", &x, &y, &z);
					vertexData[0 + vertexJump] = x;
					vertexData[1 + vertexJump] = y;
					vertexData[2 + vertexJump] = z;
					vertexJump += 6;
				}

				else if((coordinates[i])[0] == 'v' && (coordinates[i])[1] == 't') // Tekstuuri koordinaatit.
				{
					float x, y, z;
					sscanf(coordinates[i].c_str(), "vt  %f %f %f", &x, &y, &z);
					vertexData[3 + textureJump] = x;
					vertexData[4 + textureJump] = y;
					vertexData[5 + textureJump] = z;
					textureJump += 6;
				}

				else if((coordinates[i])[0] == 'f') // Indeksit.
				{
					// Obj-tiedostossa indeksit ovat muodossa f 5/2 8/3 2/4 .
					// Eli vertex koordinaatti olisi 5/8/2 ja tekstuurin 2/3/4. Indeksit alkavat myˆs ykkˆsest‰ nollan sijaan.
					unsigned int vx, vy, vz, tx, ty, tz;
					sscanf(coordinates[i].c_str(), "f %d/%d %d/%d %d/%d ", &vx, &tx, &vy, &ty, &vz, &tz);
					vertexIndex.push_back(vx - 1);
					vertexIndex.push_back(vy - 1);
					vertexIndex.push_back(vz - 1);
					textureIndex.push_back(tx - 1);
					textureIndex.push_back(ty - 1);
					textureIndex.push_back(tz - 1);
				}
			}

			LOGI("Objekti %s luettu onnistuneesti.", fileName.c_str());
			return true;
		}
	}



#elif defined(PLATFORM_WIN32)
	static void Initialize(Engine* engine, struct android_app* application)
	{
		InitDisplay(engine);
		std::cout << "Windows alusta alustettu." << std::endl;
	}

	static int InitDisplay(Engine* engine)
	{
		wchar_t*	className = L"Win";
		wchar_t*	windowName = L"Window";
		DWORD		style = WS_OVERLAPPEDWINDOW;
		RECT		clientArea;
		HWND		windowHandle; // Holds window handle.
		HDC			deviceContext; // Private GDI device context.
		WNDCLASSEX	win;

		HGLRC					renderingContext; // OpenGL rendering context.
		PIXELFORMATDESCRIPTOR	winPixel; // Describes the pixel format of a drawing surface.
		int						pixelFormat;
		
		clientArea.left		= 0;
		clientArea.top		= 0;
		clientArea.right	= 500;
		clientArea.bottom	= 500;
		AdjustWindowRectEx(&clientArea, style, FALSE, 0);

		win.lpfnWndProc		= WndProc;
		win.cbSize			= sizeof(WNDCLASSEX);
		win.style			= CS_OWNDC;
		win.hInstance		= GetModuleHandle(nullptr); // Jos tulee onglemia HINSTANCE pit‰‰ saada mainin kautta.
		win.hbrBackground	= CreateSolidBrush(RGB(0, 0, 0));
		win.lpszClassName	= className;
		win.cbClsExtra		= NULL;
		win.cbWndExtra		= NULL;
		win.hIcon			= NULL;
		win.hCursor			= NULL;
		win.lpszMenuName	= NULL;
		win.hIconSm			= NULL;

		if(!RegisterClassEx(&win))
		{
			std::cout << "RegisterClassEx ei onnistunut." << std::endl;
			return -1;
		}

		windowHandle = CreateWindowEx(
			NULL,
			className,
			windowName,
			style,
			0,
			0,
			clientArea.right - clientArea.left,
			clientArea.bottom - clientArea.top,
			NULL,
			NULL,
			win.hInstance,
			NULL);

		if(!windowHandle)
		{
			std::cout << "WindowHandle luominen ei onnistunut." << std::endl;
			return -1;
		}

		deviceContext			= GetDC(windowHandle);
		engine->deviceContext	= deviceContext;
		engine->windowHandle		= windowHandle;
		engine->width			= clientArea.right;
		engine->height			= clientArea.bottom;

		winPixel.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
		winPixel.nVersion	= 1;
		winPixel.dwFlags	= PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | LPD_SUPPORT_OPENGL;
		winPixel.iPixelType = PFD_TYPE_RGBA;
		winPixel.cColorBits = 24;
		winPixel.cDepthBits = 24;

		pixelFormat = ChoosePixelFormat(deviceContext, &winPixel); // Etsit‰‰n l‰hin pixeliformaatti jota voidaan k‰ytt‰‰.
		if(!SetPixelFormat(deviceContext, pixelFormat, &winPixel))
		{
			std::cout << "PixelFormaatin luominen ei onnistunut." << std::endl;
			return -1;
		}

		renderingContext = wglCreateContext(deviceContext); // Luodaan handle OpenGL renderˆinti‰ varten.
		wglMakeCurrent(deviceContext, renderingContext); // K‰ytet‰‰n t‰t‰ ikkunaa komentokutsuissa.
		engine->renderingContext = renderingContext;

		GLenum error = glewInit(); // Alustetaan Glew.
		if(error != GLEW_OK)
		{
			std::cout << "Glewin alustaminen ei onnistunut: " << glewGetErrorString(error) << std::endl;
			return -1;
		}

		if(!GLEW_VERSION_2_1) // Tarkastetaan onko 2.1 k‰ytˆss‰.
		{
			std::cout << "OpenGL 2.1 ei tueta t‰ll‰ laitteella." << std::endl;
			return -1;
		}

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		ShowWindow(windowHandle, SW_SHOWNORMAL);
		std::cout << "Windows-ikkunan luonti onnistui." << std::endl;
		return 0;
	}

	static void KillDisplay(Engine* engine)
	{
		wglDeleteContext(engine->renderingContext);
		engine->windowHandle = NULL;
		engine->deviceContext = NULL;
		engine->renderingContext = NULL;
		std::cout << "Ikkuna tapettu." << std::endl;
	}

	char* FileReader(std::string fileName, Engine* engine)
	{
		// Engine‰ ei oikeastaan tarvita windows-versiossa. Voisi periaatteessa sis‰lt‰‰ vaikka asset-kansion sijainnin?
		std::string fullPath = "../assets/" + fileName; // Filujen t‰ytyy olla assets-kansiossa.
		std::ifstream readFile(fullPath, std::ios::in); // Avataan luettava tiedosto ja tarkistetaan onnistuminen.
		if(!readFile.is_open())
		{
			std::cout << "Tiedoston " << fileName << " avaaminen ei onnistunut." << std::endl;
			return NULL;
		}

		// Selvitet‰‰n luettavan tiedoston pituus.
		readFile.seekg(0, readFile.end); // Pistet‰‰n char positio filun loppuun.
		int fileLength = (int)readFile.tellg(); // Pistet‰‰n pituus ylˆs.
		readFile.seekg(0, readFile.beg); // Positio takasin alkuun.

		if(fileLength == 0)
		{
			std::cout << "Tiedoston " << fileName << " pituus on nolla." << std::endl;
			return NULL;
		}

		// Kopioidaan tiedoston sis‰ltˆ stringiin.
		std::string fileContents((std::istreambuf_iterator<char>(readFile)), std::istreambuf_iterator<char>());
		char *tempChar = new char[fileContents.length() + 1];
		std::strcpy(tempChar, fileContents.c_str()); // Kopioidaan tiedoston sis‰llˆt dynaamisesti luotuun char-merkkijonoon.

		std::cout << std::endl << "Avattiin tiedosto " << fileName << " (" << fileLength << "): \n" << tempChar << std::endl;

		readFile.close();
		return tempChar;
	}

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // Application-defined function that processes messages sent to a window.
	{
		switch(message)
		{
		case WM_CLOSE: // Sent as a signal that a window or an application should terminate.
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY: // Sent when a window is being destroyed.
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
		return 0;
	}
#endif