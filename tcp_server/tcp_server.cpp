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
	struct sockaddr_in sSockInfo;						//Socket Information Structure
	char myHostname[MAX_HOST];					//Holder for HOSTNAME
	struct hostent * pHostName;						//Pointer to our hostent

	// Clear the memory of sSockInfo
	memset(&sSockInfo, 0, sizeof(sockaddr_in));/

	// Copy the system host name into myHostname
	gethostname(myHostname,MAX_HOSTNAME-1);

	// Check for Error in Getting Our Host
	if((pHostName=gethostbyname(myHostname))==NULL)
	{
		std::cout<<"Host Name Error on Server with Host Name: "<<myHostname<<std::endl;
		return false;
	}

	// IPV4 Addr
	sSockInfo.sin_family = AF_INET;

	// Use any available address for the Server
	sSockInfo.sin_addr.s_addr = htonl(INADDR_ANY);

	// Set the port
	sSockInfo.sin_port = htons(nPort);


	//Creates the socket
	if((lServerSocket = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		std::cout<<"Failure Creating the Socket"<<std::endl;
		return false;
	}


	// Binds socket
	if(bind(lServerSocket,(struct sockaddr *)&sSockInfo,sizeof(sockaddr_in)) < 0)
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
	if((socket = accept(lServerSocket,NULL,NULL)) < 0)
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
