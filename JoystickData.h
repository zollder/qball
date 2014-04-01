#include <cstdlib>
#include <iostream.h>
#include <list>
#include <math.h>

#ifndef joystickdata_h
#define joystickdata_h

//-----------------------------------------------------------------------------------------
// QBall telemetry data interface. NOTE: not used in the current version
//-----------------------------------------------------------------------------------------
class JoystickData
{
	// structures are private and their members are public by default

	// gyroscope data structure declaration: data-holder for received gyroscope values
	struct Gyroscope
	{
		double x;
		double y;
		double z;
	};

	// accelerometer data structure declaration: data-holder for received accelerometer values
	struct Accelerometer
	{
		double x;
		double y;
		double z;
	};

	// magnetometer data structure declaration: data-holder for received magnetometer values
	struct Magnetometer
	{
		double x;
		double y;
		double z;
	};

	// target system status data structure declaration: data-holder for received target system state values
	struct Status
	{
		double battery;
		double sonar;
		double other;
	};


	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		JoystickData();

		// destructor
		~JoystickData();

		// returns a pointer to gyroscope data structure that holds received gyroscope values
		Gyroscope* getGyroscopeData();

		// returns a pointer to accelerometer data structure that holds received accelerometer values
		Accelerometer* getAccelerometerData();

		// returns a pointer to magnetometer data structure that holds received magnetometer values
		Magnetometer* getMagnetometerData();

		// returns a pointer to system status data structure that holds received system state values
		Status* getStatusData();


	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	private:
		Gyroscope* gyroscopeData;
		Accelerometer* accelerometerData;
		Magnetometer* magnetometerData;
		Status* statusData;
};

#endif
