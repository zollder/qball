#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "StreamClient.h"
#include "StreamClient.h"

//---------------------------------------------------------------------------------------------
// StreamClient subclass implementation.
//---------------------------------------------------------------------------------------------

	/**-----------------------------------------------------------------------------------------
	 * Constructor
	 *-----------------------------------------------------------------------------------------*/
	StreamClient::StreamClient(unsigned short int hostPort, char* hostAddress, double timeInterval)
	{
		printf("[KPI::STREAMCLIENT]:Initializing ...\n");

		setPort(hostPort);
		setAddress(hostAddress);
		setTimeInterval(timeInterval);

		// instantiate objects
		clientSocket = new CSocket("CLIENT");
		qballData = new QballData();
		streamReader = new StreamReader(mutex, qballData, clientSocket);
		streamReaderTimer = new PulseTimer(getTimeInterval(), streamReader->getChannelId());
	}

	/**-----------------------------------------------------------------------------------------
	 * Destructor
	 * -----------------------------------------------------------------------------------------*/
	StreamClient::~StreamClient()
	{
		printf("[KPI::STREAMCLIENT]:Destroying ...\n");

		delete clientSocket;
		delete qballData;
		delete streamReader;
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
		clientSocket->clientConnect( getPort(), getAddress() );
		streamReader->start();
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
		streamReader->join();
		streamReaderTimer->stop();
		//clientSocket->~CSocket();				NOTE:maybe not necessary
	}

	/**-----------------------------------------------------------------------------------------
	 *
	 * 						****		SETTERS AND GETTERS		****
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

	/**-----------------------------------------------------------------------------------------
	 * Pulse timer interval.
	 * -----------------------------------------------------------------------------------------*/
	void StreamClient::setTimeInterval(double interval)
	{
		this->timeInterval = interval;
	}

	double StreamClient::getTimeInterval()
	{
		return timeInterval;
	}
