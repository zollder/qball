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
#include "Cppsocket.h"

void * client(void* arg)
{
	Cppsocket client("Client");
	client.clientConnect(18000, "127.0.0.1");
	delay(500);
	client.sendMsg("message from client");
	client.receiveMsg();

	sleep(1);
}

void * server(void* arg)
{
	Cppsocket server("Server");
	server.serverConnect( 18000 , 1 );
	server.receiveMsg();
	delay(500);
	server.sendMsg("message from server");

	sleep(1);
}

int main(int argc, char *argv[])
{
	/*
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
	*/

	pthread_t client_ID, server_ID;

	pthread_create(&server_ID , NULL, server, NULL);
	delay(500);
	pthread_create(&client_ID , NULL, client, NULL);

	pthread_join(client_ID, NULL);
	pthread_join(server_ID, NULL);


	return EXIT_SUCCESS;
}
