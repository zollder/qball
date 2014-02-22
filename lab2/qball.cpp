
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
<<<<<<< HEAD:lab2/qball.cpp
#include "csocket.h"

void * Sender(void* arg)
{
	cout << "[SENDER]This is Client" << endl;
	csocket senderSocket;
	senderSocket.connectSocket(18000, "127.0.0.1");
	senderSocket.sendMsg("message from client");
	//delay(1000);
	senderSocket.receiveMsg2();
	cout << "[SENDER]:Client done." << endl;
	sleep(1);
	return 0;
}


void * Receiver(void* arg)
{
	cout << "[RECEIVER]This is Server" << endl;
	csocket receiverSocket;
	receiverSocket.bindName(18000);
	receiverSocket.listenSocket(1);
	printf("HERE\n");
	receiverSocket.acceptRequest();
	delay(1500);
	receiverSocket.receiveMsg();
	receiverSocket.sendMsg("message from server");
	cout << "[RECEIVER]:Server done" << endl;
	sleep(1);
	return 0;
}
=======
>>>>>>> 87117513a757801ddbd979ab0322cf59a8130022:qball.cpp

#include "StreamServer.h"
#include "StreamClient.h"

<<<<<<< HEAD:lab2/qball.cpp
//int main(int argc, char *argv[])
//{
//	pthread_t sender_ID, receiver_ID;
//
//	pthread_create(&receiver_ID , NULL, Receiver, NULL);
//	pthread_create(&sender_ID , NULL, Sender, NULL);
//
//	pthread_join(sender_ID, NULL);
//	pthread_join(receiver_ID, NULL);
//
//	return EXIT_SUCCESS;
//}

=======
int main(int argc, char *argv[])
{
	unsigned short int port = 2000;
	char address[] = "127.0.0.1";
	double interval = 1.5;

	StreamServer* streamServer = new StreamServer(port, address, interval);
	StreamClient* streamClient = new StreamClient(port, address, interval);

	streamServer->start();
	streamClient->start();
	streamClient->stop();
	streamServer->stop();

	printf("Main thread completed. Cleaning-up ... \n");
	delete streamClient;
	delete streamServer;

	return EXIT_SUCCESS;
}
>>>>>>> 87117513a757801ddbd979ab0322cf59a8130022:qball.cpp
