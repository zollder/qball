#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "StreamClientThread.h"

//---------------------------------------------------------------------------------------------
// StreamClientThread subclass implementation.
//---------------------------------------------------------------------------------------------

	/**-----------------------------------------------------------------------------------------
	 * Constructor
	 * -----------------------------------------------------------------------------------------*/
	StreamClientThread::StreamClientThread(QballData* qballData_p, CSocket* cSocket_p)
	{
		printf("[KPI::STREAMCLIENTTHREAD]:Initializing ...\n");
		qballData = qballData_p;
		clientSocket = cSocket_p;
	}

	/**-----------------------------------------------------------------------------------------
	 * Destructor
	 * -----------------------------------------------------------------------------------------*/
	StreamClientThread::~StreamClientThread()
	{
		printf("[KPI::STREAMCLIENTTHREAD]:Destroying ...\n");
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
				printf("[KPI::STREAMCLIENTTHREAD_ERROR]:Failed to receive a timer pulse\n");
			else
			{
				printf("\n[KPI::STREAMCLIENTTHREAD]:Timer pulse %d received\n",  ++counter);
				clientSocket->receiveMsg();


				double* data = clientSocket->getData();
				for(unsigned int i = 0; i < 12; i++)
					printf("%.2f, ", data[i]);
			}
		}

		printf("\n[KPI::STREAMCLIENTTHREAD]:Max counter reached\n");
		return NULL;
	}
