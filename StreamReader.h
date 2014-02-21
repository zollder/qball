#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "BaseThread.h"
#include "QballData.h"
#include "CSocket.h"

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

		QballData* qballData;
		CSocket* clientSocket;
};

#endif
