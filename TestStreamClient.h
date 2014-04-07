#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "CSocket.h"
#include "TestClientThread.h"
#include "PulseTimer.h"

#ifndef teststreamclient_h
#define teststreamclient_h

//-----------------------------------------------------------------------------------------
/** TestStreamClient interface. */
//-----------------------------------------------------------------------------------------
class TestStreamClient
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		TestStreamClient(unsigned short int port, char* address, double interval);

		// destructor
		~TestStreamClient();

		// sets server port
		void setPort(unsigned short int port);

		// sets server IP address
		void setAddress(char* address);

		// returns server port
		unsigned short int getPort();

		// returns server port
		char* getAddress();

		// enables and starts the client
		void start();

		// stops and cleans the client
		void stop();

	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
    private:
		unsigned short int serverPort;
		char serverAddress[100];

		CSocket* clientSocket;
		TestClientThread* testClientThread;
		PulseTimer* testStreamTimer;
};

#endif
