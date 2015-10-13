// Matthew Beaulieu
// tcp server abstracts out tcp socket actions
#include "tcp_server.h"

// Matthew Beaulieu
tcp_server::tcp_server(unsigned short port)
{
	//Init all class variables
	nPort = port;
	lServerSocket = 0;
	bListening = false;
}

// Matthew Beaulieu
bool tcp_server::start()
{
	char myHostname[MAX_HOST];		//Holder for HOSTNAME
	struct hostent * pHostName;		//Pointer to our hostent

	// Clear the memory of sSockInfo
	memset(&servAddr, 0, sizeof(sockaddr_in));

	// Copy the system host name into myHostname
	gethostname(myHostname,MAX_HOST-1);

	// Check for Error in Getting Our Host
	if((pHostName=gethostbyname(myHostname))==NULL)
	{
		std::cout<<"Host Name Error on Server with Host Name: "<<myHostname<<std::endl;
		return false;
	}

	// IPV4 Addr
	servAddr.sin_family = AF_INET;

	// Use any available address for the Server
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// Set the port
	servAddr.sin_port = htons(nPort);


	// Creates the socket
	if((lServerSocket = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		std::cout<<"Failure Creating the Socket"<<std::endl;
		return false;
	}


	// Binds socket
	if(bind(lServerSocket,(struct sockaddr *) &servAddr, sizeof(sockaddr_in)) < 0)
	{
		std::cout<<"Failure Binding Socket"<<std::endl;
		std::cout<<"Error: "<<strerror(errno)<<std::endl;
		return false;
	}

	// Socket is now listening
	listen(lServerSocket,LISTEN_BACKLOG);
	
	// So we know the socket is listening
	bListening = true;
	return true;
}

// Matthew Beaulieu
long tcp_server::acceptSocket()
{
	long socket = 0;
	
	//Accept the socket or return an error
	unsigned int clntLen = sizeof(clntAddr);
	if((socket = accept(lServerSocket, (struct sockaddr *) &clntAddr, &clntLen)) < 0)
	{
		std::cout<<"Could not accept socket"<<std::endl;
		return 0;
	}
	return socket;
}

// Matthew Beaulieu
void tcp_server::closeServer()
{
	//Only close socket once
	if(bListening)
	{
		bListening = false;
		close(lServerSocket);
	}
}

// Matthew Beaulieu
tcp_server::~tcp_server()
{
	//Clean Up
	closeServer();
}
