#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "Mutex.h"
#include "CSocket.h"
#include "StreamWriter.h"
#include "PulseTimer.h"

#ifndef streamserver_h
#define streamserver_h

//-----------------------------------------------------------------------------------------
// StreamServer interface.
//-----------------------------------------------------------------------------------------
class StreamServer
{
	Mutex mutex;

	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		StreamServer(unsigned short int port, char address, double interval);

		// destructor
		~StreamServer();

		// sets server port
		void setPort(unsigned short int port);

		// sets server IP address
		void setAddress(char address);

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
		char serverAddress;
		double timeInterval;

		CSocket* serverSocket;
		StreamWriter* streamWriter;
		PulseTimer* streamWriterTimer;
};

#endif
