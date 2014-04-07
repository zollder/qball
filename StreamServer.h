#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "CSocket.h"
#include "CJoystick.h"
#include "StreamServerThread.h"
#include "PulseTimer.h"

#ifndef streamserver_h
#define streamserver_h

//-----------------------------------------------------------------------------------------
/** StreamServer interface.
 *  Wrapper around Joystick server services.
 *  Creates a server instance responsible for reading joystick data from the shared data
 *  holder instance, accepting connections from and sending control data to remote clients.
 *  Simplifies client start-up routine by instantiating and initializing
 *  CSocket, StreamServerThread and PulseTimer objects according to predefined sequence.
 */
//-----------------------------------------------------------------------------------------
class StreamServer
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		StreamServer(unsigned short int port, char* address, double interval);

		// destructor
		~StreamServer();

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

		CSocket* serverSocket;
		CJoystick* clientJoystick;
		StreamServerThread* streamServerThread;
		PulseTimer* streamServerTimer;
};

#endif
