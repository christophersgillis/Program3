/*
 * utility.cpp
 *
 * Author: Christopher Gillis
 * Created on: October 11, 2015
 *
 * Defiens some useful functions that don't fit into any specific class
 */

#include "utility.h"

// Print the given error message and end the program
void DieWithError(char * error)
{
	perror(error);
	exit(1);
} // DieWithError(char *)

// Returns a usable address from a given host name
// Copied from pg. 104 of TCP/IP Sockets in C by Donahoo and Calvert
unsigned long ResolveName(char name[])
{
	struct hostent *host;	// Structure to hold host's information

	if ((host = gethostbyname(name)) == NULL)
	{
		DieWithError("gethostbyname() failed");
		exit(1);
	}

	/* Return a usable binary, network-byte-ordered address */
	return *((unsigned long *) host->h_addr_list[0]);
} // ResolveName(char [])

// Returns the number of bytes read in a recv() call.
// Returns -1 if there is a problem, and returns -2 if there is a timeout
// Copied from http://developerweb.net/viewtopic.php?id=2933
/*
 * Params:
 * 	fd 		- Socket descriptor
 * 	buffer  - Buffer to hold what is read from recv() call
 *  len		- The length of the buffer
 *  flags	- Any flags to pass to the recv() call
 *  to		- The number of milliseconds until a timeout
 */
int recv_to(int fd, char * buffer, int len, int flags, int to)
{
	fd_set readset;			// The set of socket descriptors to watch
	int result;				// The return value
	int ioflag;				// To set io to non-blocking
	struct timeval timeout;	// To check for a timeout

	// Initialize the set
	FD_ZERO(&readset);
	FD_SET(fd, &readset);

	// Initialize the time out struct
	timeout.tv_sec = 0;
	timeout.tv_usec = to * 1000;
	result = select(fd + 1, &readset, NULL, NULL, &timeout);

	// Check for any errors
	if (result < 0)
		return -1;
	// Otherwise, recv() until we either get information or timeout
	else if (result > 0 && FD_ISSET(fd, &readset))
	{
		// Set non-blocking mode
		if ((ioflag = fcntl(fd, F_GETFL, 0)) != -1)
			fcntl(fd, F_SETFL, ioflag | O_NONBLOCK);

		// Try to receive a packet
		result = recv(fd, buffer, len, flags);

		if (ioflag != -1)
			fcntl(fd, F_SETFL, ioflag);

		return result;
	}

	// We have timed out if we make it here
	return -2;
} // recv_to(int, char *, int, int, int)
