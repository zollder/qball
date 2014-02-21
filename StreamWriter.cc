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
	StreamWriter::StreamWriter(CSocket* cSocket_p) : BaseThread(cSocket_p)
	{
		printf("Constructing StreamWriter ...\n");
	}

	//-----------------------------------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------------------------------
	StreamWriter::~StreamWriter()
	{
		printf("Destroying StreamWriter ...\n");
	}

	//-----------------------------------------------------------------------------------------
	// Overrides BaseThread's run() method
	//-----------------------------------------------------------------------------------------
	void* StreamWriter::run()
	{
		// dummy buffer
		string buffer[8];

		double writerBuffer[3] = {1.1, 1.2, 1.3};

		int counter = 0;
		while(counter < 10)
		{
			// wait for the pulse to fire
			int receivedPulse = MsgReceivePulse(getChannelId(), &buffer, sizeof(buffer), NULL);

			if (receivedPulse != 0)
			{
				printf("[StreamWriter] Error receiving display pulse\n");
			}
			else
			{
				printf("\n[StreamWriter] Timer pulse %d received, sending message ...\n",  counter+1);

				clientSocket->sendMsg(&writerBuffer);

				// change array values
				for (int i = 0; i < 3; i++)
					writerBuffer[i] = writerBuffer[i] + 1;

		    	counter++;
			}
		}

		printf("\n[StreamWriter] Max counter reached.\n");

		return NULL;
	}
