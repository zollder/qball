#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "BaseThread.h"
#include "JoystickData.h"
#include "CJoystick.h"

#ifndef joystickclientthread_h
#define joystickclientthread_h

//-----------------------------------------------------------------------------------------
// JoystickClientThread interface.
//-----------------------------------------------------------------------------------------
class JoystickClientThread : public BaseThread
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		JoystickClientThread(JoystickData*, CJoystick*);

		// destructor
		~JoystickClientThread();

		// overrides BaseThread's run() method
		void* run();

	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	private:

		// data array size
		const static unsigned int dataSize = 8;

		// TODO: remove when tests are complete
		 double* controlData;

		JoystickData* joystickData;
		CJoystick* clientJoystick;
};

#endif
