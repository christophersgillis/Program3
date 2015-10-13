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
#include <cstdio>

#define NOT_EOPH 0x02	// This is not the last packet of a photo
#define IS_EOPH  0x03	// This is the last packet of a photo

class Packet
{
	private:
		char packet[256];	// A single packet read in from an image file
		char eoph;			// A byte telling whether this is the last packet of an image file
		int size;			// The size of the packet

	public:
		/* Default constructor */
		Packet();

		/* Constructor with arguments */
		Packet(char * init_packet, char init_eoph);

		/* Make a string with the information of the packet in sequential order */
		void constructPacket(char * pktString);

		/* Build a packet structure with from a formatted string */
		void deconstructPacket(char * pktString, int pktSize);

		/* Setter/getter */
		void setPacket(char * new_packet);
		char * getPacket() { return packet; }

		void setEOPH(char new_eoph);
		char getEOPH() const { return eoph; }

		void setSize(int new_size) {size = new_size;};
		int getSize() const { return size; };
};

#endif
