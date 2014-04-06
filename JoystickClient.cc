#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "JoystickClient.h"

//---------------------------------------------------------------------------------------------
// JoystickClient implementation.
//---------------------------------------------------------------------------------------------

	/**-----------------------------------------------------------------------------------------
	 * Constructor
	 *-----------------------------------------------------------------------------------------*/
	JoystickClient::JoystickClient(double interval, JoystickData* data)
	{
		printf("[KPI::JoystickClient]:Initializing ...\n");

		// instantiate objects

		clientJoystick = new CJoystick();

		// verify joystick status and print device info
		if(!clientJoystick->isStatusOk())
		{
			printf("%s\n", clientJoystick->getStatusMessage());
			return;
		}
		else
			clientJoystick->printDeviceInfo(3);

		joystickClientThread = new JoystickClientThread(data, clientJoystick);
		joystickClientTimer = new PulseTimer(interval, joystickClientThread->getChannelId());
	}

	/**-----------------------------------------------------------------------------------------
	 * Destructor
	 * -----------------------------------------------------------------------------------------*/
	JoystickClient::~JoystickClient()
	{
		printf("[KPI::JoystickClient]:Destroying ...\n");

		delete clientJoystick;
		delete joystickClientThread;
		delete joystickClientTimer;
	}

	/**-----------------------------------------------------------------------------------------
	 * Prepares and starts the client:
	 * - starts JoystickClient thread;
	 * - enables pulse timer;
	 * -----------------------------------------------------------------------------------------*/
	void JoystickClient::start()
	{
		joystickClientThread->start();
		joystickClientTimer->start();
	}

	/**-----------------------------------------------------------------------------------------
	 * Stops and cleans up the client:
	 * - stops (joins) JoystickClient thread;
	 * - stops pulse timer;
	 * -----------------------------------------------------------------------------------------*/
	void JoystickClient::stop()
	{
		joystickClientThread->join();
		joystickClientTimer->stop();
	}
