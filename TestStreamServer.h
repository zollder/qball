#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "CSocket.h"
#include "StreamWriter.h"
#include "PulseTimer.h"

#ifndef teststreamserver_h
#define teststreamserver_h

//-----------------------------------------------------------------------------------------
// TestStreamServer interface.
//-----------------------------------------------------------------------------------------
class TestStreamServer
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		TestStreamServer(unsigned short int port, char* address, double interval);

		// destructor
		~TestStreamServer();

		// sets server port
		void setPort(unsigned short int port);

		// sets server IP address
		void setAddress(char* address);

		// sets pulse timer interval
		void setTimeInterval(double interval);

		// returns server port
		unsigned short int getPort();

		// returns server port
		char* getAddress();

		// returns pulse timer interval
		double getTimeInterval();

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
		double timeInterval;

		CSocket* serverSocket;
		StreamWriter* streamWriter;
		PulseTimer* streamWriterTimer;
};

#endif
