/*
 * Frame.h
 *
 * Author: Christopher Gillis
 * Created on: October 3, 2015
 *
 * Defines a frame that will be sent by the simulated datalink layer
 */

#ifndef __FRAME_H_
#define __FRAME_H_

#include <cstring>
#include <cstdlib>
#include <cstdio>

#define NOT_EOP 0x02	// Indicates this frame is the end of a packet
#define IS_EOP  0x03	// Indicates this frame is not the end of a packet

class Frame
{
	private:
		int seqNum;			// The sequence number of the frame
		char eop;			// The end-of-packet byte
		char ed[2];			// 2 bytes assigned to error detection
		char payload[130];	// The data to send

	public:
		/* Default constructor */
		Frame();

		/* Constructor with information */
		Frame(int init_seqNum, char * init_payload, char init_eop);

		/* Fill the passed in pointer with the information of the frame */
		void constructFrame(char * frame_str);

		/* Set the parameters of the frame from a cstring */
		void deconstructFrame(char * frame_str);

		/* Calculate the error detection bytes using XOR folding */
		void calcErrorDetect(char * new_ed);

		/* Getters/Setters */
		void setSeqNum(int new_seqNum);
		int getSeqNum() const;

		void setPayload(char * new_payload);
		char * getPayload();

		void setEOP(char new_eop);
		char getEOP() const;

		// No setter for error detection
		char * getEd();
};

#endif
