#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "StreamClient.h"

//---------------------------------------------------------------------------------------------
// StreamClient implementation.
//---------------------------------------------------------------------------------------------

	/**-----------------------------------------------------------------------------------------
	 * Constructor
	 *-----------------------------------------------------------------------------------------*/
	StreamClient::StreamClient(unsigned short int port, char* address, double interval, QballData* data)
	{
		printf("[KPI::STREAMCLIENT]:Initializing ...\n");

		setPort(port);
		setAddress(address);

		// instantiate objects
		clientSocket = new CSocket("CLIENT");
		streamClientThread = new StreamClientThread(data, clientSocket);
		streamReaderTimer = new PulseTimer(interval, streamClientThread->getChannelId());
	}

	/**-----------------------------------------------------------------------------------------
	 * Destructor
	 * -----------------------------------------------------------------------------------------*/
	StreamClient::~StreamClient()
	{
		printf("[KPI::STREAMCLIENT]:Destroying ...\n");

		delete clientSocket;
		delete streamClientThread;
		delete streamReaderTimer;
	}

	/**-----------------------------------------------------------------------------------------
	 * Prepares and starts the client:
	 * - connects to remote server;
	 * - starts StreamReader thread;
	 * - enables pulse timer;
	 * -----------------------------------------------------------------------------------------*/
	void StreamClient::start()
	{
		clientSocket->clientConnect(getPort(), getAddress());
		streamClientThread->start();
		streamReaderTimer->start();
	}

	/**-----------------------------------------------------------------------------------------
	 * Stops and cleans up the client:
	 * - closes the socket session;
	 * - stops (joins) StreamReader thread;
	 * - stops pulse timer;
	 * -----------------------------------------------------------------------------------------*/
	void StreamClient::stop()
	{
		streamClientThread->join();
		streamReaderTimer->stop();
	}


	/**-----------------------------------------------------------------------------------------
	 * SETTERS AND GETTERS
	 * -----------------------------------------------------------------------------------------*/

	/**-----------------------------------------------------------------------------------------
	 * Server port.
	 * -----------------------------------------------------------------------------------------*/
	void StreamClient::setPort(unsigned short int port)
	{
		this->serverPort = port;
	}

	unsigned short int StreamClient::getPort()
	{
		return serverPort;
	}

	/**-----------------------------------------------------------------------------------------
	 * Server IP address.
	 * -----------------------------------------------------------------------------------------*/
	void StreamClient::setAddress(char* address)
	{
		strcpy(this->serverAddress, address);
	}

	char* StreamClient::getAddress()
	{
		return serverAddress;
	}
