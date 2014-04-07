#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "StreamWriter.h"

//---------------------------------------------------------------------------------------------
// StreamWriter subclass implementation.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	StreamWriter::StreamWriter(CSocket* sSocket_p)
	{
		printf("[KPI::STREAMWRITER]:Initializing ......\n");
		serverSocket = sSocket_p;
	}

	//-----------------------------------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------------------------------
	StreamWriter::~StreamWriter()
	{
		printf("[KPI::STREAMWRITER]:Destroying ...\n");
	}

	//-----------------------------------------------------------------------------------------
	// Overrides BaseThread's run() method
	//-----------------------------------------------------------------------------------------
	void* StreamWriter::run()
	{
		serverSocket->acceptRequest("STREAMWRITER");

		// dummy buffer
		string buffer[8];

		double writerBuffer[dataSize] = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 1.10, 1.11, 1.12};

		int counter = 0;

		while(counter < 10)
		{
			// wait for the pulse to fire
			int receivedPulse = MsgReceivePulse(getChannelId(), &buffer, sizeof(buffer), NULL);

			if (receivedPulse != 0)
				printf("\n[KPI::STREAMWRITER_ERROR]:Failed to receive display pulse.");
			else
			{
				++counter;
				printf("\n[KPI::STREAMWRITER]:Pulse %d received.",  counter);

				serverSocket->sendMsg(writerBuffer);

				// change array values
				for (unsigned int i = 0; i < dataSize; i++)
					writerBuffer[i] = writerBuffer[i] + 1;
			}
		}

		printf("\n[KPI::STREAMWRITER]:Max counter reached.");
		return NULL;
	}
