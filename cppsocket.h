/*
 *cppsocket.h
 *  Created on: 2014-02-15
 *		Author: eugen, oleg
 */

#ifndef CPPSOCKET_H_
#define CPPSOCKET_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
//-----------------------------------------------------------------------------------------------------
/**
 * The server program provides functionality for both, client and server sides.
 * It allows to create a socket,  bind a name to the socket and start listening for this socket.
 * Since several clients may attempt to connect more or less simultaneously,
 * a queue of pending connections is maintained in the system address space.
 * The listen() call marks the socket as willing to accept connections and initializes the queue.
 **/
//-----------------------------------------------------------------------------------------------------
class cppsocket
{
	private:
		std::string type;				//define if server of client
		int backlog;					// connection queue size
		int sockfd;						// socket descriptor
		int send_recv_sockfd;			// socket descriptor of accepted connection ( session )
		char buffer[1024];

		struct sockaddr_in server;
		struct sockaddr_in client;

		void open();
		void createConnect();

		void bindName();
		void listenSocket();
		void acceptRequest();
		void receive();

	public:

		cppsocket( std::string );
		~cppsocket();

		void clientConnect( unsigned short int , char * );
		void serverConnect( unsigned short int , int );
		void receiveMsg();
		void sendMsg(char *);

		void closeSocket();
		void closeSession();

};
#endif /* CPPSOCKET_H_ */
