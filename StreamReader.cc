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
		printf("[KPI::StreamReader]:Constructing ...\n");
		qballData = qballData_p;
		clientSocket = cSocket_p;
	}

	/**-----------------------------------------------------------------------------------------
	 * Destructor
	 * -----------------------------------------------------------------------------------------*/
	StreamReader::~StreamReader()
	{
		printf("[KPI::StreamReader]:Destroying ...\n");
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
				printf("[KPI::StreamReader_ERROR]:Failed to receive a timer pulse\n");
			else
			{
				printf("\n[KPI::StreamReader]:Timer pulse %d received\n",  ++counter);
				clientSocket->receiveMsg();


				double* data = clientSocket->getData();
				for(unsigned int i = 0; i < sizeof(data); i++)
					printf("%.2f, ", data[i]);
			}
		}

		printf("\n[KPI::StreamReader]:Max counter reached\n");
		return NULL;
	}
