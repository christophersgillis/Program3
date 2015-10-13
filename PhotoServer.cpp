/*
 * PhotoServer.cpp
 *
 * Author: Christopher Gillis
 * Created on: October 11, 2015
 *
 * The server side of a program that will allow multiple clients to send photos
 * over a network to the same server simultaneously.
 */

#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::ofstream;
#include <sys/socket.h>	// for socket(), bind(), and connect()
#include <arpa/inet.h>	// for sockaddr_in and inet_ntoa()
#include <cstdlib>		// for atoi()
#include <cstring>		// for memeset()
#include <unistd.h>		// for close()
#include <string>
using std::string;

#include "utility.h"
#include "Frame.h"
#include "tcp_server.h"
#include "tcp_socket.h"
#include "ServerDL.h"

#define MAX_CLIENTS		5	// The maximum number of clients to accpet
#define RCV_BUF_SIZE	135	// The maximum size of the buffer to receive frames in
#define ever			;;	// To run our loop for(ever)

// TCP client handling
void HandleTCPClient(int serv, int clntNum);

int main(int argc, char * argv[])
{
	int servSock;						// Server socket descriptor
	int clntSock;						// Client socket descriptor
	struct sockaddr_in photoServAddr;	// Local address
	struct sockaddr_in photoClntAddr;	// Client address
	unsigned int clntLen;				// Length of client address structure

	// Initialize our server
	tcp_server serv(SERVER_PORT);

	serv.start();

	for(ever)
	{
		clntSock = serv.acceptSocket();

		cout << "handling client " << inet_ntoa(serv.getServAddr().sin_addr) << endl;

		HandleTCPClient(clntSock, 1);
	}
}

// Function to pass to threads. Reads from the clntSocket until all photos are 
// received.
void HandleTCPClient(int sock, int clientNumber)
{
	char buffer[RCV_BUF_SIZE];	// A buffer to receive one frame.
	long bytesRead;
	int photoNum;
	int frameLen;
	ofstream photo;
	ServerDL dl;
	Packet tempPkt;

	// Create the socket to connect to
	tcp_socket servSock(sock);

	// Read the size of the next frame to receive.
	bytesRead = servSock.readFromSocket(buffer, 3);
	frameLen = atoi(buffer);

	if (frameLen > RCV_BUF_SIZE)
		DieWithError("Can't receive more than 135 bytes");

	// Open the photo to write to
	string photoName;
	photoName = "photo11";

	photo.open(photoName.c_str(), ofstream::out);

	if (!photo.is_open())
		DieWithError("Error opening photo.");

	while (bytesRead > 0)
	{
		// Read in a frame
		if ((bytesRead = servSock.readFromSocket(buffer, frameLen)) < 0)
			DieWithError("recv() failed");

		cout << bytesRead << endl;;

		// Create a frame from the received string
		if (!dl.addFrame(buffer, bytesRead))
		{
			// If there was an error with the frame, recv another frame
			cout << "Error detected" << endl;
			
			// Send an ack
		}
		// Send the packets to the network layer
		if (dl.getNumFrames() > 1)
		{
			tempPkt = dl.buildPacket();
			photo.write(tempPkt.getPacket(), strlen(tempPkt.getPacket()));

			if (tempPkt.getEOPH() == IS_EOPH)
				break;
		}

		// Read in the next size
		if ((bytesRead = servSock.readFromSocket(buffer, 3)) < 0)
			DieWithError("recv() failed");

		frameLen = atoi(buffer);
	}

	photo.close();
} // HandleTCPClient(int, int)
