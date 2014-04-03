
#include "QballData.h"

//---------------------------------------------------------------------------------------------
// QballData implementation - data holder for QBall sensor data.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	QballData::QballData()
	{
		printf("[KPI::QBALLDATA]:Initializing ...\n");

		// create an array and initialize its members to zeros
		sensorData = new double[12];
		for(unsigned int i = 0; i < 12; i++)
			sensorData[i] = 0;
	}

	//-----------------------------------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------------------------------
	QballData::~QballData()
	{
		printf("[KPI::QBALLDATA]:Destroying ...\n");

		delete sensorData;
	}

	//-----------------------------------------------------------------------------------------
	/** Saves (copies) sensor data into the local array of doubles. */
	//-----------------------------------------------------------------------------------------
	void QballData::saveSensorData(double* data)
	{
		mutex.lock();

		for(unsigned int i = 0; i < 12; i++)
			sensorData[i] = data[i];

		mutex.unlock();
	}

	//-----------------------------------------------------------------------------------------
	/** Returns sensor data as an array of doubles.
	 *  Copies sensor data from local array to one injected by client. */
	//-----------------------------------------------------------------------------------------
	double* QballData::readSensorData(double* data)
	{
		mutex.lock();

		for(unsigned int i = 0; i < 12; i++)
			data[i] = sensorData[i];

		mutex.unlock();

		return data;
	}
