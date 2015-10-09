#
# Makefile for a concurrent server and its clients
#
# Authors: Christopher Gillis, Matthew Beaulieu
# Created on: September 30, 2015
#

CC= g++
CFLAGS= -c -Wall
LDFLAGS= -lm -lrt
CLIENT= FrameTest.cpp
SERVER= FrameTest.cpp
CLIENTEX= client
SERVEREX= server
SRC= Frame.cpp utility.cpp Packet.cpp
OBJECTS= $(SRC:.c=.o)

all: $(CLIENTEX) $(SERVEREX) Makefile

$(CLIENTEX): $(OBJECTS) $(CLIENT) $(SRC)
	$(CC) $(CLIENT) $(OBJECTS) -o $@ $(LDFLAGS)

$(SERVEREX): $(OBJECTS) $(SERVER) $(SRC)
	$(CC) $(SERVER) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(CLIENTEX) $(SERVEREX) 
