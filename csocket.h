#ifndef CSOCKET_H
#define CSOCKET_H

#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>

//-----------------------------------------------------------------------------------------------------
/**
 * The server program provides functionality for both, client and server sides.
 * It allows to create a socket,  bind a name to the socket and start listening for this socket.
 * Since several clients may attempt to connect more or less simultaneously,
 * a queue of pending connections is maintained in the system address space.
 * The listen() call marks the socket as willing to accept connections and initializes the queue.
 */
//-----------------------------------------------------------------------------------------------------
class csocket
{
	private:
		int sockfd;	// socket descriptor 
		int send_recv_sockfd;	// socket descriptor of accepted connection
		struct sockaddr_in server;
		struct sockaddr_in client;
		char buffer[1024];

	public: 
		unsigned short int port;
		int backlog;	// connection queue size

		csocket();
		~csocket(); 

		int open();
		int bindName(unsigned short int port);
		int listenSocket(int maxConn);
		int acceptRequest();
		int connectSocket(unsigned short int serverPort, char * serverIp);
		int receiveMsg();
		int sendMsg(char * buff);
		int closeSocket();
		int closeSession();
}; 

#endif /*CSOCKET_H_*/
