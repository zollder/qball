#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "StreamServer.h"

//---------------------------------------------------------------------------------------------
// StreamServer implementation.
//---------------------------------------------------------------------------------------------

	/**-----------------------------------------------------------------------------------------
	 * Constructor
	 * -----------------------------------------------------------------------------------------*/
	StreamServer::StreamServer(unsigned short int port, char* address, double interval, JoystickData* data)
	{
		printf("[KPI::STREAMSERVER]:Constructing ...\n");

		setPort(port);
		setAddress(address);

		// instantiate objects
		serverSocket = new CSocket("STREAMSERVER");
		streamServerThread = new StreamServerThread(data, serverSocket);
		streamServerTimer = new PulseTimer(interval, streamServerThread->getChannelId());
	}

	/**-----------------------------------------------------------------------------------------
	 * Destructor
	 * -----------------------------------------------------------------------------------------*/
	StreamServer::~StreamServer()
	{
		printf("[KPI::STREAMSERVER]:Destroying ...\n");

		delete serverSocket;
		delete streamServerThread;
		delete streamServerTimer;
	}
	/**-----------------------------------------------------------------------------------------
	 * Prepares and starts the server:
	 * -----------------------------------------------------------------------------------------*/
	void StreamServer::start()
	{
		serverSocket->serverConnect(getPort(), 1);
		streamServerThread->start();
		streamServerTimer->start();
	}

	/**-----------------------------------------------------------------------------------------
	 * Stops and cleans up the server:
	 * -----------------------------------------------------------------------------------------*/
	void StreamServer::stop()
	{
		streamServerThread->join();
		streamServerTimer->stop();
	}

	/**-----------------------------------------------------------------------------------------
	 * Server port getter and setter.
	 * -----------------------------------------------------------------------------------------*/
	void StreamServer::setPort(unsigned short int port)
	{
		this->serverPort = port;
	}

	unsigned short int StreamServer::getPort()
	{
		return serverPort;
	}

	/**-----------------------------------------------------------------------------------------
	 * Server IP address getter and setter.
	 * -----------------------------------------------------------------------------------------*/
	void StreamServer::setAddress(char* address)
	{
		strcpy(this->serverAddress, address);
	}

	char* StreamServer::getAddress()
	{
		return serverAddress;
	}
