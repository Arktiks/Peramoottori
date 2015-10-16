#ifndef APPLICATION_H
#define APPLICATION_H

#include <core/WindowHandler.h>
#include <android_native_app_glue.h>

namespace pm
{
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

	private:

		/// Print warning messages if trying to use Application without initializing.
		bool Warning(std::string function);

		/// Default constructor.
		/// Initialize needs to be called for Application to work properly.
		Application() : application(nullptr) {}; 

		/// Private destructor prevents delete.
		/// Class needs to be cleaned up with DestroyInstance.
		~Application() {};

		android_app* application; ///< Pointer to android application.

		static Application* instance; ///< Pointer to only instance of the class.
	};
}

#endif