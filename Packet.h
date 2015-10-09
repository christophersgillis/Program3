/*
 * Packet.h
 *
 * Author: Christopher Gillis
 * Created on: October 9, 2015
 *
 * Holds a packet to simulate the network layer between our photo clients and
 * server.
 */

#ifndef __PACKET_H_
#define __PACKET_H_

#include <cstring>

#define NOT_EOPH 0x02	// This is not the last packet of a photo
#define IS_EOPH  0x03	// This is the last packet of a photo

class Packet
{
	private:
		char packet[256];	// A single packet read in from an image file
		char eoph;			// A byte telling whether this is the last packet of an image file

	public:
		/* Default constructor */
		Packet();

		/* Constructor with arguments */
		Packet(char * init_packet, char init_eoph);

		/* Setter/getter */
		void setPacket(char * new_packet);
		char * getPacket() { return packet; }

		void setEOPH(char new_eoph);
		char getEOPH() const { return eoph; }
};

#endif
