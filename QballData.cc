

#include "QballData.h"

//---------------------------------------------------------------------------------------------
// NaviData class implementation.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	QballData::QballData()
	{
		printf("Initializing QballData ... \n");

		// initialize gyroscope data holder
		gyroscopeData = new Gyroscope();
		gyroscopeData -> x = 0;
		gyroscopeData -> y = 0;
		gyroscopeData -> z = 0;

		// initialize accelerometer data holder
		accelerometerData = new Accelerometer();
		accelerometerData -> x = 0;
		accelerometerData -> y = 0;
		accelerometerData -> z = 0;

		// initialize magnetometer data holder
		magnetometerData = new Magnetometer();
		magnetometerData -> x = 0;
		magnetometerData -> y = 0;
		magnetometerData -> z = 0;

		// initialize system status data holder
		statusData = new Status();
		statusData -> x = 0;
		statusData -> y = 0;
		statusData -> z = 0;
	}

	//-----------------------------------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------------------------------
	QballData::~QballData()
	{
		printf("Destroying QballData ... \n");

		delete gyroscopeData;
		delete accelerometerData;
		delete magnetometerData;
		delete statusData;
	}

	//-----------------------------------------------------------------------------------------
	// returns a pointer to gyroscope data holder.
	//-----------------------------------------------------------------------------------------
	QballData::Gyroscope* QballData::getGyroscopeData()
	{
		return gyroscopeData;
	}

	//-----------------------------------------------------------------------------------------
	// returns a pointer to accelerometer data holder.
	//-----------------------------------------------------------------------------------------
	QballData::Accelerometer* QballData::getAccelerometerData()
	{
		return accelerometerData;
	}

	//-----------------------------------------------------------------------------------------
	// returns a pointer to magnetometer data holder.
	//-----------------------------------------------------------------------------------------
	QballData::Magnetometer* QballData::getMagnetometerData()
	{
		return magnetometerData;
	}

	//-----------------------------------------------------------------------------------------
	// returns a pointer to system status data holder.
	//-----------------------------------------------------------------------------------------
	QballData::Status* QballData::getStatusData()
	{
		return statusData;
	}
