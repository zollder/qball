#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "CJoystick.h"
#include "JoystickData.h"
#include "JoystickClientThread.h"
#include "PulseTimer.h"

#ifndef joystickclient_h
#define joystickclient_h

//-----------------------------------------------------------------------------------------
// StreamClient interface.
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
/** JoystickClient interface.
 *  Wrapper around Joystick client services.
 *  Simplifies client start-up routine by instantiating and initializing
 *  CJoystick, JoystickClientThread and PulseTimer objects in the required sequence.
 *  Is driven by the pulse timer instance with custom time interval.
 */
//-----------------------------------------------------------------------------------------
class JoystickClient
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		JoystickClient(double interval, JoystickData* data);

		// destructor
		~JoystickClient();

		// enables and starts the client
		void start();

		// stops and cleans the client
		void stop();

	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
    private:

		CJoystick* clientJoystick;
		JoystickClientThread* joystickClientThread;
		PulseTimer* joystickClientTimer;
};

#endif
