

#include "JoystickData.h"

//---------------------------------------------------------------------------------------------
// NaviData class implementation. NOTE: not used in the current version
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	JoystickData::JoystickData()
	{
		printf("[KPI::JoystickData]:Initializing ...\n");

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
		statusData -> battery = 0;
		statusData -> sonar = 0;
		statusData -> other = 0;
	}

	//-----------------------------------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------------------------------
	JoystickData::~JoystickData()
	{
		printf("[KPI::JoystickData]:Destroying ...\n");

		delete gyroscopeData;
		delete accelerometerData;
		delete magnetometerData;
		delete statusData;
	}

	//-----------------------------------------------------------------------------------------
	// returns a pointer to gyroscope data holder.
	//-----------------------------------------------------------------------------------------
	JoystickData::Gyroscope* JoystickData::getGyroscopeData()
	{
		return gyroscopeData;
	}

	//-----------------------------------------------------------------------------------------
	// returns a pointer to accelerometer data holder.
	//-----------------------------------------------------------------------------------------
	JoystickData::Accelerometer* JoystickData::getAccelerometerData()
	{
		return accelerometerData;
	}

	//-----------------------------------------------------------------------------------------
	// returns a pointer to magnetometer data holder.
	//-----------------------------------------------------------------------------------------
	JoystickData::Magnetometer* JoystickData::getMagnetometerData()
	{
		return magnetometerData;
	}

	//-----------------------------------------------------------------------------------------
	// returns a pointer to system status data holder.
	//-----------------------------------------------------------------------------------------
	JoystickData::Status* JoystickData::getStatusData()
	{
		return statusData;
	}
