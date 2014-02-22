<<<<<<< HEAD
/*
 * PulseTimer.h
 *
 *  Created on: 2014-02-16
 *      Author: eugen,oleg
 */
#ifndef PULSETIMER_H_
#define PULSETIMER_H_
=======
>>>>>>> 87117513a757801ddbd979ab0322cf59a8130022
#include <cstdlib>
#include <iostream.h>
#include <time.h>
#include <sys/siginfo.h>
#include <sys/neutrino.h>

// include -lmath linker option at compile time to avoid "undefined reference" error
#include <math.h>

<<<<<<< HEAD
=======
#ifndef pulsetimer_h
#define pulsetimer_h

>>>>>>> 87117513a757801ddbd979ab0322cf59a8130022
// pulse from timer (check the pulse's code value upon message receipt)
#define PULSE_FROM_TIMER 1

//-----------------------------------------------------------------------------------------
// PulseTimer interface.
//-----------------------------------------------------------------------------------------
class PulseTimer
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
<<<<<<< HEAD
		PulseTimer(double);
=======
		PulseTimer(double, int);
>>>>>>> 87117513a757801ddbd979ab0322cf59a8130022

		// destructor
		~PulseTimer();

		// starts timer
		int start();

		// stops timer
		int stop();

<<<<<<< HEAD
		// waits for the pulse to fire
		void wait();

=======
>>>>>>> 87117513a757801ddbd979ab0322cf59a8130022
		// (re)initializes the guts of the timer structure
		void reset();

		// detaches timer from the channel.
		int detach();

		// returns a handle to the current timer instance (itself)
		timer_t getTimerId();

		// returns connection id
		int getConnectionId();

		// returns seconds portion of the time interval
		long getSeconds();

		// returns nanoseconds portion of the time interval
		long getNanoseconds();

		// returns timer's running state
		bool isRunning();

		// returns timer's detached state
		bool isDetached();

<<<<<<< HEAD
		// returns channel id
		int getChannelId();

=======
>>>>>>> 87117513a757801ddbd979ab0322cf59a8130022
	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	private:

		timer_t timerId;
		struct itimerspec timer;
		struct sigevent event;
		int connectionId;
<<<<<<< HEAD
		int channelId;
=======
>>>>>>> 87117513a757801ddbd979ab0322cf59a8130022

		long seconds;
		long nanoseconds;

		bool running;
		bool detached;

	//-----------------------------------------------------------------------------------------
	// Protected members
	//-----------------------------------------------------------------------------------------
	protected:

<<<<<<< HEAD
		// created communication channel
		int createChannel();

		// sets channel id
		void setChannelId(int);

=======
>>>>>>> 87117513a757801ddbd979ab0322cf59a8130022
		// attaches connection
		void connectionAttach(int);

		// sets seconds portion of the time interval
		void setInterval(double interval);

		// creates timer
		void createTimer();

		// sets connection id
		void setConnectionId(int id);

		// sets timer's running flag (1=true, 0=false)
		void setRunning(bool);

		// sets timer's detached flag (1=true, 0=false)
		void setDetached(bool);
};
<<<<<<< HEAD
#endif /* PULSETIMER_H_ */
=======

#endif
>>>>>>> 87117513a757801ddbd979ab0322cf59a8130022
