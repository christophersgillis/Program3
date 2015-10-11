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

// Returns a usable address from a given host name
// Copied from pg. 104 of TCP/IP Sockets in C by Donahoo and Calvert
unsigned long ResolveName(char name[]);

// Print a given error message and end the program
void DieWithError(char * errorMessage);
