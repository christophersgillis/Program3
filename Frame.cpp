/*
 * Frame.cpp
 *
 * Author: Christopher Gillis
 * Created on: October 3, 2015
 */

#include "Frame.h"

/* Default constructor */
Frame::Frame()
{
	eop = NOT_EOP;		// An initialized frame does not contain the end of a packet
	seqNum = 0;			// The sequence number will be 0 for now.
	strcpy(payload, "");// Set the payload to an empty string
	calcErrorDetect(ed);// Calculate the error detection bytes
	size = 0;
} // Frame()

/* Constructor with information */
Frame::Frame(int init_seqNum, char * init_payload, char init_eop)
{
	size = 0;

	// Fill in values from arguments
	/* Ensure the sequence number is only 2 characters long */
	if (init_seqNum > 99 || init_seqNum < 0)
		seqNum = 0;		// If an invalid number is passed set to 0
	else
		seqNum = init_seqNum;			

	/* Ensure the payload is no more than 130 characters */
	memcpy(payload, init_payload, 130);

	// Terminate the string
	if (strlen(init_payload) < 130)
	{
		payload[strlen(init_payload)] = '\0';
	}
	else
		payload[129] = '\0';

	/* Ensure the end-of-packet variable is a valid entry */
	if (init_eop != NOT_EOP && init_eop != IS_EOP)
		eop = IS_EOP;	// If an invalid entry is passed, assume its the end of a packet
	else
		eop = init_eop;

	// Calculate the error detection bytes
	calcErrorDetect(ed);
} // Frame(int, char *, char)

/*
 * Build a cstring by placing the information in this frame in a sequential
 * order: [SEQ_NUM][EOP][PAYLOAD][ERROR_DETECT]
 */
void Frame::constructFrame(char * frame_str)
{
	/* Create the final string to send to the server */
	sprintf(frame_str, "%2d%c%s%c%c",
							seqNum,
							eop,
							payload,
							ed[0],
							ed[1]);
} // constructFrame(char *)

/* Build a frame by pulling information out of a formatted cstring */
void Frame::deconstructFrame(char * frame_str, int frmSize)
{
	/* String format: [SEQ_NUM][EOP][PAYLOAD][ED] */

	if (frmSize == 0)
		return;

	/* Get the sequence number from the string */
	char seq_str[2];
	seq_str[0] = frame_str[0];
	seq_str[1] = frame_str[1];
	seqNum = atoi(seq_str);

	/* Get the end-of-packet character */
	eop = frame_str[2];

	/* Get the error detection bytes */
	ed[0] = frame_str[frmSize - 2];
	ed[1] = frame_str[frmSize - 1];

	/* Lastly, get the payload from the leftover bytes */
	// Subtract 5 from the length because of the other information in the string
	int payloadSize = frmSize - 5;	
	memcpy(payload, frame_str + 3, payloadSize);

	size = frmSize;
} // deconstructFrame(char *)

void Frame::calcErrorDetect(char * new_ed)
{
	/* Use XOR folding to get the error detection bits */
	char frameToken[2];		// Holds 2 bytes of the frame at a time
	// Make sure the seqNum is 2 bytes long
	sprintf(frameToken, "%2d", seqNum);

	// Initialize the errorDetect to the seqNum
	memcpy(new_ed, frameToken, 2);
/*
	// Check the length of our payload so far
	int payloadLen = strlen(payload);

	if (size > 4)
		payloadLen = size - 5;

	// Add one for the eop byte
	payloadLen++;

	// If we don't have a payload, just XOR the eop byte and an extra byte
	if (payloadLen == 1)
	{
		frameToken[0] = eop;
		frameToken[1] = ' ';

		new_ed[0] ^= frameToken[0];
		new_ed[1] ^= frameToken[1];
	}
	// If we have an odd number of bytes, loop through the payload with an extra byte
	else if (payloadLen % 2 == 1)
	{
		frameToken[0] = eop;
		frameToken[1] = ' ';
		
		new_ed[0] ^= frameToken[0];
		new_ed[1] ^= frameToken[1];

		int i;
		for (i = 0; i < payloadLen - 1; i += 2)
		{
			frameToken[0] = payload[i];
			frameToken[1] = payload[i + 1];

			new_ed[0] ^= frameToken[0];
			new_ed[1] ^= frameToken[1];
		}
	}
	// If we have an even number of bytes, use the eop and the first byte of the payload
	else
	{
		frameToken[0] = eop;
		frameToken[1] = payload[0];

		new_ed[0] ^= frameToken[0];
		new_ed[1] ^= frameToken[1];

		// Loop through the payload starting on the second character
		int i;
		for (i = 1; i < payloadLen - 1; i += 2)
		{
			frameToken[0] = payload[i];
			frameToken[1] = payload[i + 1];

			new_ed[0] ^= frameToken[0];
			new_ed[1] ^= frameToken[1];
		}
	}
*/
} // calcErrorDetect()

/* Getters/Setters */
// Sequence number
void Frame::setSeqNum(int new_seqNum)
{
	/* Make sure the sequence number is only 2 bytes long */
	if (new_seqNum > 99 || new_seqNum < 0)
		seqNum = 0;
	else
		seqNum = new_seqNum;
}
int Frame::getSeqNum() const
{
	return seqNum;
}

// Payload
void Frame::setPayload(char * new_payload)
{
	/* Make sure the payload is at most 130 characters */
	memcpy(payload, new_payload, 130);
}
char * Frame::getPayload()
{
	return payload;
}

// EOP
void Frame::setEOP(char new_eop)
{
	/* Make sure the EOP is one of two characters */
	if (new_eop != NOT_EOP && new_eop != IS_EOP)
		eop = IS_EOP;
	else
		eop = new_eop;

	calcErrorDetect(ed);
}
char Frame::getEOP() const
{
	return eop;
}

// Error Detection
/* No setter for error detection */
char * Frame::getEd()
{
	return ed;
}
