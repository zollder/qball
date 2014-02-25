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
	StreamWriter::StreamWriter(Mutex& mutex_r, Cppsocket* sSocket_p) : BaseThread(mutex_r)
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
		serverSocket->acceptRequest( "STREAMWRITER" );

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
				printf("[KPI::STREAMWRITER_ERROR]:Failed to receive display pulse\n");
			}
			else
			{
				printf("\n[KPI::STREAMWRITER]:Timer pulse %d received, sending data ...\n",  ++counter);

				serverSocket->sendMsg(writerBuffer);
				// change array values
				for (int i = 0; i < 3; i++)
					writerBuffer[i] = writerBuffer[i] + 1;
			}
		}
		printf("\n[KPI::STREAMWRITER]:Max counter reached\n");

		return NULL;
	}
