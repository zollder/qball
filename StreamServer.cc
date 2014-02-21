#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "StreamServer.h"
#include "StreamServer.h"

//---------------------------------------------------------------------------------------------
// StreamServer subclass implementation.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	StreamServer::StreamServer(unsigned short int hostPort, char hostAddress, double timeInterval)
	{
		printf("Constructing StreamServer ...\n");

		setPort(hostPort);
		setAddress(hostAddress);
		setTimeInterval(timeInterval);

		// instantiate objects
		serverSocket = new CSocket();
		streamWriter = new StreamWriter(mutex, serverSocket);
		streamWriterTimer = new PulseTimer(getTimeInterval(), streamWriter->getChannelId());
	}

	/**-----------------------------------------------------------------------------------------
	 * Destructor
	-----------------------------------------------------------------------------------------*/
	StreamServer::~StreamServer()
	{
		printf("Destroying StreamServer ...\n");

		delete serverSocket;
		delete streamWriter;
		delete streamWriterTimer;
	}

	/**-----------------------------------------------------------------------------------------
	 * Sets server port.
	-----------------------------------------------------------------------------------------*/
	void StreamServer::setPort(unsigned short int port)
	{
		serverPort = port;
	}

	/**-----------------------------------------------------------------------------------------
	 * Sets server IP address.
	-----------------------------------------------------------------------------------------*/
	void StreamServer::setAddress(char address)
	{
		serverAddress = address;
	}

	/**-----------------------------------------------------------------------------------------
	 * Sets pulse timer interval.
	-----------------------------------------------------------------------------------------*/
	void StreamServer::setTimeInterval(double interval)
	{
		timeInterval = interval;
	}

	/**-----------------------------------------------------------------------------------------
	 * Returns server port.
	-----------------------------------------------------------------------------------------*/
	unsigned short int StreamServer::getPort()
	{
		return serverPort;
	}

	/**-----------------------------------------------------------------------------------------
	 * Returns server IP address.
	-----------------------------------------------------------------------------------------*/
	char* StreamServer::getAddress()
	{
		return &serverAddress;
	}

	/**-----------------------------------------------------------------------------------------
	 * Returns pulse timer interval.
	-----------------------------------------------------------------------------------------*/
	char StreamServer::getTimeInterval()
	{
		return timeInterval;
	}

	/**-----------------------------------------------------------------------------------------
	 * Prepares and starts the server:
	-----------------------------------------------------------------------------------------*/
	void StreamServer::start()
	{
		serverSocket->bindName(getPort());
		streamWriter->start();
		streamWriterTimer->start();
	}

	/**-----------------------------------------------------------------------------------------
	 * Stops and cleans up the server:
	-----------------------------------------------------------------------------------------*/
	void StreamServer::stop()
	{
		serverSocket->closeSession();
		serverSocket->closeSocket();
		streamWriter->join();
		streamWriterTimer->stop();
	}
