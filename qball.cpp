//=========================================================================== //=========================================================================== //=========================================================================== //===========================================================================
#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <sync.h>
#include <sys/siginfo.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <sys/syspage.h>
#include "csocket.h"


void * Sender(void* arg)
{
	csocket senderSocket;
	char buff[100];
	//cout<<"This is sender."<<endl;
	senderSocket.connectSocket(2000, "127.0.0.1");
	//s.connect(2000,"localhost");
	senderSocket.sendMsg("This is sent by sender.");
	senderSocket.receiveMsg();
	cout<<buff<<endl;
	cout<<"Done from sender."<<endl;
	return 0;
}


void * Receiver(void* arg)
{
	csocket receiverSocket;
	//s.connect(2000,"127.0.0.1");
	receiverSocket.bindName(2000);
	receiverSocket.listenSocket(1);
	receiverSocket.acceptRequest();
	receiverSocket.receiveMsg();
	//cout<<"from Receiver (buffer content): "<<buff<<endl;
	char buff[100];
	receiverSocket.sendMsg("This is sent by receiver.");
	// prompt a message
	cout<<"Done from receiver."<<endl;
	sleep(1);
	return 0;
}


int main(int argc, char *argv[])
{
	pthread_t sender_ID,receiver_ID;

	pthread_create(&receiver_ID , NULL, Receiver, NULL);
	delay(500);
	pthread_create(&sender_ID , NULL, Sender, NULL);

	pthread_join(sender_ID, NULL);
	pthread_join(receiver_ID, NULL);

	return EXIT_SUCCESS;
}
