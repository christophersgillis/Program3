/*
 * utility.h
 *
 * Author: Christopher Gillis
 * Created on: October 4, 2015
 *
 * Defines some useful non-class specific functions
 */

#include <cstdlib>
#include <netdb.h>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

// Returns a usable address from a given host name
// Copied from pg. 104 of TCP/IP Sockets in C by Donahoo and Calvert
unsigned long ResolveName(char name[]);

// Print a given error message and end the program
void DieWithError(char * errorMessage);

// Returns the number of bytes read in a single recv() call.
// Returns -1 if there is an error with fd or -2 if there is a timeout.
// Copied from http://developerweb.net/viewtopic.php?id=2933
int recv_to(int fd, char * buffer, int len, int flags, int to);
