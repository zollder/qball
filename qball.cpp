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

#include <hash_map>

#include "StreamServer.h"
#include "StreamClient.h"
#include "Cppsocket.h"

using namespace std;

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





/*	struct position
	{
		double x;
		double y;
		double z;
	};
	position p;
	p.x=5;
	p.y=10;
	p.z=15;

 	 hash_map < const char* , position> m;
   	   m["Accelerator"] = p;
   	   m["foo"] = 43;

    cout << m["Accelerator"].x << endl;
*/
	return EXIT_SUCCESS;
}
