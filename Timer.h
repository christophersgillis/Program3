/*
 * Timer.h
 *
 * Author: Christopher Gillis
 * Created on: October 10, 2015
 *
 * Handles keeping track of the timeouts for the frames managed by the 
 * simulated datalink layer.
 */

#ifndef __TIMER_H_
#define __TIMER_H_

#include <time.h>	// for struct timespec and clock_gettime()

class Timer
{
	private:
		struct timespec prev_ts;	// Stores the last time since the timer was checked

	public:
		/* Default constructor */
		Timer();

		/* Return time in milliseconds since startTimer() was last called */
		long int startTimer();

		/* Return time in milliseconds since startTimer was last called
 		 * Does not reset timer 
		 */
		long int checkTimer() const;
};	// Timer

#endif
