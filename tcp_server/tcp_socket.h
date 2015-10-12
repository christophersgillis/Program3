// Matthew Beaulieu
// TCP Socket Include File

#ifndef TCP_SOCKET_H_
#define TCP_SOCKET_H_

// Include Section
#include <sys/time.h>
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

// Constants

// Maximum buffer size
#define MAX_BUFFER_SIZE 256



// Manages the TCP Connection
class tcp_socket{
private:
	///file descriptor set
	fd_set m_activefds;
	///file descriptors to read from
	fd_set m_readfds;
	///Socket file descriptor
	long m_socket_fd;
	///Whether or not the socket is connected
	bool m_connected;
	
	public:
	// makes a TCP socket with a file descriptor
	tcp_socket(long socket_fd);
	
	// closes the socket
	void closeSocket();
	// writes to the socket with a message and the size of the message
	bool writeToSocket(char * message, unsigned long size);

	// reads from some socket into an array, given the size of the array
	long readFromSocket(char * array, unsigned long maxSize);

	// Reads from the socket with the timeout
	long readFromSocketWithTimeout(char * array, unsigned long maxSize, unsigned long millis);

	// Get the file descriptor for the class
	long getNativeHandle(){
		return m_socket_fd;
	}

	// Whether or not the socket is connected
	bool isConnected(){
		return m_connected;
	}

	// Destructor
	virtual ~tcp_socket();
};

// type def to the physical layer for clarity sake
typedef tcp_socket physical_layer;


#endif /* TCP_SOCKET_H_ */
