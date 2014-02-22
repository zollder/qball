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
	StreamWriter::StreamWriter(Mutex& mutex_r, CSocket* sSocket_p) : BaseThread(mutex_r)
	{
		printf("Constructing StreamWriter ...\n");
		serverSocket = sSocket_p;
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
		serverSocket->listenSocket(1);
		serverSocket->acceptRequest();
		printf("[StreamWriter] Request accepted. \n");

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
				printf("\n[StreamWriter] Timer pulse %d received, sending data ...\n",  counter+1);

				serverSocket->sendMsg(writerBuffer);

				// change array values
				for (int i = 0; i < 3; i++)
					writerBuffer[i] = writerBuffer[i] + 1;

		    	counter++;
			}
		}

		printf("\n\n[StreamWriter] Max counter reached.\n");

		return NULL;
	}
