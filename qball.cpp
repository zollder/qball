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

#include "TestStreamServer.h"
#include "StreamClient.h"
#include "JoystickClient.h"
#include "CSocket.h"
#include "CJoystick.h"
#include "CJoystick.h"
#include "QballData.h"
#include "JoystickData.h"
#include "QballPrinter.h"
#include "StreamServer.h"
#include "TestStreamClient.h"

using namespace std;

int main(int argc, char *argv[])
{
	//* ====================== Test Joystick read/send ==========================*/

	// NOTE: don't forget to change CSocket buffer size to 8
	// properties
	unsigned short int port = 18000;
	char address[] = "127.0.0.1";
	double interval = 1.5;

	JoystickData* joystickData = new JoystickData();
	JoystickClient* joystickClient = new JoystickClient(joystickData, 1);
	StreamServer* streamServer = new StreamServer(port, address, interval, joystickData);

	TestStreamClient* gballClient = new TestStreamClient(port, address, interval);

	joystickClient->start();
	streamServer->start();
	gballClient->start();
	gballClient->stop();
	streamServer->stop();
	joystickClient->stop();

	printf("\n[KPI::Main Thread]:Completed, Cleaning-up ...\n\n");
	delete joystickData;
	delete joystickClient;
	delete streamServer;
	delete gballClient;

	return EXIT_SUCCESS;

	//* ====================== Test Qball read/print ==========================*/

	// NOTE: don't forget to change CSocket buffer size to 12
	// properties
//	unsigned short int port = 18000;
//	char address[] = "127.0.0.1";
//	double interval = 1.5;
//
//	QballData* qballData = new QballData();
//	QballPrinter* printer = new QballPrinter(qballData, interval);
//	TestStreamServer* testStreamServer = new TestStreamServer(port, address, interval);
//	StreamClient* streamClient = new StreamClient(port, address, interval, qballData);
//
//	printer->start();
//	testStreamServer->start();
//	streamClient->start();
//	streamClient->stop();
//	testStreamServer->stop();
//	printer->stop();
//
//	printf("\n[KPI::Main Thread]:Completed, Cleaning-up ...\n\n");
//	delete qballData;
//	delete printer;
//	delete streamClient;
//	delete testStreamServer;
//
//	return EXIT_SUCCESS;
}
