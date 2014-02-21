#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "BaseThread.h"

#ifndef streamwriter_h
#define streamwriter_h

//-----------------------------------------------------------------------------------------
// StreamWriter interface.
//-----------------------------------------------------------------------------------------
class StreamWriter : public BaseThread
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		StreamWriter(CSocket*);

		// destructor
		~StreamWriter();

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
