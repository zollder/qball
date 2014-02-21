
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

#include "StreamServer.h"
#include "StreamClient.h"

//void * Sender(void* arg)
//{
//	double msgToSend[3] = {1.1, 2.2, 3.3};
//	cout << "[SENDER]This is Client" << endl;
//	CSocket senderSocket;
//	senderSocket.connectSocket(2000, "127.0.0.1");
//	senderSocket.sendMsg(msgToSend);
//	//delay(1000);
//	senderSocket.receiveMsg2();
//	cout << "[SENDER]:Client done." << endl;
//	sleep(1);
//	return 0;
//}
//
//
//void * Receiver(void* arg)
//{
//	double msgToSend[3] = {3.3, 2.2, 1.1};
//	cout << "[RECEIVER]This is Server" << endl;
//	CSocket receiverSocket;
//	receiverSocket.bindName(2000);
//	receiverSocket.listenSocket(1);
//	receiverSocket.acceptRequest();
//	delay(1500);
//	receiverSocket.receiveMsg();
//	receiverSocket.sendMsg(msgToSend);
//	cout << "[RECEIVER]:Server done" << endl;
//	sleep(1);
//	return 0;
//}


int main(int argc, char *argv[])
{
	unsigned short int port = 2000;
	char address[] = "127.0.0.1";
	double interval = 1;

	StreamServer* streamServer = new StreamServer(port, address, interval);
	StreamClient* streamClient = new StreamClient(port, address, interval);

	streamServer->start();
	streamClient->start();

	return EXIT_SUCCESS;
}
