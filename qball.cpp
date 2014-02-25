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

int main(int argc, char *argv[])
{

	unsigned short int port = 18000;
	char address[] = "127.0.0.1";
	double interval = 1.5;

	StreamServer* streamServer = new StreamServer(port, address, interval);
	StreamClient* streamClient = new StreamClient(port, address, interval);

	streamServer->start();
	streamClient->start();
	streamClient->stop();
	streamServer->stop();

	printf("\n[KPI::Main Thread]:Completed, Cleaning-up ...\n\n");
	delete streamClient;
	delete streamServer;


	return EXIT_SUCCESS;
}
