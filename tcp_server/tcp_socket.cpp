// TCP_Socket Abstraction

#include "tcp_socket.h"

// Matthew Beaulieu
// Initializes with some file descriptor
tcp_socket::tcp_socket(long socket_fd){
	m_socket_fd = socket_fd;
	m_connected = true;

	//Set up file descriptor sets
	FD_ZERO(&m_activefds);
	FD_SET(socket_fd, &m_activefds);
}

// Matthew Beaulieu
// Writes a message to the socket with how big it is
bool tcp_socket::writeToSocket(char * message, unsigned long size)
{
	//Don't send anything if the size is zero or we are not connected
	if(size==0||!m_connected)
	{

		return false;
	}

	//Will return the bytes sent over the network
	size_t bytesSent = send(m_socket_fd, message, size, 0);
	//Check we sent the bytes that were intended to be sent
	if(bytesSent!=size)
	{
		std::cout<<"Error: Writing to Socket"<<std::endl;
		return false;
	}
	return true;

}

// Matthew Beaulieu
// Reads from the socket into a buffer
long tcp_socket::readFromSocket(char * array, unsigned long maxSize)
{
	//Don't read unless we are connected, listening and intend to read one or more bytes
	if(maxSize==0||!m_connected)
	{
		return false;
	}
	
	//Here we read up to maxSize
	if(maxSize > MAX_BUFFER_SIZE)
	{
		maxSize = MAX_BUFFER_SIZE;
	}
	
	// rc returns how many bytes were read
	long rc = recv(m_socket_fd, array, maxSize, 0);
	
	//Socket error if rc < 0
	if(rc < 0)
	{
		std::cout<<"Socket Error on Read"<<std::endl;
	}
	
	// Nothing was read
	else if(rc == 0)
	{
		std::cout<<"No Data Received from Socket"<<std::endl;
	}
	return rc;
}

// Matthew Beaulieu
long tcp_socket::readFromSocketWithTimeout(char * array, unsigned long maxSize, unsigned long millis){
	//Don't read unless we are connected, listening and intend to read one or more bytes
	if(maxSize==0||!m_connected)
	{
		return 0;
	}
	
	// Set the file descriptor
	fd_set readFds;
	FD_ZERO(&readFds);
	FD_SET(m_socket_fd,&readFds);

	timeval t;
	t.tv_sec = millis/1000;					// Seconds
	t.tv_usec = (millis%1000) * 1000;	// micro seconds
	
	// if the message is too large, only read up to max size
	if(maxSize > MAX_BUFFER_SIZE)
	{
		maxSize = MAX_BUFFER_SIZE;
	}
	
	long count;
	
	// checks the socket using select
	if(select(m_socket_fd + 1, &readFds, NULL, NULL, &t) > 0){
		// If the FD is set 
		if(FD_ISSET(m_socket_fd, &readFds)){
			//Read from Socket
			count = recv(m_socket_fd, (char *)array, maxSize, 0);

		}
		
		// finds the time that Select times out
		else{
			std::cout<<"Select Timeout of: "<<t.tv_sec<<" seconds and "<<t.tv_usec<<" milliseconds has passed"<<std::endl;
			count = 0;
		}
	}
	
	// if select returns an error
	else{
		std::cout<<"select() error"<<std::endl;
		count = -1;
	}
	return count;
}

// Matthew Beaulieu
void tcp_socket::closeSocket(){
	// set the socket as !connected and close it
	if(m_connected){
		m_connected = false;
		close(m_socket_fd);
	}
}

// Clean it up
tcp_socket::~tcp_socket(){
	//Clean-Up
	closeSocket();
}
