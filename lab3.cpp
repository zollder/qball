/*
 * lab3.cpp
 *
 *  Created on: 2014-02-15
 *      Author: eugen, oleg
 */
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <pthread.h>
#include <sync.h>
#include <unistd.h>
#include <sys/siginfo.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <sys/syspage.h>
#include "cppsocket.h"


#include <unistd.h>


void * client(void* arg)
{
	cppsocket client("Client");

	client.clientConnect(18000, "127.0.0.1");
	client.sendMsg("message from client");
	client.receiveMsg();

	sleep(1);
}

void * server(void* arg)
{
	cppsocket server("Server");
	server.serverConnect( 18000 , 1 );
	delay(1500);
	server.receiveMsg();
	server.sendMsg("message from server");

	sleep(1);
}

int main(int argc, char *argv[])
{
	pthread_t client_ID, server_ID;

	pthread_create(&server_ID , NULL, server, NULL);
	pthread_create(&client_ID , NULL, client, NULL);

	pthread_join(client_ID, NULL);
	pthread_join(server_ID, NULL);

	return EXIT_SUCCESS;
}
