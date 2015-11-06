#ifndef APPLICATION_H
#define APPLICATION_H

#include <core/WindowHandler.h>
#include <android_native_app_glue.h>

namespace pm
{
	//Defining function pointers
	typedef void(*StartFunction)();
	typedef void(*ResumeFunction)();
	typedef void(*PauseFunction)(); 
	typedef void(*StopFunction)();

	/** \brief System that handles communication with java side.
	*
	* \ingroup Core
	*/

	class Application
	{

		friend class EventHandler; // Required for static android_native_app_glue functions.
		

	public:

		/** \brief Return instance of Application. 
		*
		* Application class uses singleton pattern to make sure only one
		* instance of Application exists during runtime.
		* \return Pointer to Application.
		*/
		static Application* GetInstance();

		/** @name Restricted Public Member Functions
		*  User should not use following restricted functions unless he is 100% confident of their purpose.
		*/
		///@{
		/**
		* \brief Delete pm::Application and all created resources.
		*
		* Deleting application is already part of cleaning routine when application is shut down permanently.
		* As such user will no need to call this unless for very specific reason.
		*/
		void DestroyInstance();
		///@}

		/** \brief Initialize Peramoottori and all modules.
		*
		*	Should be first function called when creating application.
		*	\param application pointer to android_application struct.
		*/
		void Initialize(android_app* application);

		/** \brief Core update loop that polls android events and inputs.
		*
		* Recommended to be nested with while-statement.
		* \return false if our main loop is put on halt.
		*/
		bool Update(); 

		/** \brief Draw stored in SpriteBatch.
		*
		* Calls for SpriteBatch::Draw() and swaps frame buffers.
		*/
		void Draw();

		/** \brief Check if Application is done initializing.
		* 
		* When initializing the application it will take some time to get device context
		* up and running.
		* \return true if Application is ready to be updated and drawn.
		*/
		bool IsReady();

		/** \brief Check if our program is currently being used.
		*
		* Useful when you want to make sure our program has priority over other apps.
		* \return true if Application is currently focused.
		*/
		bool IsFocused();

		/// Loops infinitely until Application is ready to be updated and drawn.
		void Wait();

		WindowHandler window; ///< Handles display of android device.

		/** \brief Pointer to hold saved data.
		*
		* User can assign their game state as void-pointer.
		*/
		void* saveData;



		// function pointer setup

		/** \brief User generated pause function setter
		*
		* Users can create their own start fuctions in main and pass it as a pointer to the engine.
		*/
		void setStartFunction(void(*StartFunction)()) { startFunction = StartFunction; };

		/** \brief User generated pause function getter
		*
		* Start function getter
		*/
		StartFunction getStartFunction() { return startFunction; };

		/** \brief User generated pause function setter
		*
		* Users can create their own resume fuctions in main and pass it as a pointer to the engine.
		*/
		void setResumeFunction(void(*ResumeFunction)()) { resumeFunction = ResumeFunction; };

		/** \brief User generated pause function getter
		*
		* Resume function getter
		*/
		ResumeFunction getResumeFunction() { return resumeFunction; };

		/** \brief User generated pause function setter
		*
		* Users can create their own pause fuctions in main and pass it as a pointer to the engine.
		*/
		void setPauseFunction(void(*PauseFunction)()) { pauseFunction = PauseFunction; };

		/** \brief User generated pause function getter
		*
		* Pause function getter
		*/
		PauseFunction getPauseFunction() { return pauseFunction; };

		/** \brief User generated pause function setter
		*
		* Users can create their own stop fuctions in main and pass it as a pointer to the engine.
		*/
		void setStopFunction(void(*StopFunction)()) { stopFunction = StopFunction; };

		/** \brief User generated pause function getter
		*
		* Stop function getter
		*/
		StopFunction getStopFunction() { return stopFunction; };



	private:

		/// Print warning messages if trying to use Application without initializing.
		bool Warning(std::string function);

		/// Default constructor.
		/// Initialize needs to be called for Application to work properly.
		Application() : application(nullptr) {}; 

		/// Private destructor prevents delete.
		/// Class needs to be cleaned up with DestroyInstance.
		~Application() {};

		StartFunction startFunction;
		ResumeFunction resumeFunction;
		PauseFunction pauseFunction;
		StopFunction stopFunction;

		android_app* application; ///< Pointer to android application.

		static Application* instance; ///< Pointer to only instance of the class.
	};
}

#endif