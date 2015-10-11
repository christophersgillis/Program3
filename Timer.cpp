/*
 * Timer.cpp
 *
 * Author: Christopher Gillis
 * Created on: October 11, 2015
 */

#include "Timer.h"

Timer::Timer()
{
	// Initialize the timer to the current time when it was created
	clock_gettime(CLOCK_REALTIME, &prev_ts);
}

// Return the elapsed time in milliseconds from the last time startTimer() was
// called. Resets the timer.
long int Timer::startTimer()
{
	struct timespec post_ts;

	clock_gettime(CLOCK_REALTIME, &post_ts);

	// Compute elapsed time.
	long int before_msec = prev_ts.tv_sec * 1000 + prev_ts.tv_nsec/1000000;
	long int after_msec = post_ts.tv_sec * 1000 + post_ts.tv_nsec/1000000;
	long int elapsed_time = after_msec - before_msec;

	// Reset the timer
	clock_gettime(CLOCK_REALTIME, &prev_ts);
	return elapsed_time;
} // startTimer()

// Return the elapsed time in milliseconds from the last time startTimer() was
// called. Does NOT reset the timer
long int Timer::checkTimer() const
{
	struct timespec post_ts;

	clock_gettime(CLOCK_REALTIME, &post_ts);

	// Compute elapsed time.
	long int before_msec = prev_ts.tv_sec * 1000 + prev_ts.tv_nsec/1000000;
	long int after_msec = post_ts.tv_sec * 1000 + post_ts.tv_nsec/1000000;
	long int elapsed_time = after_msec - before_msec;

	return elapsed_time;
}
