// Matthew Beaulieu
// tcpclient.h

#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_

// Nescessary include files
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <vector>

///The size of a read buffer for TCP
#define MAX_BUFFER_SIZE 255

// tcp client handles all initializing of tcp socket connection
// as well as error checking
class tcp_client {
public:
        // initialize function. connected is false, socket is 0
        tcp_client();

        /* Connects to a remote server.
         * 
         * Must be used before reading or writing
         * ipaddr: Remote IP or Host Name of the Server
         * port: Port to communicate on
         * return -> true if connection success, false else
         */
        bool connectToServer(char * ipaddr, unsigned short port);

        /* Writes to a remote connection
         *
         * msg: string to write to server
         * size: size of the message
         * return -> true if write success, false else
         */
        bool writeToSocket(char * msg, unsigned long size);

		/* Checks whether or not the socket is connected
         * return -> true if bConnected, false is not bConnected
         */
        bool isConnected()
        {
                return bConnected;
        }
		
        /* Reads from a remote connection
         * array: Pointer to an allocated array that is passed and filled with the return string
         * maxSize: Max Size of the array to be allocated. Can not be bigger than MAX_BUFFER_SIZE
         * return -> size of the buffer read, 0 on error or no read
         */
        long readFromSocket(char * array, unsigned long max);
		long readFromSocketWithTimeout(char * array, unsigned long maxSize, unsigned long timeout);

		
        // closes the socket, ending TCP connection
        void closeSocket();

        //deletes TCP Client, cleans up socket
        ~tcp_client();

protected:
        //Socket File Descriptor
        long lSocket;

        //Is the socket connected
        bool bConnected;
};

typedef tcp_client physical_layer;
#endif /* TCP_CLIENT_H_ */
