#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "TestClientThread.h"

//---------------------------------------------------------------------------------------------
// TestClientThread implementation.
//---------------------------------------------------------------------------------------------

	/**-----------------------------------------------------------------------------------------
	 * Constructor
	 * -----------------------------------------------------------------------------------------*/
	TestClientThread::TestClientThread(CSocket* cSocket_p)
	{
		printf("[KPI::TESTCLIENTTHREAD]:Initializing ...\n");
		clientSocket = cSocket_p;

		// create and initialize array
		receivedData = new double[dataSize];
		for(unsigned int i = 0; i < dataSize; i++)
			receivedData[i] = 0;
	}

	/**-----------------------------------------------------------------------------------------
	 * Destructor
	 * -----------------------------------------------------------------------------------------*/
	TestClientThread::~TestClientThread()
	{
		printf("[KPI::TESTCLIENTTHREAD]:Destroying ...\n");
		delete receivedData;
	}

	/**-----------------------------------------------------------------------------------------
	 * Overrides BaseThread's run() method.
	 * Implements TestClientThread thread that receives and displays data from the server.
	 * -----------------------------------------------------------------------------------------*/
	void* TestClientThread::run()
	{
		// dummy buffer
		string buffer[8];

		int counter = 0;
		while(counter < 10)
		{
			// wait for the pulse to fire
			int receivedPulse = MsgReceivePulse(getChannelId(), &buffer, sizeof(buffer), NULL);

			if (receivedPulse < 0)
				printf("\n[KPI::TESTCLIENTTHREAD_ERROR]:Failed to receive a timer pulse.");
			else
			{
				++counter;
				printf("\n[KPI::TESTCLIENTTHREAD]:Timer pulse %d received.",  counter);
				clientSocket->receiveMsg();

				// locally save received data
				for(unsigned int i = 0; i < dataSize; i++)
					receivedData[i] = clientSocket->getData()[i];

				// display saved data
				printf("\n[KPI::TESTCLIENTTHREAD]:Printing ");
				for(unsigned int i = 0; i < dataSize; i++)
					printf("%.2f, ", receivedData[i]);
			}
		}

		printf("\n[KPI::TESTCLIENTTHREAD]:Max counter reached.");
		return NULL;
	}
