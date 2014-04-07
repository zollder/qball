#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "TestStreamClient.h"

//---------------------------------------------------------------------------------------------
// TestStreamClient implementation.
//---------------------------------------------------------------------------------------------

	/**-----------------------------------------------------------------------------------------
	 * Constructor
	 *-----------------------------------------------------------------------------------------*/
	TestStreamClient::TestStreamClient(unsigned short int port, char* address, double interval)
	{
		printf("[KPI::TESTSTREAMCLIENT]:Initializing ...\n");

		setPort(port);
		setAddress(address);

		// instantiate objects
		clientSocket = new CSocket("TESTSTREAMCLIENT");
		testClientThread = new TestClientThread(clientSocket);
		testStreamTimer = new PulseTimer(interval, testClientThread->getChannelId());
	}

	/**-----------------------------------------------------------------------------------------
	 * Destructor
	 * -----------------------------------------------------------------------------------------*/
	TestStreamClient::~TestStreamClient()
	{
		printf("[KPI::TESTSTREAMCLIENT]:Destroying ...\n");

		delete clientSocket;
		delete testClientThread;
		delete testStreamTimer;
	}

	/**-----------------------------------------------------------------------------------------
	 * Prepares and starts the client:
	 * - connects to remote server;
	 * - starts StreamReader thread;
	 * - enables pulse timer;
	 * -----------------------------------------------------------------------------------------*/
	void TestStreamClient::start()
	{
		clientSocket->clientConnect(getPort(), getAddress());
		testClientThread->start();
		testStreamTimer->start();
	}

	/**-----------------------------------------------------------------------------------------
	 * Stops and cleans up the client:
	 * - closes the socket session;
	 * - stops (joins) StreamReader thread;
	 * - stops pulse timer;
	 * -----------------------------------------------------------------------------------------*/
	void TestStreamClient::stop()
	{
		testClientThread->join();
		testStreamTimer->stop();
	}

	/**-----------------------------------------------------------------------------------------
	 * Server port.
	 * -----------------------------------------------------------------------------------------*/
	void TestStreamClient::setPort(unsigned short int port)
	{
		this->serverPort = port;
	}

	unsigned short int TestStreamClient::getPort()
	{
		return serverPort;
	}

	/**-----------------------------------------------------------------------------------------
	 * Server IP address.
	 * -----------------------------------------------------------------------------------------*/
	void TestStreamClient::setAddress(char* address)
	{
		strcpy(this->serverAddress, address);
	}

	char* TestStreamClient::getAddress()
	{
		return serverAddress;
	}
