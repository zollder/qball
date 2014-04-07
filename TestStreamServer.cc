#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "TestStreamServer.h"

//---------------------------------------------------------------------------------------------
// TestTestStreamServer implementation.
//---------------------------------------------------------------------------------------------

	/**-----------------------------------------------------------------------------------------
	 * Constructor
	 * -----------------------------------------------------------------------------------------*/
	TestStreamServer::TestStreamServer(unsigned short int hostPort, char* hostAddress, double timeInterval)
	{
		printf("[KPI::TESTSTREAMSERVER]:Constructing ...\n");

		setPort(hostPort);
		setAddress(hostAddress);
		setTimeInterval(timeInterval);

		// instantiate objects
		serverSocket = new CSocket("TESTSTREAMSERVER");
		streamWriter = new StreamWriter(serverSocket);
		streamWriterTimer = new PulseTimer(getTimeInterval(), streamWriter->getChannelId());
	}

	/**-----------------------------------------------------------------------------------------
	 * Destructor
	 * -----------------------------------------------------------------------------------------*/
	TestStreamServer::~TestStreamServer()
	{
		printf("[KPI::TESTSTREAMSERVER]:Destroying ...\n");

		delete serverSocket;
		delete streamWriter;
		delete streamWriterTimer;
	}
	/**-----------------------------------------------------------------------------------------
	 * Prepares and starts the server:
	 * -----------------------------------------------------------------------------------------*/
	void TestStreamServer::start()
	{
		serverSocket->serverConnect( getPort(), 1 );
		streamWriter->start();
		streamWriterTimer->start();
	}

	/**-----------------------------------------------------------------------------------------
	 * Stops and cleans up the server:
	 * -----------------------------------------------------------------------------------------*/
	void TestStreamServer::stop()
	{
		streamWriter->join();
		streamWriterTimer->stop();
	}

	/**-----------------------------------------------------------------------------------------
	 * Server port.
	 * -----------------------------------------------------------------------------------------*/
	void TestStreamServer::setPort(unsigned short int port)
	{
		this->serverPort = port;
	}

	unsigned short int TestStreamServer::getPort()
	{
		return serverPort;
	}

	/**-----------------------------------------------------------------------------------------
	 * Server IP address.
	 * -----------------------------------------------------------------------------------------*/
	void TestStreamServer::setAddress(char* address)
	{
		strcpy(this->serverAddress, address);
	}

	char* TestStreamServer::getAddress()
	{
		return serverAddress;
	}

	/**-----------------------------------------------------------------------------------------
	 * Pulse timer interval.
	 * -----------------------------------------------------------------------------------------*/
	void TestStreamServer::setTimeInterval(double interval)
	{
		this->timeInterval = interval;
	}

	double TestStreamServer::getTimeInterval()
	{
		return timeInterval;
	}
