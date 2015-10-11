/*
 * ClientDL.h
 *
 * Author: Christopher Gillis
 * Created on: October 10, 2015
 *
 * Manages all of the frames sent by a client to the server and their respective
 * timers.
 */

#ifndef __CLIENTDL_H_
#define __CLIENTDL_H_

#include "Frame.h"
#include "Timer.h"

class ClientDL
{
	private:
		Frame frames[100];		// All of the frames currently sent
		Timer timers[100];		// All of the timers for the respective frames
		int numFrames;			// The number of frames currently being monitored

	public:
		/* Default constructor */
		ClientDL();

		/* Add a frame to monitor */
		bool addFrame(Frame new_frame);

		/* Remove a frame to monitor */
		bool removeFrame(int frameIndex);

		/* Check the timer for a frame */
		long int checkFrameTimer(int frameIndex);

		/* Check and reset the timer for a frame */
		long int startFrameTimer(int frameIndex);
};

#endif
