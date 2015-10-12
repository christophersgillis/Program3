// Matthew Beaulieu
// tcp server abstracts out tcp socket actions header

#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

// Includes
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

// Constants
#define MAX_BUFFER_SIZE 256
#define MAX_HOST 255
#define SERVER_PORT 36500
#define LISTEN_BACKLOG 2

// Abstracts out and manages a TCP Server
class tcp_server{
public:
	// Makes a TCP Server givena  port
	tcp_server(unsigned short port);
	
	// Starts the TCP server
	bool start();

	// Accepts a connection
	long acceptSocket();

	/// stops and closes the server
	void closeServer();

	// If we're listening for clients, we cant do anything
	bool isListening()
	{
		return bListening;
	}
	
	// returns our port we're listening to
	unsigned short getPort()
	{
		return nPort;
	}
	
	// Cleans up
	virtual ~tcp_server();

// private embers
private:
	unsigned short nPort;			// Port which the server binds to
	long lServerSocket;			// Socket FD for server
	bool bListening;					// Whether or not the server is listening
};

#endif 
