#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "StreamServerThread.h"

//---------------------------------------------------------------------------------------------
// StreamServerThread subclass implementation.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	StreamServerThread::StreamServerThread(JoystickData* data_p, CSocket* sSocket_p)
	{
		printf("[KPI::STREAMSERVERTHREAD]:Initializing ......\n");
		serverSocket = sSocket_p;
		joystickData = data_p;

		// create array and initialize its members
		controlData = new double[dataSize];
		for (unsigned int i = 0; i < dataSize; i++)
			controlData[i] = 0;
	}

	//-----------------------------------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------------------------------
	StreamServerThread::~StreamServerThread()
	{
		printf("[KPI::STREAMSERVERTHREAD]:Destroying ...\n");
		delete controlData;
	}

	//-----------------------------------------------------------------------------------------
	// Overrides BaseThread's run() method
	//-----------------------------------------------------------------------------------------
	void* StreamServerThread::run()
	{
		serverSocket->acceptRequest("STREAMSERVERTHREAD");

		// dummy buffer
		string buffer[8];

		int counter = 0;

		while(counter < 15)
		{
			// wait for the pulse to fire
			int receivedPulse = MsgReceivePulse(getChannelId(), &buffer, sizeof(buffer), NULL);

			if (receivedPulse != 0)
				printf("\n[KPI::SSTREAMSERVERTHREAD_ERROR]:Failed to receive display pulse.");
			else
			{
				++counter;
				printf("\n[KPI::STREAMSERVERTHREAD]:Pulse %d received.",  counter);

				// read data from data holder
				controlData = joystickData->readJoystickData(controlData);

				// modify array values (for testing purposes only)
				for (unsigned int i = 0; i < dataSize; i++)
					controlData[i] = controlData[i] + counter;

				serverSocket->sendMsg(controlData);

			}
		}

		printf("\n[KPI::STREAMSERVERTHREAD]:Max counter reached.");
		return NULL;
	}
