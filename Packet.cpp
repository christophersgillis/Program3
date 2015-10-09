/*
 * Packet.cpp
 *
 * Author: Christopher Gillis
 * Created on: October 9, 2015
 */

#include "Packet.h"

/* Default constructor */
Packet::Packet()
{
	strcpy(packet, "");		// Initialize our packet to an empty string
	eoph = NOT_EOPH;		// Initially, no packet will be the last of a photo
} // Packet()

/* Constructor with arguments */
Packet::Packet(char * init_packet, char init_eoph)
{
	/* Make sure the packet is no more than 256 bytes */
	int packLen = strlen(init_packet);
	strncpy(packet, init_packet, 256);
	// Terminate the string
	if (packLen < 256)
		packet[packLen] = '\0';
	else
		packet[255] = '\0';

	/* Make sure the eoph byte is an appropriate value */
	if (init_eoph != NOT_EOPH && init_eoph != IS_EOPH)
		eoph = NOT_EOPH;
	else
		eoph = init_eoph;
} // Packet(char *, char)

/* Setters/Getters */
// Packet
void Packet::setPacket(char * new_packet)
{
	/* Ensure the packet is no more than 256 bytes */
	int packLen = strlen(new_packet);
	strncpy(packet, new_packet, 256);
	// Terminate the string
	if (packLen < 256)
		packet[packLen] = '\0';
	else
		packet[255] = '\0';
}
// Getter defined in header

void Packet::setEOPH(char new_eoph)
{
	/* Ensure the eoph byte is an appropriate value */
	if (new_eoph != NOT_EOPH && new_eoph != IS_EOPH)
		eoph = NOT_EOPH;
	else
		eoph = new_eoph;
}
// Getter defined in header
