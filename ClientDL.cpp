/*
 * ClientDL.cpp
 *
 * Author: Christopher Gillis
 * Created on: October 11, 2015
 */

#include "ClientDL.h"

// Initialize the number of frames being monitored to 0.
ClientDL::ClientDL()
{
	numFrames = 0;
}

// Add a frame if there is space. Return false if the array is full
bool ClientDL::addFrame(Frame new_frame)
{
	// Make sure there is room for the frame
	if (numFrames >= 100)
		return false;
	else
	{
		frames[numFrames] = new_frame;
		numFrames++;
	}
}

// Remove a frame at the given index. Return false if no frame exists at that
// index.
bool ClientDL::removeFrame(int frameIndex)
{
	// Make sure a frame exists where we are trying to remove it.
	if (numFrames <= frameIndex || numFrames <= 0)
		return false;
	else
	{
		int i;
		for (i = frameIndex; i < numFrames; i++)
		{
			frames[frameIndex] = frames[frameIndex + 1];
			timers[frameIndex] = timers[frameIndex + 1];
		}
		numFrames--;
	}
}

// Check the timer for a frame
long int ClientDL::checkFrameTimer(int frameIndex)
{
	// Make sure a frame exists at the given index. If not, return an 
	// impossible value
	if (numFrames <= frameIndex || numFrames <= 0)
		return -1;
	else
		return timers[frameIndex].checkTimer();
}

// Check the timer for a frame and reset it
long int ClientDL::startFrameTimer(int frameIndex)
{
	// Make sure a frame exists at the given index. If not, return an 
	// impossible value
	if (numFrames <= frameIndex || numFrames <= 0)
		return -1;
	else
		return timers[frameIndex].startTimer();
}
