#include <cstdlib>
#include <iostream.h>
#include <list>
#include <math.h>

#include "Mutex.h"

#ifndef joystickdata_h
#define joystickdata_h

//-----------------------------------------------------------------------------------------
// JoystickData interface. Data holder for joystick control data.
//-----------------------------------------------------------------------------------------
class JoystickData
{
	// local mutex instance
	Mutex mutex;

	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		JoystickData();

		// destructor
		~JoystickData();

		//-----------------------------------------------------------------------------------------
		/** Saves (copies) joystick control data into the local array of doubles. */
		//-----------------------------------------------------------------------------------------
		void saveJoystickData(double* data);

		//-----------------------------------------------------------------------------------------
		/** Returns joystick control data as an array of doubles.
		 *  Copies joystick data from local array to one provided by client. */
		//-----------------------------------------------------------------------------------------
		double* readJoystickData(double* data);


	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	private:

		// pointer to an array of doubles holding joystick data
		double* joystickData;
};

#endif
