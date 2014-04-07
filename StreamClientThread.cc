#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "StreamClientThread.h"

//---------------------------------------------------------------------------------------------
// StreamClientThread implementation.
//---------------------------------------------------------------------------------------------

	/**-----------------------------------------------------------------------------------------
	 * Constructor
	 * -----------------------------------------------------------------------------------------*/
	StreamClientThread::StreamClientThread(QballData* qballData_p, CSocket* cSocket_p)
	{
		printf("[KPI::STREAMCLIENTTHREAD]:Initializing ...\n");
		qballData = qballData_p;
		clientSocket = cSocket_p;
		// sensorData = new double[dataSize];
	}

	/**-----------------------------------------------------------------------------------------
	 * Destructor
	 * -----------------------------------------------------------------------------------------*/
	StreamClientThread::~StreamClientThread()
	{
		printf("[KPI::STREAMCLIENTTHREAD]:Destroying ...\n");
		// delete sensorData;
	}

	/**-----------------------------------------------------------------------------------------
	 * Overrides BaseThread's run() method.
	 * Implements StreamClientThread thread that receives and displays data from the server.
	 * -----------------------------------------------------------------------------------------*/
	void* StreamClientThread::run()
	{
		// dummy buffer
		string buffer[8];

		int counter = 0;
		while(counter < 10)
		{
			// wait for the pulse to fire
			int receivedPulse = MsgReceivePulse(getChannelId(), &buffer, sizeof(buffer), NULL);

			if (receivedPulse < 0)
				printf("\n[KPI::STREAMCLIENTTHREAD_ERROR]:Failed to receive a timer pulse.");
			else
			{
				++counter;
				printf("\n[KPI::STREAMCLIENTTHREAD]:Pulse %d received.",  counter);
				clientSocket->receiveMsg();

				// save data into the shared QballData instance
				qballData->saveSensorData(clientSocket->getData());
			}
		}

		printf("\n[KPI::STREAMCLIENTTHREAD]:Max counter reached.");
		return NULL;
	}
