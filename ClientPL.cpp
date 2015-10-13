/*
 * ClientPL.cpp
 *
 * Author: Christopher Gillis
 * Created on: October 11, 2015
 */

#include "ClientPL.h"

// Default constructor
ClientPL::ClientPL()
{

}

/* Send a frame to the server */
void ClientPL::toPhysicalLayer(int sd, Frame frame)
{
	// Build the string to send to the server
	char frameStr[135];
	frame.constructFrame(frameStr);

	// Get the length of the newly constructed string
	int frameLen = strlen(frameStr);

	// Send the string to the server
	if (send(sd, frameStr, frameLen, 0) != frameLen)
		DieWithError("send() sent a different number of bytes than expected");
} // toPhysicalLayer(int, Frame)

/* Receive a frame from the server */
int ClientPL::fromPhysicalLayer(int sd, char * buffer, int len, int flags, int to)
{
	fd_set readset;				// The set of socket descriptors to watch
	int result;					// The return value
	int ioflag;					// To set io to non-blocking
	struct timeval timeout;		// To check for a timeout

	// Initialize the set
	FD_ZERO(&readset);
	FD_SET(sd, &readset);

	// Initialize the timeout struct
	timeout.tv_sec = 0;
	timeout.tv_usec = to * 1000;
	result = select(sd + 1, &readset, NULL, NULL, &timeout);

	// Check for any errors
	if (result < 0)
		return -1;
	// Otherwise recv() until we either get information or timeout
	else if (result > 0 && FD_ISSET(sd, &readset))
	{
		// Set non-blocking mode
		if ((ioflag = fcntl(sd, F_GETFL, 0)) != -1)
			fcntl(sd, F_SETFL, ioflag | O_NONBLOCK);

		// Try to receive a packet
		result = recv(sd, buffer, len, flags);

		if (ioflag != -1)
			fcntl(sd, F_SETFL, ioflag);

		return result;
	}

	// If we reach here, we have timed out
	return -2;
} // fromPhysicalLayer(int) 
