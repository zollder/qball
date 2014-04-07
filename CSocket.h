#ifndef CSOCKET_H_
#define CSOCKET_H_
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
class CSocket
{
	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	public:

		CSocket( std::string );
		~CSocket();

		void clientConnect( unsigned short int , char * );
		void serverConnect( unsigned short int , int );

		void acceptRequest( std::string );
		void receiveMsg();
		void sendMsg(double *);
		double* getData();

	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	private:

		std::string type;				// define if server of client
		int backlog;					// connection queue size
		int sockfd;						// socket descriptor
		int send_recv_sockfd;			// socket descriptor of accepted connection ( session )

		const static unsigned int bufferSize = 8;
		double buffer[bufferSize];

		struct sockaddr_in server;
		struct sockaddr_in client;

		void open();
		void createConnect( unsigned short int&, char* );
		void bindName( unsigned short int );
		void listenSocket(int);

		void receive();
		void closeSocket();
		void closeSession();

};
#endif /* CSocket_H_ */
