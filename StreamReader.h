#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "BaseThread.h"

#ifndef streamreader_h
#define streamreader_h

//-----------------------------------------------------------------------------------------
// StreamReader interface.
//-----------------------------------------------------------------------------------------
class StreamReader : public BaseThread
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		StreamReader(Mutex&, QballData*, CSocket*);

		// destructor
		~StreamReader();

		// overrides BaseThread's run() method
		void* run();

	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
    private:
		// local data holders (distance and velocity)
		double x,y,z;
		double Vx,Vy,Vz;
};

#endif
