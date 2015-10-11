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
