#ifndef TIME_H
#define TIME_H

#include <ctime>

namespace pm
{
	/** \brief Class to calculate elapsed time within your android %application.
	*
	* \ingroup Core
	*/

	class Time
	{
	public:
		enum FRACTION
		{
			SECONDS, MILLISECONDS, MICROSECONDS
		};

		/**
		* \brief Default constructor.
		*/
		Time(void){};
		/**
		* \brief Custom constructor.
		*/
		Time(std::clock_t start);
		/**
		* \brief Default destructor.
		*/
		~Time();
		/**
		* Function for restarting time.
		*/
		double Restart();
		/**
		* Function for restarting time.
		* \param[in] fraction in what format elapsed time is returned (seconds, milliseconds, microseconds).
		* \return Elapsed time as double.
		*/
		double Restart(FRACTION fraction);
		/**
		* \brief Function for starting timer.
		*/
		void Start();

		/** When called for the first time Time objects internal timer starts ticking.
		* When called second time and onward elapsed time between calls is calculated.
		* \return Elapsed time between calls in milliseconds.
		*/
		double GetElapsedTime(FRACTION time);

		/**
		* Overloaded '==' operator to compare timers.
		*/
		bool operator==(const Time rhs)
		{
			if (this->_start == rhs._start)
				return true;
			return false;
		}
	private:
		std::clock_t _start;
	};
}

#endif