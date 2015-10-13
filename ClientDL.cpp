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
} // ClientDL()

// Take a packet, build frames for it, and insert them into the array
void ClientDL::toNetworkLayer(Packet pkt)
{
	char tempPayload[130];	// Holds a temporary version of the payload

	// Get a cstring version of the packet
	char temp[257];
	pkt.constructPacket(temp);

	// Get the length of the packet to see how many frames we need to make
	int pktLen = pkt.getSize() + 1;

	Frame tempFrame;	// A temporary frame before we insert it into the datalink layer

	// The number of characters put into the first packet if we require two.
	int offset = 0;

	if (pktLen >= 130)
	{
		// Get part of the packet to put into the frame
		offset = (pktLen / 2) - (pktLen % 2);
		memcpy(tempPayload, temp, offset);

		// Set the information in the frame
		tempFrame.setSeqNum(numFrames);
		tempFrame.setPayload(tempPayload);
		tempFrame.setEOP(NOT_EOP);

		tempFrame.setSize(5 + offset);
		// Start monitoring the frame
		addFrame(tempFrame);
	}

	// Get part of the packet to put into the frame
	memcpy(tempPayload, temp + offset, (pktLen - offset));

	// Set the information in the frame
	tempFrame.setSeqNum(numFrames);
	tempFrame.setPayload(tempPayload);
	tempFrame.setEOP(IS_EOP);

	tempFrame.setSize(5 + (pktLen - offset));

	// Start monitoring the frame
	addFrame(tempFrame);
} // toNetworklayer(Packet)

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

// Getter for a frame
Frame ClientDL::getFrame(int index) const
{
	return frames[index];
}

// Getter for numFrames
int ClientDL::getNumFrames() const
{
	return numFrames;
}
