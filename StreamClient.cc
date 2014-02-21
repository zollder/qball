#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "StreamClient.h"
#include "StreamClient.h"

//---------------------------------------------------------------------------------------------
// StreamClient subclass implementation.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	StreamClient::StreamClient(unsigned short int hostPort, char* hostAddress, double timeInterval)
	{
		printf("Constructing StreamClient ...\n");

		setPort(hostPort);
		setAddress(hostAddress);
		setTimeInterval(timeInterval);

		// instantiate objects
		clientSocket = new CSocket();
		qballData = new QballData();
		streamReader = new StreamReader(mutex, qballData, clientSocket);
		streamReaderTimer = new PulseTimer(getTimeInterval(), streamReader->getChannelId());
	}

	/**-----------------------------------------------------------------------------------------
	 * Destructor
	-----------------------------------------------------------------------------------------*/
	StreamClient::~StreamClient()
	{
		printf("Destroying StreamClient ...\n");

		delete clientSocket;
		delete qballData;
		delete streamReader;
		delete streamReaderTimer;
	}

	/**-----------------------------------------------------------------------------------------
	 * Sets server port.
	-----------------------------------------------------------------------------------------*/
	void StreamClient::setPort(unsigned short int port)
	{
		serverPort = port;
	}

	/**-----------------------------------------------------------------------------------------
	 * Sets server IP address.
	-----------------------------------------------------------------------------------------*/
	void StreamClient::setAddress(char* address)
	{
		strcpy(this->serverAddress, address);
	}

	/**-----------------------------------------------------------------------------------------
	 * Sets pulse timer interval.
	-----------------------------------------------------------------------------------------*/
	void StreamClient::setTimeInterval(double interval)
	{
		timeInterval = interval;
	}

	/**-----------------------------------------------------------------------------------------
	 * Returns server port.
	-----------------------------------------------------------------------------------------*/
	unsigned short int StreamClient::getPort()
	{
		return serverPort;
	}

	/**-----------------------------------------------------------------------------------------
	 * Returns server IP address.
	-----------------------------------------------------------------------------------------*/
	char* StreamClient::getAddress()
	{
		return serverAddress;
	}

	/**-----------------------------------------------------------------------------------------
	 * Returns pulse timer interval.
	-----------------------------------------------------------------------------------------*/
	char StreamClient::getTimeInterval()
	{
		return timeInterval;
	}

	/**-----------------------------------------------------------------------------------------
	 * Prepares and starts the client:
	 * - connects to remote server;
	 * - starts StreamReader thread;
	 * - enables pulse timer;
	-----------------------------------------------------------------------------------------*/
	void StreamClient::start()
	{
		clientSocket->connectSocket(getPort(), getAddress());
		streamReader->start();
		streamReaderTimer->start();
	}

	/**-----------------------------------------------------------------------------------------
	 * Stops and cleans up the client:
	 * - closes the socket session;
	 * - stops (joins) StreamReader thread;
	 * - stops pulse timer;
	-----------------------------------------------------------------------------------------*/
	void StreamClient::stop()
	{
		clientSocket->closeSession();
		streamReader->join();
		streamReaderTimer->stop();
	}
