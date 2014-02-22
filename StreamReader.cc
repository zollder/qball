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
	StreamReader::StreamReader(Mutex& mutex_r, QballData* qballData_p, CSocket* cSocket_p) : BaseThread(mutex_r)
	{
		printf("Constructing StreamReader ...\n");
		qballData = qballData_p;
		clientSocket = cSocket_p;
	}

	/**-----------------------------------------------------------------------------------------
	 * Destructor
	 * -----------------------------------------------------------------------------------------*/
	StreamReader::~StreamReader()
	{
		printf("Destroying StreamReader ...\n");
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
				printf("[StreamReader] Error receiving timer pulse.\n");
			else
			{
				printf("\n[StreamReader] Timer pulse %d received, receiving data ...\n",  counter+1);
				clientSocket->receiveMsg();

				printf("[CLIENT] Received data: ");
				double* data = clientSocket->getData();
				for(unsigned int i = 0; i < sizeof(data); i++)
					printf("%.2f, ", data[i]);

		    	counter++;
			}
		}

		printf("\n\n[StreamReader] Max counter reached.\n");
		return NULL;
	}
