#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "CSocket.h"
#include "QballData.h"
#include "StreamClientThread.h"
#include "PulseTimer.h"

#ifndef streamclient_h
#define streamclient_h

//-----------------------------------------------------------------------------------------
// StreamClient interface.
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
/** StreamClient interface.
 *  Wrapper around QBall client services.
 *  Simplifies client start-up routine by instantiating and initializing
 *  CSocket, StreamClientThread and PulseTimer objects in the required sequence.
 *  Is driven by the pulse timer instance with custom time interval.
 */
//-----------------------------------------------------------------------------------------
class StreamClient
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		StreamClient(unsigned short int port, char* address, double interval, QballData* data);

		// destructor
		~StreamClient();

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
		StreamClientThread* streamClientThread;
		PulseTimer* streamReaderTimer;
};

#endif
