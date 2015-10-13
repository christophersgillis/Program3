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
	// Makes a TCP Server given a port
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

	// Get the socket descriptor
	int getServSock() const { return lServerSocket; };

	// Get the server address structure
	struct sockaddr_in getServAddr() const { return servAddr; };

	// Get the client address structure
	struct sockaddr_in getClntAddr() const { return clntAddr; };
// private embers
private:
	unsigned short nPort;		// Port which the server binds to
	int lServerSocket;			// Socket FD for server
	bool bListening;			// Whether or not the server is listening
	struct sockaddr_in clntAddr;// Client address
	struct sockaddr_in servAddr;// Local address
};

#endif 
