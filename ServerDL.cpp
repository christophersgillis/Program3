/*
 * ServerDL.cpp
 *
 * Author: Christopher Gillis
 * Created on: October 12, 2015
 */

#include "ServerDL.h"

/* Default constructor */
ServerDL::ServerDL()
{
	numFrames = 0;
}

/* Add a frame to the array. Return false if array is full */
bool ServerDL::addFrame(char * frameStr)
{
	if (numFrames >= 100)
		return false;

	Frame new_frame;

	new_frame.deconstructFrame(frameStr);

	/* Check the error detection bytes */
	char ed[2];
	new_frame.calcErrorDetect(ed);
	if (strncmp(ed, new_frame.getEd(), 2) != 0)
	{
		return false;
	}

	framesRecvd[numFrames] = new_frame;

	return true;
} // addFrame(Frame)

/* Remove the frame at the given index. Return false if no frame at index or if array is empty */
bool ServerDL::removeFrame(int frame)
{
	if (numFrames <= frame || numFrames <= 0)
		return false;
	else
	{
		int i;
		for (i = frame; i < numFrames; i++)
		{
			framesRecvd[frame] = framesRecvd[frame + 1];
		}
		numFrames--;
	}
} // removeFrame(int)

/* Build a packet from the frames being processed */
Packet ServerDL::buildPacket()
{
	char payload[257];
	strcpy(payload, "");
	int seqNum = 0;

	while(1)
	{
		if (framesRecvd[0].getEOP() == IS_EOP)
		{
			if (framesRecvd[0].getSeqNum() != seqNum)
			{
				Packet junk;
				return junk;
			}

			strcat(payload, framesRecvd[0].getPayload());
			removeFrame(0);
			break;
		}
		else
		{
			strcat(payload, framesRecvd[0].getPayload());
			seqNum = framesRecvd[0].getSeqNum();
			removeFrame(0);
		}
	}

	Packet newPacket;
	newPacket.deconstructPacket(payload);

	return newPacket;
}

/* Build an ack for the indexed frame */
Frame ServerDL::buildAck(int frame)
{
	Frame ack;
	ack.setSeqNum(framesRecvd[frame].getSeqNum());
	ack.setEOP(NOT_EOP);

	return ack;
}
