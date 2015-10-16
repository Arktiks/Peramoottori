#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <android_native_app_glue.h>
#include <android/sensor.h>

namespace pm
{
	/** \brief Handles input and lifeline of application.
	*
	* Current functionality includes initializing and handling device sensors. Such as disabling and enabling
	* them depending if application is focused. 
	*
	* Readying and destroying OpenGL context and objects depending on state of application.
	*
	* Destroying application and writing memory leaks using Memory class.
	*
	* \ingroup Core
	*/

	class CommandCenter
	{

		friend class android_native_app_glue;
		friend class Application;

	private:

		/// Application handles initializing.
		static void Initialize(android_app* application);

		static void Clean(); ///< Destructor.

		/// Enable touch and accelerometer sensors.
		static void EnableSensors();

		/// Disable touch and accelerometer sensors.
		static void DisableSensors();

		/// Poll sensor events and update Input accordingly.
		static void UpdateSensors(int identity);

		static void Start(); ///< When activity is becoming visible to user.
	
		static void Resume(); ///< When activity starts interacting with user.
		
		static void Pause(); ///< Called when system is about to start resuming another activity.
	
		static void Stop(); ///< Activity is no longer visible to user.
	
		static void Destroy(); ///< Final call before activity is destroyed.
	
		static void ReadyWindow(android_app* application); ///< ANativeWindow is ready for use.
	
		static void TerminateWindow(); ///< ANativeWindow needs to be terminated.
		
		static void GainedFocus();
		
		static void LostFocus();

		// Pointer to const data does not allow modification of the data through the pointer.
		static const ASensor* accelerometerSensor; ///< Sensor that measures proper acceleration.

		// Contains sensor events in queue.
		// Returns negative value if no events are available or error has occurred
		static ASensorEventQueue* sensorEventQueue; ///< Sensor event queue.

		static android_app* android_application; ///< Reference to android application.

		static bool focus;

	protected:

		/** @name Restricted Static Protected Member Functions
		*  User should not use following restricted functions unless he is 100% confident of their purpose.
		*/
		///@{
		/** \brief Handles application input processing.
		*
		* \note Reference given to android_native_app_glue.
		*/
		static int HandleInput(android_app* application, AInputEvent* event);

		/** \brief Handles application command processing.
		*
		* \note Reference given to android_native_app_glue.
		*/
		static void ProcessCommand(android_app* application, int32_t command);
		///@}
	};
}

#endif