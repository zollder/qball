
#include "PulseTimer.h"

//---------------------------------------------------------------------------------------------
// Periodic PulseTimer class implementation.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	PulseTimer::PulseTimer(double interval, int channelId)
	{
		printf("[KPI::TIMER]:Initializing ...\n");

		// connect client to the channel
		connectionAttach(channelId);

		// convert interval to seconds and nanoseconds and initialize corresponding members
		setInterval(interval);

		// initialize notification structure and create timer
		createTimer();

		setRunning(false);
	}

	//-----------------------------------------------------------------------------------------
	// Destroys timer object.
	// 1. Detaches previously attached timer by specified connectionId (if not already detached).
	// 2. Removes it from the  timer_create() function by specified timerId.
	// (the timer is moved from  the active system timer list to the free list of available timers.)
	//-----------------------------------------------------------------------------------------
	PulseTimer::~PulseTimer()
	{
		printf("[KPI::TIMER]:Destroying ...\n");

		// detaches the connection
		if (ConnectDetach(getConnectionId()) < 0)
			printf("[KPI::TIMER_ERROR]:Detaching connection\n");

		// 0 <=> success, -1 <=> failure
		if (timer_delete(timerId) != 0)
			printf("[KPI::TIMER_ERROR]:Removing timer\n");
	}

	//-----------------------------------------------------------------------------------------
	// Connects client (pulse timer) to the server (corresponding thread).
	// Establishes a connection between the calling process and the channel specified by chId.
	//-----------------------------------------------------------------------------------------
	void PulseTimer::connectionAttach(int& chId)
	{
		int connectId = ConnectAttach(0, 0, chId, 0, 0);
		if (connectId == -1)
		{
			printf("[KPI::TIMER_ERROR]:Attaching connection\n");
			setDetached(true);
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("[KPI::TIMER]Connection attached\t\t\t\t[OK]\n");
			setConnectionId(connectId);
			setDetached(false);
		}
	}

	//-----------------------------------------------------------------------------------------
	// Converts specified time interval into seconds and nanoseconds
	//-----------------------------------------------------------------------------------------
	void PulseTimer::setInterval(double& interval)
	{
		double sec = floor(interval);
		seconds = (long) sec;
		nanoseconds = (long) (interval - sec)*pow(10,9);
	}

	//-----------------------------------------------------------------------------------------
	// Initializes notification.
	// Creates timer object within the kernel and initializes timerId (returns reference to timerId)
	//-----------------------------------------------------------------------------------------
	void PulseTimer::createTimer()
	{
		SIGEV_PULSE_INIT(&event, getConnectionId(), SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_TIMER, NULL);

		int timer = timer_create(CLOCK_REALTIME, &event, &timerId);
		if (timer == -1)
		{
			printf("[KPI::TIMER_ERROR]Failed to create timer\n");
			exit(EXIT_FAILURE);
		}
		else
			printf("[KPI::TIMER]:Timer created\t\t\t\t[OK]\n");
	}

	//-----------------------------------------------------------------------------------------
	// Starts timer and updates its running status.
	//-----------------------------------------------------------------------------------------
	int PulseTimer::start()
	{
		// (re)initializes timer structure
		reset();

		// start the timer and running status accordingly
		int result = timer_settime(timerId, 0, &timer, NULL);
		if (result != 0)
		{
			printf("[KPI::TIMER_ERROR]Failed to set time\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			this->setRunning(true);
			printf("[KPI::TIMER]Timer started\t\t\t\t[OK]\n");
		}

		return result;
	}

	//-----------------------------------------------------------------------------------------
	// Stops timer by nullifying its timer values and updating active system timer.
	//-----------------------------------------------------------------------------------------
	int PulseTimer::stop()
	{
		timer.it_value.tv_sec = 0;
		timer.it_value.tv_nsec = 0;
		timer.it_interval.tv_sec = 0;
		timer.it_interval.tv_nsec = 0;

		int result = timer_settime(timerId, 0, &timer, NULL);
		if (result == 0)
			this->setRunning(false);
		else
			printf("[KPI::TIMER_ERROR]:Unable to stop timer\n");

		return result;
	}

	//-----------------------------------------------------------------------------------------
	// (Re)Initializes the guts of the timer structure.
	//-----------------------------------------------------------------------------------------
	void PulseTimer::reset()
	{
		// periodic timer: will go off in 1 sec and then again every sec+nanosec
		timer.it_value.tv_sec = 1;
		timer.it_value.tv_nsec = 0;
		timer.it_interval.tv_sec = getSeconds();
		timer.it_interval.tv_nsec = getNanoseconds();
	}

	//-----------------------------------------------------------------------------------------
	// Detaches the connection specified by the connectionId.
	// If any threads are blocked on the connection at the time the connection is detached,
	// the send fails and returns with an error (see QNX doc for ConnectDetach()).
	//-----------------------------------------------------------------------------------------
	int PulseTimer::detach()
	{
		int result = ConnectDetach(getConnectionId());
		if (result == 0)
			this->setDetached(true);
		else
			printf("[KPI::TIMER_ERROR]:Unable to detach\n");

		return result;
	}

	/**-----------------------------------------------------------------------------------------
	 *
	 * 						****		SETTERS AND GETTERS		****
	 * -----------------------------------------------------------------------------------------*/

	//-----------------------------------------------------------------------------------------
	// Returns timer id for display or logging purposes.
	//-----------------------------------------------------------------------------------------
	timer_t PulseTimer::getTimerId()
	{
		return timerId;
	}

	//-----------------------------------------------------------------------------------------
	// Connection id.
	//-----------------------------------------------------------------------------------------
	void PulseTimer::setConnectionId(int id)
	{
		connectionId = id;
	}

	int PulseTimer::getConnectionId()
	{
		return connectionId;
	}

	//-----------------------------------------------------------------------------------------
	// Returns seconds portion (converted) of the timer interval.
	//-----------------------------------------------------------------------------------------
	long PulseTimer::getSeconds()
	{
		return seconds;
	}

	//-----------------------------------------------------------------------------------------
	// Returns nanoseconds portion (converted) of the timer interval.
	//-----------------------------------------------------------------------------------------
	long PulseTimer::getNanoseconds()
	{
		return nanoseconds;
	}

	//-----------------------------------------------------------------------------------------
	// Timer's running state.
	//-----------------------------------------------------------------------------------------
	void PulseTimer::setRunning(bool runningState)
	{
		running = runningState;
	}

	bool PulseTimer::isRunning()
	{
		return running;
	}

	//-----------------------------------------------------------------------------------------
	// Timer's detached flag (1=true, 0=false)
	//-----------------------------------------------------------------------------------------
	void PulseTimer::setDetached(bool detachedState)
	{
		detached = detachedState;
	}

	bool PulseTimer::isDetached()
	{
		return detached;
	}
