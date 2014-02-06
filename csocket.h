#ifndef CSOCKET_H
#define CSOCKET_H

#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>

//============================================================================= 
class csocket
{
	private:
		int sockfd;	// socket descriptor 
		int send_recv_sockfd;	// socket descriptor of accepted connection 
		struct sockaddr_in addr;
		struct sockaddr_in client_addr;

	public: 
		unsigned short int port;
		int backlog;	// how many pending connections queue will hold 

		csocket();
		~csocket(); 

		int open();
		int bind(unsigned short int port);
		int connect(unsigned short int HostPort, char * HostIP);
		int listen();
		int accept();
		int send(char * buff, int len);
		int receive(char * buff, int len);
		int close();
		int close_session(); 
}; 

#endif /*CSOCKET_H_*/
