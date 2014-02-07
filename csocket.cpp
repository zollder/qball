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

/** ---------------------------------------------------------------------------------------------------------------------------
 * Client/Server.
 * Creates a socket in the specified domain, of the specified type and default protocol.
 * domain: AF_INET - Internet domain.
 * type: SOCK_STREAM - ensures bidirectional, reliable, sequenced, and non-duplicated flow of data without record boundaries.
 * protocol: 0 - unspecified/default (TCP is default for SOCK_STREAM)
 -----------------------------------------------------------------------------------------------------------------------------*/
int csocket::open()
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd != 0)
		printf("Failed to open a socket. \n");
	else
		printf("Socket opened successfully. \n");

	return sockfd;
}

/** ---------------------------------------------------------------------------------------------------------------------------
 * Server.
 * Binds a name to a socket.
 * Allows processes to reference it to receive messages.
 * Communicating processes are bound by an "association."
 * In the Internet domain, an association is defined by <local address, local port, remote address, remote port> tuples
 * and must be unique.
-----------------------------------------------------------------------------------------------------------------------------*/
int csocket::bindName(unsigned short int port)
{ 
	// set the port number 
	this->port = port;

	// create a name with wildcards
	server.sin_family = AF_INET;			// host byte order
	server.sin_addr.s_addr = INADDR_ANY;	// localhost
	server.sin_port = htons(port);			// short, network byte order
	memset(&(server.sin_zero), 0, 8);		// pad the rest of the struct with zeros

	// to make sure it does not block when socket related functions are called 
	if (fcntl(sockfd, F_GETFL, 0) == -1)
		cout<<"Error in fcntl() call."<<endl; 

	// Set options associated with the socket
	// to make sure the server does't prevent other threads from using the port
	int option = 1; 
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) != 0)
		printf("Failed to set socket options. \n");

	// bind the name to the socket (must be created first)
	int status = bind(sockfd, (struct sockaddr *)&server, sizeof(server));
	if (status != 0)
		printf("Failed to bind a name. \n");
	else
	{
		printf("Name bound successfully. \n");
		printf("Port in use: %u \n", port);
	}

	return status;
} 

/** ---------------------------------------------------------------------------------------------------------------------------
 * Server.
 * Listens for connections on a socket.
 * Accepts the max number of allowed connections as an argument.
-----------------------------------------------------------------------------------------------------------------------------*/
int csocket::listenSocket(int maxConn)
{
	// set max number of clients on the socket
	backlog = maxConn;
	int status = listen(sockfd, backlog);
	if (status != 0)
		printf("Started listening for requests. \n");
	else
		printf("Listen operation error. \n");

	return status;
}

/** ---------------------------------------------------------------------------------------------------------------------------
 * Server.
 * Accept a connection on a socket.
-----------------------------------------------------------------------------------------------------------------------------*/
int csocket::acceptRequest()
{
	send_recv_sockfd = accept(sockfd, 0, 0);
	if (send_recv_sockfd == -1)
	{
		printf("Failed to accept stream message. \n");
		return EXIT_FAILURE;
	}

	return send_recv_sockfd;
}

/** ---------------------------------------------------------------------------------------------------------------------------
 * Client/Server.
 * Receives/Reads message from a descriptor and writes it to a buffer.
-----------------------------------------------------------------------------------------------------------------------------*/
int csocket::receiveMsg()
{
	memset(buffer, 0, sizeof(buffer));

	int rvalue  = read(send_recv_sockfd, buffer,  1024);
	if (rvalue < 0)
		printf("Error reading stream message. \n");
	else if (rvalue == 0)
		printf("Empty stream, ending connection. \n");
	else do
		printf("Buffer content: %s\n", buffer);
	while (rvalue > 0);

	return rvalue;
}

/** ---------------------------------------------------------------------------------------------------------------------------
 * Client.
 * Establishes a connection to a known service IP on a server according to specified socket type.
 * If successful, the socket is associated with the server and data transfer may begin.
-----------------------------------------------------------------------------------------------------------------------------*/
int csocket::connectSocket(unsigned short int serverPort, char * serverIp)
{
	// set server port number
	this->port = serverPort;

	server.sin_family = AF_INET;
	server.sin_port = htons(serverPort);
	server.sin_addr.s_addr = inet_addr(serverIp);
	memset(&(server.sin_zero), 0, 8);	// pad the rest of the struct with zeros

	// connect to the server
	int status = connect(sockfd, (struct sockaddr *)&server, sizeof (server));

	// set the send_recv_sockfd equal to sockfd
	send_recv_sockfd = sockfd;
	return status;
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

int csocket::send(char * buff, int len)
{ 
	int returnvalue;	// send data return returnvalue; 
} 

