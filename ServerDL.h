/*
 * ServerDL.h
 *
 * Author: Christopher Gillis
 * Created on: October 12, 2015
 *
 * Manages the frames received from the client.
 */

#ifndef __SERVERDL_H_
#define __SERVERDL_H_

#include <iostream>

#include "Frame.h"
#include "Packet.h"

class ServerDL
{
	private:
		Frame framesRecvd[100];		// All of the frames currently received
		int numFrames;				// The number of frames currently being processed

	public:
		/* Default constructor */
		ServerDL();

		/* Add a frame to the array */
		bool addFrame(char * frameStr);

		/* Remove the frame at the given index */
		bool removeFrame(int frameIndex);

		/* Build a packet from the frames being processed */
		Packet buildPacket();

		/* Build an ack frame to send to the client */
		Frame buildAck(int frame);

		/* Get num frames */
		int getNumFrames() const { return numFrames; };
};

#endif
