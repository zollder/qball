#include <unistd.h> 
#include <iostream.h> 
#include <errno.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <fcntl.h>
#include "csocket.h"

using namespace std; 

csocket::csocket()
{
	backlog = 10;	// set the default number of pending connections queue to 10
	send_recv_sockfd = -1;	// mark the send_recv_sockfd as invalid 
	open(); 
} 

csocket::~csocket()
{
	close_session();
	close(); 
} 

/**
 * Creates a socket in the specified domain, of the specified type and default protocol.
 * domain: AF_INET - Internet domain.
 * type: SOCK_STREAM - ensures bidirectional, reliable, sequenced, and un-duplicated flow of data without record boundaries.
 * protocol: 0 - unspecified/default (TCP is default for SOCK_STREAM)
 */
int csocket::open()
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd != 0)
		printf("Failed to open a socket. \n");
	else
		printf("Socket opened successfully. \n");

	return sockfd;
}

/**
 * Binds a name to a socket.
 * Allows processes to reference it to receive messages.
 * Communicating processes are bound by an "association."
 * In the Internet domain, an association is defined by <local address, local port, remote address, remote port> tuples
 * and must be unique.
 */
int csocket::bind(unsigned short int port)
{ 
	// the return value of function 
	int returnval;
	// set the port number 
	this->port = port;
	// host byte order
	addr.sin_family = AF_INET;
	// short, network byte order 
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	// local host
	/* zero the rest of the struct */ 
	memset(&(addr.sin_zero), 0, 8);

	// to make sure it does not block when socket related functions are called 
	int flags;
	flags = fcntl(sockfd, F_GETFL, 0); 
	if (flags == -1)
	{
		cout<<"Error in fcntl() call."<<endl; 
	}
	else
	{
		if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) 
			cout << "Error in fcntl() call." << endl; 
	}

	// To make sure the server does not block the other threads to use this port 
	int option = 1; 
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int)); 

	// use addr to bind the socket 
	return returnval; 
} 

int csocket::close_session()
{
	// check if socket session is created
	// invalidate session: close the session socket if the socket descriptor is valid
	send_recv_sockfd = -1;
	return 0;
}

int csocket::close()
{
	// close the accepted connections
	// chech that is socket created or not
	// close the socket if the socket descriptor is valid
	sockfd = -1;
	return 0;
}

int csocket::connect(unsigned short int HostPort, char * HostIP)
{ 
	int returnval;		// the return value of function 
	this->port = port;	// ***set the port number 

	/* host byte order */ 
	addr.sin_family = AF_INET;
	/* short, network byte order */ 
	addr.sin_port = htons(HostPort);

	addr.sin_addr.s_addr = inet_addr(HostIP);
	/* zero the rest of the struct */ 
	memset(&(addr.sin_zero), 0, 8);
	// connect to the server 
	send_recv_sockfd=sockfd; 
	// set the send_recv_sockfd equal to sockfd 
	return returnval; 
} 

int csocket::listen()
{ 
	// the return value of function 
	int returnval; 
	// listen to the port 
	return returnval; 
} 

int csocket::accept()
{ 
	// accept the connection from client 
	return send_recv_sockfd;
} 

int csocket::send(char * buff, int len)
{ 
	int returnvalue;	// send data return returnvalue; 
} 

int csocket::receive(char * buff, int len)
{ 
	int returnvalue; 
	// receive 
	return returnvalue; 
}
