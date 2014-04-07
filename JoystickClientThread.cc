#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "JoystickClientThread.h"

//---------------------------------------------------------------------------------------------
// JoystickClientThread implementation.
//---------------------------------------------------------------------------------------------

	/**-----------------------------------------------------------------------------------------
	 * Constructor
	 * -----------------------------------------------------------------------------------------*/
	JoystickClientThread::JoystickClientThread(JoystickData* joystickData_p, CJoystick* cJoystick_p)
	{
		printf("[KPI::JOYSTICKCLIENTTHREAD]:Initializing ...\n");
		joystickData = joystickData_p;
		clientJoystick = cJoystick_p;
		/** TODO: remove when all tests are complete */
		controlData = new double[dataSize];
	}

	/**-----------------------------------------------------------------------------------------
	 * Destructor
	 * -----------------------------------------------------------------------------------------*/
	JoystickClientThread::~JoystickClientThread()
	{
		printf("[KPI::JOYSTICKCLIENTTHREAD]:Destroying ...\n");
		/** TODO: remove when all tests are complete */
		delete controlData;
	}

	/**-----------------------------------------------------------------------------------------
	 * Overrides BaseThread's run() method.
	 * Implements JoystickClientThread that reads joystick control data and saves it
	 * in the shared data store.
	 * -----------------------------------------------------------------------------------------*/
	void* JoystickClientThread::run()
	{
		// dummy buffer
		string buffer[8];

		int counter = 0;
		while(counter < 15)
		{
			// wait for the pulse to fire
			int receivedPulse = MsgReceivePulse(getChannelId(), &buffer, sizeof(buffer), NULL);

			if (receivedPulse < 0)
				printf("[KPI::JOYSTICKCLIENTTHREAD_ERROR]:Failed to receive a timer pulse\n");
			else
			{
				printf("\n[KPI::JOYSTICKCLIENTTHREAD]:Timer pulse %d received\n",  ++counter);

				// save data into the shared QballData instance
				joystickData->saveJoystickData(clientJoystick->getData());

				if(!clientJoystick->isStatusOk())
				{
					printf(clientJoystick->getStatusMessage());
					return NULL;
				}
			}
		}

		printf("\n[KPI::JoystickClientThread]:Max counter reached\n");
		return NULL;
	}
