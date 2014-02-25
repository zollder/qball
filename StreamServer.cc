#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "StreamServer.h"
#include "StreamServer.h"

//---------------------------------------------------------------------------------------------
// StreamServer subclass implementation.
//---------------------------------------------------------------------------------------------

	/**-----------------------------------------------------------------------------------------
	 * Constructor
	 * -----------------------------------------------------------------------------------------*/
	StreamServer::StreamServer(unsigned short int hostPort, char* hostAddress, double timeInterval)
	{
		printf("[KPI::STREAMSERVER]:Constructing ...\n");

		setPort(hostPort);
		setAddress(hostAddress);
		setTimeInterval(timeInterval);

		// instantiate objects
		serverSocket = new Cppsocket("SERVER");
		streamWriter = new StreamWriter(mutex, serverSocket);
		streamWriterTimer = new PulseTimer(getTimeInterval(), streamWriter->getChannelId());
	}

	/**-----------------------------------------------------------------------------------------
	 * Destructor
	 * -----------------------------------------------------------------------------------------*/
	StreamServer::~StreamServer()
	{
		printf("[KPI::STREAMSERVER]:Destroying ...\n");

		delete serverSocket;
		delete streamWriter;
		delete streamWriterTimer;
	}
	/**-----------------------------------------------------------------------------------------
	 * Prepares and starts the server:
	 * -----------------------------------------------------------------------------------------*/
	void StreamServer::start()
	{
		serverSocket->serverConnect( getPort(), 1 );
		streamWriter->start();
		streamWriterTimer->start();
	}

	/**-----------------------------------------------------------------------------------------
	 * Stops and cleans up the server:
	 * -----------------------------------------------------------------------------------------*/
	void StreamServer::stop()
	{
		streamWriter->join();
		streamWriterTimer->stop();
		//serverSocket->~Cppsocket();
	}
	/**-----------------------------------------------------------------------------------------
	 *
	 * 						****		SETTERS AND GETTERS		****
	 * -----------------------------------------------------------------------------------------*/

	/**-----------------------------------------------------------------------------------------
	 * Server port.
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
	 * Server IP address.
	 * -----------------------------------------------------------------------------------------*/
	void StreamServer::setAddress(char* address)
	{
		strcpy(this->serverAddress, address);
	}

	char* StreamServer::getAddress()
	{
		return serverAddress;
	}

	/**-----------------------------------------------------------------------------------------
	 * Pulse timer interval.
	 * -----------------------------------------------------------------------------------------*/
	void StreamServer::setTimeInterval(double interval)
	{
		this->timeInterval = interval;
	}

	char StreamServer::getTimeInterval()
	{
		return timeInterval;
	}
