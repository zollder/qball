#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "QballPrinterThread.h"

//---------------------------------------------------------------------------------------------
// QballPrinterThread subclass implementation.
// Prints sensor data stored in a data holder class instance.
//---------------------------------------------------------------------------------------------

	/**-----------------------------------------------------------------------------------------
	 * Constructor
	 * -----------------------------------------------------------------------------------------*/
	QballPrinterThread::QballPrinterThread(QballData* qballData_p)
	{
		printf("[KPI::QBALLPRINTERTHREAD]:Initializing ...\n");
		qballData = qballData_p;

		// create an array and initialize its members to zeros
		sensorDataLocal = new double[dataSize];
		for(unsigned int i = 0; i < dataSize; i++)
			sensorDataLocal[i] = 0;
	}

	/**-----------------------------------------------------------------------------------------
	 * Destructor
	 * -----------------------------------------------------------------------------------------*/
	QballPrinterThread::~QballPrinterThread()
	{
		printf("[KPI::QBALLPRINTERTHREAD]:Destroying ...\n");

		delete sensorDataLocal;
	}

	/**-----------------------------------------------------------------------------------------
	 * Overrides BaseThread's run() method.
	 * Implements QballPrinterThread that reads and displays data from the data holder object.
	 * -----------------------------------------------------------------------------------------*/
	void* QballPrinterThread::run()
	{
		// dummy buffer
		string buffer[8];

		int counter = 0;
		while(counter < 10)
		{
			// wait for the pulse to fire
			int receivedPulse = MsgReceivePulse(getChannelId(), &buffer, sizeof(buffer), NULL);

			if (receivedPulse < 0)
				printf("[KPI::QBALLPRINTERTHREAD_ERROR]:Failed to receive a timer pulse\n");
			else
			{
				printf("\n[KPI::QBALLPRINTERTHREAD]:Timer pulse %d received\n",  ++counter);

				// read data from the qballData to local array of doubles
				sensorDataLocal = qballData->readSensorData(sensorDataLocal);

				// print sensor data to the console
				printf("\n[KPI::QBALLPRINTERTHREAD]:Printing data ...\n");
				for(unsigned int i = 0; i < dataSize; i++)
					printf("%.2f, ", sensorDataLocal[i]);
			}
		}

		printf("\n[KPI::QBALLPRINTERTHREAD]:Max counter reached\n");
		return NULL;
	}
