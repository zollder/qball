
#include <cstdlib>
#include <iostream.h>
#include <list>
#include <math.h>

#include "Mutex.h"

#ifndef qballdata_h
#define qballdata_h

//-----------------------------------------------------------------------------------------
// QballData interface - data holder for QBall sensor data.
//-----------------------------------------------------------------------------------------
class QballData
{
	// local mutex instance
	Mutex mutex;

	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		QballData();

		// destructor
		~QballData();

		//-----------------------------------------------------------------------------------------
		/** Saves (copies) sensor data into the local array of doubles. */
		//-----------------------------------------------------------------------------------------
		void saveSensorData(double* data);

		//-----------------------------------------------------------------------------------------
		/** Returns sensor data as an array of doubles.
		 *  Copies sensor data from local array to one injected by client. */
		//-----------------------------------------------------------------------------------------
		double* readSensorData(double* data);

	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	private:

		// pointer to an array of doubles holding sensor data
		double* sensorData;
};

#endif
