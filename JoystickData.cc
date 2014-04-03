
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

		// create an array and initialize its members to zeros
		joystickData = new double[8];
		for(unsigned int i = 0; i < 8; i++)
			joystickData[i] = 0;
	}

	//-----------------------------------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------------------------------
	JoystickData::~JoystickData()
	{
		printf("[KPI::JoystickData]:Destroying ...\n");

		delete joystickData;
	}

	//-----------------------------------------------------------------------------------------
	/** Saves (copies) joystick control data into the local array of doubles. */
	//-----------------------------------------------------------------------------------------
	void JoystickData::saveJoystickData(double* data)
	{
		mutex.lock();

		for(unsigned int i = 0; i < 8; i++)
			joystickData[i] = data[i];

		mutex.unlock();
	}

	//-----------------------------------------------------------------------------------------
	/** Returns joystick control data as an array of doubles.
	 *  Copies joystick data from local array to one provided by client. */
	//-----------------------------------------------------------------------------------------
	double* JoystickData::readJoystickData(double* data)
	{
		mutex.lock();

		for(unsigned int i = 0; i < 8; i++)
			data[i] = joystickData[i];

		mutex.unlock();

		return data;
	}
