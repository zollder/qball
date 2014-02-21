#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "StreamReader.h"

//---------------------------------------------------------------------------------------------
// StreamReader subclass implementation.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	StreamReader::StreamReader(Mutex& mutex_r, QballData* qballData_p, CSocket* cSocket_p) : BaseThread(mutex_r, qballData_p, cSocket_p)
	{
		printf("Constructing StreamReader ...\n");
	}

	//-----------------------------------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------------------------------
	StreamReader::~StreamReader()
	{
		printf("Destroying StreamReader ...\n");
	}

	//-----------------------------------------------------------------------------------------
	// Overrides BaseThread's run() method
	//-----------------------------------------------------------------------------------------
	void* StreamReader::run()
	{
		// dummy buffer
		string buffer[8];

		int counter = 0;
		while(counter < 5)
		{
			// wait for the pulse to fire
			int receivedPulse = MsgReceivePulse(getChannelId(), &buffer, sizeof(buffer), NULL);

			if (receivedPulse != 0)
			{
				printf("[StreamReader] Error receiving display pulse\n");
			}
			else
			{
				printf("\n[StreamReader] Timer pulse %d received\n",  counter+1);

				clientSocket->receiveMsg();
				// fetch navi data from shared object
//				mutex.lock();
//				x = naviData->getDistanceData()->x;
//				y = naviData->getDistanceData()->y;
//				z = naviData->getDistanceData()->z;
//
//				Vx = naviData->getVelocityData()->Vx;
//				Vy = naviData->getVelocityData()->Vy;
//				Vz = naviData->getVelocityData()->Vz;
//				mutex.unlock();

				// Display distance and velocity (shared data object)
//				printf("Distance: x: %f, y: %f, z: %f \n", x, y, z);
//				printf("Velocity: Vx: %f, Vy: %f, Vz: %f \n", Vx, Vy, Vz);

		    	counter++;
			}
		}

		printf("\n[StreamReader] Max counter reached.\n");

		return NULL;
	}
