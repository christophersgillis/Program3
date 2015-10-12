// Matthew Beaulieu
// tcp client abstracts out tcp socket actions

#include "tcp_client.h"
#include <fstream>

// tcp client class
tcp_client::tcp_client()
{
        // Initializing
        // We're not connected and our socket doesnt exist yet
        lSocket = 0;
        bConnected = false;
}

// Purpose: connect to the server
// return true if successful connection, else false
bool tcp_client::connectToServer(char * ipaddr, unsigned short port)
{
        //Gets the IP of the remote server
		int h;
        //hostnet pointer
        struct hostent * pHostnet;

        //Remote Socket Info
        struct sockaddr_in sockInfo;

        // conveniant function to get the hostname
        pHostnet = gethostbyname(ipaddr);

        // if we did not correctly get the name, error message
        if(!pHostnet)
        {
                std::cout<<"Error: Could not resolve host name: "<<ipaddr<<std::endl;
                return false;
        }

        //zero the memory of socket info
        memset(&sockInfo,0,sizeof(sockInfo));

        // copy socket info
        memcpy((char*)&sockInfo.sin_addr, pHostnet->h_addr, pHostnet->h_length);

        // set socket info
        sockInfo.sin_family = AF_INET;
        sockInfo.sin_port = htons(port);

        //Create the socket, if error return false and print message
        if((lSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
                std::cout<<"Error: Could not create socket."<<std::endl;
                return false;
        }

		//Connect, if error return false and print message
        if(connect(lSocket,(struct sockaddr *)&sockInfo,sizeof(sockInfo)) < 0)
        {
                std::cout<<"Error: Could not connect to IP:"<<ipaddr<<" on port: "<<port<<std::endl;
                return false;
        }

        // if the method has not returned false yet, then we are connected
        bConnected = true;
        return true;
}

// Purpose: write command and error checking
bool tcp_client::writeToSocket(char * msg, unsigned long size)
{
        //if our size is zero or the socket is not connnected, dont send anything
        if(size==0||!bConnected)
        {
                std::cout<<"Error: Message size is 0 or socket not connected"<<std::endl;
                return false;
        }

        //calls send command and saves sentBytes
        size_t sentBytes = send(lSocket, msg, size, 0);

        //Check the proper amount of bytes was sent
        if(sentBytes!=size)
        {
        	return -1;
        }
        return sentBytes;

}

// Purpose: read from a socket and error checking
long tcp_client::readFromSocket(char * array, unsigned long max)
{
	// If the message has 0 bytes or not connected, don't connect
	if(max==0||!bConnected)
	{
			return false;
	}

	// if the max is grater than our maximum buffer suze it needs to be smaller
	if(max > MAX_BUFFER_SIZE)
	{
		max = MAX_BUFFER_SIZE;
	}

	//recieves data from sockey
	long rc = recv(lSocket, array, max, 0);

	// Socket error
	if(rc < 0)
	{
			std::cout<<"Socket Error on Read"<<std::endl;
	}
	//No data received
	else if(rc == 0)
	{
	}
	return rc;
}

// Matthew Beaulieu
long tcp_client::readFromSocketWithTimeout(char * array, unsigned long maxSize, unsigned long timeout){
	//Don't perform a read if we are not connected or we are requesting a message of 0 bytes
	if(maxSize==0||!bConnected)
	{
		return false;
	}
	
	// Set the file descriptor info
	fd_set readFds;
	FD_ZERO(&readFds);
	FD_SET(lSocket,&readFds);

	timeval t;											// timeout value
	t.tv_sec = timeout/1000;						// seconds
	t.tv_usec = (timeout%1000) * 1000;		// miceoseconds
	
	// if the message is too large, cut it down to max buffer size
	if(maxSize > MAX_BUFFER_SIZE)
	{
		maxSize = MAX_BUFFER_SIZE;
	}
	
	//Bytes read
	long count;
	
	// trys to use select
	if(select(lSocket + 1, &readFds, NULL, NULL, &t) > 0){
		// if FD is set, read from the socket
		if(FD_ISSET(lSocket, &readFds)){
			count = recv(lSocket, array, maxSize, 0);
		}
		
		//fd_isset
		else{
			count = 0;
		}
	}

	// Handled by the network layer
	else{
		count = -1;
	}
	
	return count;
}

// Purpose: removes the object
tcp_client::~tcp_client()
{
        //Only cleanup to do is closing the socket
        closeSocket();
}

// Purpose: closes the socket
void tcp_client::closeSocket()
{
        // should only close the socket if you know, you're connected
        if(bConnected)
        {
                // reinitialize to disconnected values, call close
                bConnected = false;
                close(lSocket);
                lSocket = 0;
        }
}