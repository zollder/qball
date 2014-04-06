#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "BaseThread.h"
#include "QballData.h"
#include "CSocket.h"

#ifndef streamclientthread_h
#define streamclientthread_h

//-----------------------------------------------------------------------------------------
// StreamClientThread interface.
//-----------------------------------------------------------------------------------------
class StreamClientThread : public BaseThread
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		StreamClientThread(QballData*, CSocket*);

		// destructor
		~StreamClientThread();

		// overrides BaseThread's run() method
		void* run();

	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	private:

		// data array size
		const static unsigned int dataSize = 12;

		QballData* qballData;
		CSocket* clientSocket;
};

#endif
