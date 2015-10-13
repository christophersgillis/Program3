/*
 * ClientPL.h
 *
 * Author: Christopher Gillis
 * Created on: October 11, 2015
 *
 * The simulated physical layer of our client that will take frames and send them
 * to our server as TCP messages.
 */

#ifndef __CLIENTPL_H_
#define __CLIENTPL_H_

#include "Frame.h"
#include "utility.h"
#include <sys/socket.h>	// for send() and recv()
#include <unistd.h>
#include <fcntl.h>

class ClientPL
{
	private:
		
	public:
		/* Default constructor */
		ClientPL();

		/* Send the frame to the server */
		void toPhysicalLayer(int sd, Frame frame);

		/* Receive frames back from the server */
		int fromPhysicalLayer(int sd, char * buffer, int len, int flags, int to);
};	// ClientPL

#endif
