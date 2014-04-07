#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "BaseThread.h"
#include "CSocket.h"

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

		const static unsigned int dataSize = 12;
		CSocket* serverSocket;
};

#endif
