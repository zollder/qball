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
	cout << "This is sender." << endl;
	csocket senderSocket;
	senderSocket.connectSocket(2000, "127.0.0.1");
	senderSocket.sendMsg("message from client");
	delay(1000);
	senderSocket.receiveMsg();
	cout << "Server done." << endl;
	sleep(1);
	return 0;
}


void * Receiver(void* arg)
{
	cout << "This is receiver." << endl;
	csocket receiverSocket;
	receiverSocket.bindName(2000);
	receiverSocket.listenSocket(1);
	receiverSocket.acceptRequest();
	delay(500);
	receiverSocket.receiveMsg();
	receiverSocket.sendMsg("message from server");
	cout << "Client done" << endl;
	sleep(1);
	return 0;
}


int main(int argc, char *argv[])
{
	pthread_t sender_ID, receiver_ID;

	pthread_create(&receiver_ID , NULL, Receiver, NULL);
	pthread_create(&sender_ID , NULL, Sender, NULL);

	pthread_join(sender_ID, NULL);
	pthread_join(receiver_ID, NULL);

	return EXIT_SUCCESS;
}
