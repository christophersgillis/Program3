/*
 * Author: Christopher Gillis, Matthew Beaulieu
 * Created on: September 30, 2015
 *
 * The client side of a program to send multiple photos from multiple clients
 * to a single server that will handle all clients simultaneously using 
 * threads.
 *
 * This program will also simulate the network, datalink, and physical layers
 * of the connection.
 */

#include <cstdlib>		// for exit(), atoi()
#include <iostream>		// for standard input and output
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
#include <fstream>		// for file input and output
using std::ifstream;
#include <sys/socket.h>	// for socket(), connect(), send() and recv()
#include <arpa/inet.h>	// for sockaddr_in and inet_addr()
#include <cstdlib>		// for atoi()
#include <unistd.h>		// for close()
#include <cstring>		// for memset()
#include <string>
using std::string;

#include "Frame.h"		// To make frames
#include "Packet.h"		// To make packets
#include "ClientDL.h"	// To manage frames
#include "utility.h"	// for DieWithError() and ResolveName()
#include "tcp_client.h"	// To simulate the physical layer

#define PORT_NUMBER 36500	// The port number used to connect to the server
#define TIMEOUT		1000	// Time in milliseconds to wait for a frame
#define ever 		;;		// To run our loop for(ever)

int main(int argc, char * argv[])
{
	int sock;				// Socket descriptor
	struct sockaddr_in photoServAddr;	// Address of server
	char * servName;		// The name of the server to connect to
	string photoName;		// The name of the current photo we are sending
	ifstream photo;			// The file we are reading from
	int numPhotos;			// The number of photos to send to the server
	char temp[256];			// A temporary string to hold chunks from the file
	Packet tempPkt;			// Holds chunks of the file before they are broken into frames
	ClientDL dl;			// The simulated datalink layer for this client
	int id;					// A unique id for this client
	tcp_client pl;			// The simulated physical layer for this client
	int bytesRcvd;			// The number of bytes received in a single recv call
	char frameBuffer[135];	// The buffer for a received frame

	/* Check for the proper number of arguments */
	if (argc < 4 || argc >= 5)
	{
		cerr << "Usage: <Server Name> <Client ID> <# of photos>" << endl;
	}

	/* Get the arguments from the command line */
	servName = argv[1];
	id = atoi(argv[2]);
	numPhotos = atoi(argv[3]);

	cout << "connecting" << endl;
	/* Create a stream socket using TCP */
	if (!pl.connectToServer(servName, PORT_NUMBER))
		DieWithError("Could not connect to server.");
	cout << "connected" << endl;
	/* Send the photos to the server */
	int i;
	for (i = 0; i < numPhotos; i++)
	{
		/* Prompt the user for the file name of the photo to send */
		cout << "Please enter the photo you would like to send: " << endl;
		cin >> photoName;

		/* Open the file and read from it in 256 byte chunks */
		photo.open(photoName.c_str(), std::ios::binary);

		/* Make sure the file opened correctly */
		if (!photo.is_open())
			DieWithError("Error opening photo.");

		/* Read until the end of the photo in fixed size chunks */
		for (ever)
		{
			// Read from the photo file
			photo.read(temp, 256);

			// Build the packet structure
			tempPkt.setSize(photo.gcount() + 1);
			tempPkt.setPacket(temp);
			tempPkt.setEOPH(NOT_EOPH);

			// If we don't read the full amount, we must be at the end of the
			// file.
			if (photo.eof())
				tempPkt.setEOPH(IS_EOPH);

			// Pass the packet to the datalink layer
			dl.toNetworkLayer(tempPkt);
			
			// Pass to the physical layer
			int i;
			for (i = 0; i < dl.getNumFrames(); i++)
			{
				int bytesSent;

				// Send the frame to the server
				dl.getFrame(i).constructFrame(frameBuffer);
				int fBufferLen = dl.getFrame(i).getSize();;
				char buffer[3];
				int bufferLen = 3;
				sprintf(buffer, "%3d", fBufferLen);

				// Send the length of the frame to the server
				pl.writeToSocket(buffer, bufferLen);

				// Send the frame to the server
				bytesSent = pl.writeToSocket(frameBuffer, fBufferLen);

				cout << bytesSent << endl;
/*				// Recv the frame back from the server
				bytesRcvd = pl.readFromSocketWithTimeout(frameBuffer, MAX_BUFFER_SIZE, TIMEOUT);
				
				if (bytesRcvd == 0)
					DieWithError("Recv() failed");
				else if (bytesRcvd == -1)
				{
					// handle timeout
				}
				else
				{
					// Send ack to datalink layer
				} */
			}

			// If this was the last frame of the photo, move on to the next photo
			if (tempPkt.getEOPH() == IS_EOPH)
			{
				cout << "End of photo" << endl;
				break;
			}
		}

		// Close the file
		photo.close();
	}

	// Clean up
	pl.closeSocket();
}
