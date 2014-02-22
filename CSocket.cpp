#include <unistd.h> 
#include <iostream.h> 
#include <errno.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <fcntl.h>

#include "CSocket.h"

using namespace std; 

//-----------------------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------------------
CSocket::CSocket()
{
	backlog = 10;			// set the default number of pending connections queue to 10
	send_recv_sockfd = -1;	// mark the send_recv_sockfd as invalid
	open(); 
} 

//-----------------------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------------------
CSocket::~CSocket()
{
	closeSession();
	closeSocket();
} 

/** -----------------------------------------------------------------------------------------
 * Client/Server.
 * Creates a socket in the specified domain, of the specified type and default protocol.
 * domain: AF_INET - Internet domain.
 * type: SOCK_STREAM - ensures bidirectional, reliable, sequenced, and non-duplicated
 * flow of data without record boundaries.
 * protocol: 0 - unspecified/default (TCP is default for SOCK_STREAM)
 * -----------------------------------------------------------------------------------------*/
int CSocket::open()
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		printf("Failed to open a socket. \n");
	else
		printf("Socket opened successfully. \n");

	return sockfd;
}

/** -----------------------------------------------------------------------------------------
 * Server.
 * Binds a name to a socket.
 * Allows processes to reference it to receive messages.
 * Communicating processes are bound by an "association."
 * In the Internet domain, an association is defined by
 * <local address, local port, remote address, remote port> tuples and must be unique.
 * -----------------------------------------------------------------------------------------*/
int CSocket::bindName(unsigned short int port)
{ 
	// set the port number 
	this->port = port;

	// create a name with wildcards
	server.sin_family = AF_INET;			// host byte order
	server.sin_addr.s_addr = INADDR_ANY;	// localhost
	server.sin_port = htons(port);			// short, network byte order
	memset(&(server.sin_zero), 0, 8);		// pad the rest of the struct with zeros

	// bind the name to the socket (must be created first)
	int status = bind(sockfd, (struct sockaddr *)&server, sizeof(server));
	if (status < 0)
		printf("Failed to bind a name. \n");
	else
	{
		printf("Name bound successfully. \n");
		printf("Port in use: %u \n", port);
	}

	return status;
} 

/** -----------------------------------------------------------------------------------------
 * Server.
 * Listens for connections on a socket.
 * Accepts the max number of allowed connections as an argument.
 * Returns status of the request (-1 if an error occurs).
 * -----------------------------------------------------------------------------------------*/
int CSocket::listenSocket(int maxConn)
{
	// set max number of clients on the socket
	backlog = maxConn;
	int status = listen(sockfd, backlog);
	if (status < 0)
		printf("[SERVER] Listen operation error.\n");
	else
		printf("[SERVER] Started listening for requests.\tStatus: %d \n", status);

	return status;
}

/** -----------------------------------------------------------------------------------------
 * Server.
 * Accept a connection on a socket.
 * Returns a descriptor for the accepted socket.
 * -----------------------------------------------------------------------------------------*/
int CSocket::acceptRequest()
{
	send_recv_sockfd = accept(sockfd, 0 , 0 );
	if (send_recv_sockfd < 0)
	{
		printf("[SERVER] Failed to accept stream message. \n");
		return EXIT_FAILURE;
	}
	else
		printf("[SERVER]Request accepted successfully.\tStatus: %d \n", send_recv_sockfd);

	return send_recv_sockfd;
}

/** -----------------------------------------------------------------------------------------
 * Client.
 * Establishes a connection to a known service IP on a server according to specified
 * socket type and binds a name to a socket.
 * If successful, the socket is associated with the server and data transfer may begin.
 * Returns request status (0 - success, -1 - error).
 * -----------------------------------------------------------------------------------------*/
int CSocket::connectSocket(unsigned short int serverPort, char * serverIp)
{
	// set server port number
	this->port = serverPort;

	server.sin_family = AF_INET;
	server.sin_port = htons(serverPort);
	server.sin_addr.s_addr = inet_addr(serverIp);
	memset(&(server.sin_zero), 0, 8);	// pad the rest of the struct with zeros

	// connect to the server with the specified descriptor (sockfd)
	int status = connect(sockfd, (struct sockaddr *)&server, sizeof (server));
	if (status < 0)
	{
		printf("[CLIENT] Error connecting to a socket. \n");
		return EXIT_FAILURE;
	}
	else
		printf("[CLIENT] Client successfully connected.\tStatus: %d \n", status);

	send_recv_sockfd = sockfd;

	return status;
}

/** -----------------------------------------------------------------------------------------
 * Client/Server.
 * Receives/Reads message from a descriptor and writes it to a buffer.
 * -----------------------------------------------------------------------------------------*/
int CSocket::receiveMsg()
{
	memset(buffer, 0, sizeof(buffer));

	int rvalue  = recv(send_recv_sockfd, buffer,  sizeof(buffer), MSG_WAITALL);;
	if (rvalue < 0)
		printf("[CLIENT] Error reading from stream socket. \n");
	else if (rvalue == 0)
		printf("[CLIENT] Empty stream, ending connection. \n");
	else
		printf("[CLIENT] Message received successfully.\n");

	return rvalue;
}

/** -----------------------------------------------------------------------------------------
 * Client/Server.
 * Sends/Writes message to a socket from the specified buffer.
 * -----------------------------------------------------------------------------------------*/
int CSocket::sendMsg(double *sendBuffer)
{
	int status = write(send_recv_sockfd, sendBuffer, sizeof(buffer));
	if (status < 0)
		printf("[SERVER] Error writing on stream socket.\n");
	else
		printf("[SERVER] Message successfully sent.\n", sendBuffer);

	return status;
}

/** -----------------------------------------------------------------------------------------
 * Shuts down all or part of a full-duplex connection on the socket.
 * -----------------------------------------------------------------------------------------*/
int CSocket::closeSession()
{
	// verify that session is not already closed
	if (send_recv_sockfd < 0)
	{
		printf("[CLIENT] Session already closed. \n");
		exit(1);
	}

	// shut down the session (server or client) and validate
	int status= shutdown(send_recv_sockfd, 0);
	if (status < 0)
	{
		printf("[CLIENT] Invalid session descriptor. \n");
		exit(2);
	}

	// close session socket if it belongs to the server and validate
	if (send_recv_sockfd != sockfd)
	{
		status = close(send_recv_sockfd);
		if (status < 0)
		{
			printf("[SERVER] Error closing session socket. \n");
			exit(3);
		}
		else
			printf("[SERVER] Session socket closed\n");
	}
	else
		// report success otherwise and invalidate session socket
		printf("[SERVER] Session socket successfully closed. \n");

	send_recv_sockfd = -1;

	return status;
}

/** -----------------------------------------------------------------------------------------
 * Closes socket.
 * -----------------------------------------------------------------------------------------*/
int CSocket::closeSocket()
{
	// verify that socket is not already closed
	if (sockfd < 0)
	{
		printf("Socket already closed or descriptor is invalid \n");
		exit(1);
	}

	int status = close(sockfd);

	if (status < 0)
		printf("Invalid socket descriptor. \n");
	else
		printf("Socket successfully closed. \n");

	sockfd = -1;

	return status;
}

/** -----------------------------------------------------------------------------------------
 * Returns pointer to a buffer with received data.
 * -----------------------------------------------------------------------------------------*/
double* CSocket::getData()
{
	return buffer;
}


