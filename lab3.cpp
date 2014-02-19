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
#include <iostream>
char escape;

void * client(void* arg)
{
	cppsocket client("Client");
	client.clientConnect(18000, "127.0.0.1");
	delay(500);
	client.sendMsg("message from client");
	client.receiveMsg();

	sleep(1);
//	while( !flag )
//	{}

}

void * server(void* arg)
{
	cppsocket server("Server");
	server.serverConnect( 18000 , 1 );
	server.receiveMsg();
	delay(500);
	server.sendMsg("message from server");

	sleep(1);
//	while( !flag)
//	{}

}

void * monitor(void* arg)
{
	while( escape != 'q' )
	{
		std::cout << "Command: ";
		std::cin >> escape;
	}
	std::cout << "[KPI::Term]: Exiting" << std::endl;

}


int main(int argc, char *argv[])
{
	escape =0;

	pthread_t client_ID, server_ID,monitor_ID;

	pthread_create(&server_ID , NULL, server, NULL);
	delay(500);
	pthread_create(&client_ID , NULL, client, NULL);
	delay(2000);
	pthread_create(&monitor_ID , NULL, monitor, NULL);

	pthread_join(monitor_ID, NULL);
	pthread_join(client_ID, NULL);
	pthread_join(server_ID, NULL);


	return EXIT_SUCCESS;
}

