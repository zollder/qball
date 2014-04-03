#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "DataPrinter.h"

//---------------------------------------------------------------------------------------------
// DataPrinter subclass implementation.
// Prints sensor data stored in a data holder class instance.
//---------------------------------------------------------------------------------------------

	/**-----------------------------------------------------------------------------------------
	 * Constructor
	 * -----------------------------------------------------------------------------------------*/
	DataPrinter::DataPrinter(QballData* qballData_p)
	{
		printf("[KPI::DATAPRINTER]:Initializing ...\n");
		qballData = qballData_p;

		// create an array and initialize its members to zeros
		sensorDataLocal = new double[12];
		for(unsigned int i = 0; i < 12; i++)
			sensorDataLocal[i] = 0;
	}

	/**-----------------------------------------------------------------------------------------
	 * Destructor
	 * -----------------------------------------------------------------------------------------*/
	DataPrinter::~DataPrinter()
	{
		printf("[KPI::DATAPRINTER]:Destroying ...\n");
	}

	/**-----------------------------------------------------------------------------------------
	 * Overrides BaseThread's run() method.
	 * Implements DataPrinter thread that reads and displays data from the data holder object.
	 * -----------------------------------------------------------------------------------------*/
	void* DataPrinter::run()
	{
		// dummy buffer
		string buffer[8];

		int counter = 0;
		while(counter < 10)
		{
			// wait for the pulse to fire
			int receivedPulse = MsgReceivePulse(getChannelId(), &buffer, sizeof(buffer), NULL);

			if (receivedPulse < 0)
				printf("[KPI::DATAPRINTER_ERROR]:Failed to receive a timer pulse\n");
			else
			{
				printf("\n[KPI::DATAPRINTER]:Timer pulse %d received\n",  ++counter);

				// read data from the qballData to local array of doubles
				sensorDataLocal = qballData->readSensorData(sensorDataLocal);

				// print sensor data to the console
				for(unsigned int i = 0; i < 12; i++)
					printf("%.2f, ", sensorDataLocal[i]);
			}
		}

		printf("\n[KPI::DATAPRINTER]:Max counter reached\n");
		return NULL;
	}
