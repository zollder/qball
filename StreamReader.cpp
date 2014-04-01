#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "StreamReader.h"

//---------------------------------------------------------------------------------------------
// StreamReader subclass implementation.
//---------------------------------------------------------------------------------------------

	/**-----------------------------------------------------------------------------------------
	 * Constructor
	 * -----------------------------------------------------------------------------------------*/
	StreamReader::StreamReader(Mutex& mutex_r, QballData* qballData_p, Cppsocket* cSocket_p) : BaseThread(mutex_r)
	{
		printf("[KPI::STREAMREADER]:Initializing ...\n");
		qballData = qballData_p;
		clientSocket = cSocket_p;
	}

	/**-----------------------------------------------------------------------------------------
	 * Destructor
	 * -----------------------------------------------------------------------------------------*/
	StreamReader::~StreamReader()
	{
		printf("[KPI::STREAMREADER]:Destroying ...\n");
	}

	/**-----------------------------------------------------------------------------------------
	 * Overrides BaseThread's run() method.
	 * Implements StreamReader thread that receives and displays data from the server.
	 * -----------------------------------------------------------------------------------------*/
	void* StreamReader::run()
	{
		// dummy buffer
		string buffer[8];

		int counter = 0;
		while(counter < 10)
		{
			// wait for the pulse to fire
			int receivedPulse = MsgReceivePulse(getChannelId(), &buffer, sizeof(buffer), NULL);

			if (receivedPulse < 0)
				printf("[KPI::STREAMREADER_ERROR]:Failed to receive a timer pulse\n");
			else
			{
				printf("\n[KPI::STREAMREADER]:Timer pulse %d received\n",  ++counter);
				clientSocket->receiveMsg();


				double* data = clientSocket->getData();
				for(unsigned int i = 0; i < 12; i++)
					printf("%.2f, ", data[i]);
			}
		}

		printf("\n[KPI::STREAMREADER]:Max counter reached\n");
		return NULL;
	}
