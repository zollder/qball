/*
 *cppsocket.cpp
 *  Created on: 2014-02-15
 *		Author: eugen, oleg
 */
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include "cppsocket.h"
#include "socketException.h"

using namespace std;

cppsocket::cppsocket(string name)
{
	backlog = 10;			// set the default number of pending connections queue to 10
	send_recv_sockfd = -1;	// mark the send_recv_sockfd as invalid
	type = name;			//name of the host type that is instantiated
}

/** ---------------------------------------------------------------------------------------------------------------------------
 * Client.
 * Establishes a connection to a known service IP on a server according to specified socket type and binds a name to a socket.
 * If successful, the socket is associated with the server and data transfer may begin.
 * Returns request status (0 - success, -1 - error)
-----------------------------------------------------------------------------------------------------------------------------*/
void cppsocket::clientConnect( unsigned short int serverPort, char * serverIp )
{
	try
	{
		open();
		cout<<"[KPI::"<<type<<"]:Socket opened\t\t\t\t[OK]"<<endl;

		server.sin_family = AF_INET;
		server.sin_port = htons(serverPort);
		server.sin_addr.s_addr = inet_addr(serverIp);
		memset(&(server.sin_zero), 0, 8);	// pad the rest of the struct with zeros

		createConnect();
		cout<<"[KPI::"<<type<<"]:Connected to "<< serverIp<< "\t\t\t[OK]"<<endl;
	}
	catch( socketException &e)
	{
		cerr<<"[KPI::"<<type<<" ERROR]:"<< e.what()<<endl;
		exit(EXIT_FAILURE);
	}

}

void cppsocket::createConnect ()
{
	// connect to the server with the specified descriptor (sockfd)
	int status = connect(sockfd, (struct sockaddr *)&server, sizeof (server));
	if (status < 0)
		throw socketException("Error connecting to a socket");

	send_recv_sockfd = sockfd;
}


void cppsocket::serverConnect( unsigned short int serverPort , int maxConnect)
{
	try
	{
		open();
		cout<<"[KPI::"<<type<<"]:Socket opened\t\t\t\t[OK]"<<endl;

		bindName(serverPort);
		cout<<"[KPI::"<<type<< "]:Bounded on port "<< serverPort << "\t\t\t[OK]"<<endl;

		listenSocket( maxConnect );
		cout<<"[KPI::"<<type<< "]:Listening on port " << "\t\t\t[OK]"<<endl;
	}
	catch( socketException &e)
	{
		cerr<<"[KPI::"<<type<<" ERROR]:"<<endl;
		exit(EXIT_FAILURE);
	}

	// TODO: accept request should throw a different exception
	// it allows to use one 'try' with two 'catches' for different exceptions
	try
	{
		acceptRequest();
		cout<<"[KPI::"<<type<< "]:Accepted connection" << "\t\t\t[OK]"<<endl;
	}
	catch( socketException &e)
	{
		cerr<<"[KPI::"<<type<<" ERROR]:"<< e.what()<<endl;
	}


}

/** ---------------------------------------------------------------------------------------------------------------------------
 * Client/Server.
 * Creates a socket in the specified domain, of the specified type and default protocol.
 * domain: AF_INET - Internet domain.
 * type: SOCK_STREAM - ensures bidirectional, reliable, sequenced, and non-duplicated flow of data without record boundaries.
 * protocol: 0 - unspecified/default (TCP is default for SOCK_STREAM)
 -----------------------------------------------------------------------------------------------------------------------------*/
void cppsocket::open()
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		//throw string("Failed to open a socket");
		throw socketException("Failed to open a socket");
}

/** ---------------------------------------------------------------------------------------------------------------------------
 * Server.
 * Binds a name to a socket.
 * Allows processes to reference it to receive messages.
 * Communicating processes are bound by an "association."
 * In the Internet domain, an association is defined by <local address, local port, remote address, remote port> tuples
 * and must be unique.
-----------------------------------------------------------------------------------------------------------------------------*/
void cppsocket::bindName( unsigned short int serverPort  )
{
	// create a name with wild cards
	server.sin_family = AF_INET;			// host byte order
	server.sin_addr.s_addr = INADDR_ANY;	// localhost
	server.sin_port = htons(serverPort);	// short, network byte order
	memset(&(server.sin_zero), 0, 8);		// pad the rest of the struct with zeros

	// bind the name to the socket (must be created first)
	int status = bind(sockfd, (struct sockaddr *)&server, sizeof(server));
	if (status < 0)
		throw socketException("Failed to bind a name");
}

/** ---------------------------------------------------------------------------------------------------------------------------
 * Server.
 * Listens for connections on a socket.
 * Accepts the max number of allowed connections as an argument.
 * Returns status of the request (-1 if an error occurs)
 -----------------------------------------------------------------------------------------------------------------------------*/
void cppsocket::listenSocket( int maxConnect )
{
	// set max number of clients on the socket
	backlog = maxConnect;

	int status = listen(sockfd, backlog);

	if (status < 0)
		throw socketException("Listen operation error");
}

/** ---------------------------------------------------------------------------------------------------------------------------
 * Server.
 * Accept a connection on a socket.
 * Returns a descriptor for the accepted socket.
-----------------------------------------------------------------------------------------------------------------------------*/
void cppsocket::acceptRequest()
{
	send_recv_sockfd = accept(sockfd, 0 , 0 );
	if (send_recv_sockfd < 0)
		throw socketException("Failed to accept stream message");
}

/** ---------------------------------------------------------------------------------------------------------------------------
 * Server / Client.
 * Receives/Read message from a descriptor and writes it to a buffer.
 *-----------------------------------------------------------------------------------------------------------------------------*/
void cppsocket::receiveMsg()
{
	try
	{
		receive();
		cout<<"[KPI::"<<type<< "]:Message received: "<< buffer <<"\t[OK]"<<endl;
	}
	catch( socketException &e)
	{
		cerr<<"[KPI::"<<type<<" ERROR]:"<< e.what()<<endl;
	}

}

void cppsocket::receive()
{
	memset(buffer, 0, sizeof(buffer));

	//operation block until the full request is satisfied
	int rvalue  = recv(send_recv_sockfd, buffer,  sizeof(buffer),MSG_WAITALL);
	if (rvalue < 0)
		throw socketException("Error reading from stream socket. \n");
	else if (rvalue == 0)
		throw socketException("Empty stream, ending connection. \n");

}

/** ---------------------------------------------------------------------------------------------------------------------------
 * Client/Server.
 * Sends/Writes message to a socket from the specified buffer.
 *-----------------------------------------------------------------------------------------------------------------------------*/
void cppsocket::sendMsg(char * sendBuffer)
{
	try
	{
		int status = write(send_recv_sockfd, sendBuffer, sizeof(buffer));
			if (status < 0)
				throw socketException("Error writing on stream socket");
		cout<<"[KPI::"<<type<< "]:Message sent: "<< sendBuffer <<"\t[OK]" <<endl;
	}
	catch( socketException &e)
	{
		cerr<<"[KPI::"<<type<<" ERROR]:"<< e.what()<<endl;
	}

}

/** ---------------------------------------------------------------------------------------------------------------------------
 * Shuts down all or part of a full-duplex connection on the socket.
 *-----------------------------------------------------------------------------------------------------------------------------*/
cppsocket::~cppsocket()
{
	try
	{
		closeSession();
		// report success otherwise and invalidate session socket
		cout<<"[KPI::"<<type<<"]:Session socket closed\t\t\t[OK]"<<endl;
	}
	catch( socketException &e)
	{
		cerr<<"[KPI::"<<type<<" ERROR]:"<< e.what()<<endl;
	}

	try
	{
		closeSocket();
		// report success otherwise and invalidate session socket
		cout<<"[KPI::"<<type<<"]:Socket closed\t\t\t\t[OK]"<<endl;
	}
	catch( socketException &e)
	{
		cerr<<"[KPI::"<<type<<" ERROR]:"<< e.what()<<endl;
	}
}
/** ---------------------------------------------------------------------------------------------------------------------------
 * Closes Session.
 *-----------------------------------------------------------------------------------------------------------------------------*/
void cppsocket::closeSession()
{
	// verify that session is not already closed
	if (send_recv_sockfd < 0)
		throw socketException("Session already closed");

	// shut down the session (server or client) and validate
	int status= shutdown(send_recv_sockfd, 0);
	if (status < 0)
		throw socketException("Invalid session descriptor");

	// close session socket if it belongs to the server and validate
	if (send_recv_sockfd != sockfd)
	{
		status = close(send_recv_sockfd);
		if (status < 0)
			throw socketException("Error closing session socket");
	}

	send_recv_sockfd = -1;
}

/** ---------------------------------------------------------------------------------------------------------------------------
 * Closes socket.
 *-----------------------------------------------------------------------------------------------------------------------------*/
void cppsocket::closeSocket()
{
	// verify that socket is not already closed
	if (sockfd < 0)
		throw socketException("Socket already closed or descriptor is invalid");

	int status = close(sockfd);
	if (status < 0)
		throw socketException("Invalid socket descriptor");

	sockfd = -1;
}
