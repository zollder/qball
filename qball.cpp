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
#include "cjoystick.h"

using namespace std;

int main(int argc, char *argv[])
{
	/* lab 3
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
	*/

	Cjoystick joystick;

	 if( !joystick.is_status_ok() )
	 {
		 printf("%s\n", joystick.get_status_msg());
		 return EXIT_FAILURE;
	 }

	 sleep(2);
	 joystick.print_device_info(3);

	 int t = 20;
	 while( --t )
	 {
	 /* another option of printing.
	  * fprintf(stdout, "\nx: %03d y: %03d z: %03d rx: %03d ry: %03d rz: %03d",
	   joystick.getX(), joystick.getY(), joystick.getZ(),joystick.getRX(), joystick.getRY(),joystick.getRZ() )*/

		 printf("x: %d y: %d z: %d rx: %d ry: %d rz: %d\n",
				 joystick.getX(), joystick.getY(), joystick.getZ(),joystick.getRX(), joystick.getRY(),joystick.getRZ() );

		 sleep(1);

		 if( !joystick.is_status_ok() )
			 return -1;
	 }

	return EXIT_SUCCESS;
}
//TODO incorportate Cjoystick into streamclient

