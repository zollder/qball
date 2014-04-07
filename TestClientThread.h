#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "BaseThread.h"
#include "CSocket.h"

#ifndef testclientthread_h
#define testclientthread_h

//-----------------------------------------------------------------------------------------
// TestClientThread interface.
//-----------------------------------------------------------------------------------------
class TestClientThread : public BaseThread
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		TestClientThread(CSocket*);

		// destructor
		~TestClientThread();

		// overrides BaseThread's run() method
		void* run();

	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	private:

		// data array size
		const static unsigned int dataSize = 8;

		// TODO: remove when tests are complete
		double* receivedData;

		CSocket* clientSocket;
};

#endif
