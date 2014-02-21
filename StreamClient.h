#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "Mutex.h"
#include "CSocket.h"
#include "QballData.h"
#include "StreamReader.h"
#include "PulseTimer.h"

#ifndef streamclient_h
#define streamclient_h

//-----------------------------------------------------------------------------------------
// StreamClient interface.
//-----------------------------------------------------------------------------------------
class StreamClient
{
		Mutex mutex;

	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		StreamClient(unsigned short int port, char* address, double interval);

		// destructor
		~StreamClient();

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
		char getTimeInterval();

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

		CSocket* clientSocket;
		QballData* qballData;
		StreamReader* streamReader;
		PulseTimer* streamReaderTimer;
};

#endif
