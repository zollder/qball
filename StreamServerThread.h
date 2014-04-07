#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "BaseThread.h"
#include "CSocket.h"
#include "JoystickData.h"

#ifndef streamserverthread_h
#define streamserverthread_h

//-----------------------------------------------------------------------------------------
// StreamServerThread interface.
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
/** StreamServerThread interface
 *  Is responsible for reading joystick data from the shared data holder and
 *  send it to the target device.
 *  Is driven by the pulse timer instance with custom time interval.
 */
//-----------------------------------------------------------------------------------------
class StreamServerThread : public BaseThread
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		StreamServerThread(JoystickData*, CSocket*);

		// destructor
		~StreamServerThread();

		// overrides BaseThread's run() method
		void* run();

	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	private:

		// data array size
		const static unsigned int dataSize = 8;
		double* controlData;

		JoystickData* joystickData;
		CSocket* serverSocket;
};

#endif
