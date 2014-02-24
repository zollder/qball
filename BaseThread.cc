
#include "BaseThread.h"

//---------------------------------------------------------------------------------------------
// BaseThread class implementation.
//---------------------------------------------------------------------------------------------

	/**-----------------------------------------------------------------------------------------
	 * Constructor
	 * -----------------------------------------------------------------------------------------*/
//TODO Ask Eugen why passing mutex_r to a class mutex which does not have a constructor that accepts variable...
	BaseThread::BaseThread(Mutex& mutex_r) : mutex(mutex_r)
	{
		printf("[KPI::BaseThread]:Constructing ...\n");

		// pulse timer-related initializations
		setThreadId(1);
		setRunning(false);
		setDetached(false);
		setChannelId(createChannel());
	}

	/**-----------------------------------------------------------------------------------------
	 * Destroys thread object.
	 * - if the thread is running, mark it as detached to reclaim its storage upon termination
	 * - terminate thread, if it's running
	 * - destroy communication channel if it was successfully created by constructor
	 * -----------------------------------------------------------------------------------------*/
	BaseThread::~BaseThread()
	{
		printf("[KPI::BASETHREAD]:Destroying ...\n");

		if (isRunning() && !isDetached())
			pthread_detach(threadId);

		if (isRunning())
			pthread_cancel(threadId);

		int chId = getChannelId();
		if (chId != -1)
			ChannelDestroy(chId);
	}

	/**-----------------------------------------------------------------------------------------
	 * Creates a channel that can receive messages and pulses.
	 * ConnectAttach() should be called from the timer object in order to establish connection.
	 * -----------------------------------------------------------------------------------------*/
	int BaseThread::createChannel()
	{
		// disable priority inheritance with _NTO_CHF_FIXED_PRIORITY option
		int chId = ChannelCreate(_NTO_CHF_FIXED_PRIORITY);
		if (chId == -1)
				printf("[KPI::ERROR]:Unable to create a channel\n");
		else
			// for debugging purpose only
			printf("[KPI::BASETHREAD]:Channel successfully created \n");

		return chId;
	}


	/**-----------------------------------------------------------------------------------------
	 * Makes the current Thread instance runnable
	 * -----------------------------------------------------------------------------------------*/
	static void* runThread(void* arg)
	{
		return ((BaseThread*)arg)->run();
	}

	/**-----------------------------------------------------------------------------------------
	 * Starts a new thread or updates thread running status if the thread is already running.
	 * - threadId <=> reference to runThread for its future calls
	 * - runThread <=> target function that makes this class instance 'runnable'
	 * - this <=> void pointer to BaseThread instance, required to call run() within runThread
	 * - result = 0 => successful creation, result > 0 => failed to create thread
	 * -----------------------------------------------------------------------------------------*/
	int BaseThread::start()
	{
		int result = pthread_create(&threadId, NULL, runThread, this);
		if (result == 0)
		{
			this->setRunning(true);
			printf("[KPI::BASETHREAD]:Thread started\n");
		}

		return result;
	}

	/**-----------------------------------------------------------------------------------------
	 * Waits for the thread to complete and sets detached flag since pthread_join detaches it.
	 * -----------------------------------------------------------------------------------------*/
	int BaseThread::join()
	{
		int result = -1;
		if (isRunning())
		{
			result = pthread_join(threadId, NULL);
			if (result == 0)
			{
				setDetached(true);
				setRunning(false);
				printf("[KPI::BASETHREAD]:Thread detached/joined\n");
			}
		}

		return result;
	}

	/**-----------------------------------------------------------------------------------------
	 * Detaches a running and non-detached thread before it completes execution.
	 * Sets 'detached' flag if the operation is successful.
	 * -----------------------------------------------------------------------------------------*/
	int BaseThread::detach()
	{
		int result = -1;
		if (isRunning() && !isDetached())
		{
			result = pthread_detach(threadId);
			if (result == 0)
				setDetached(true);
		}

		return result;
	}

	/**-----------------------------------------------------------------------------------------
	 *
	 * 						****		SETTERS AND GETTERS		****
	 * -----------------------------------------------------------------------------------------*/

	/**-----------------------------------------------------------------------------------------
	 * Thread Running status.
	 * -----------------------------------------------------------------------------------------*/
	bool BaseThread::isRunning()
	{
		return running;
	}

	void BaseThread::setRunning(bool runningState)
	{
		this->running = runningState;
	}

	/**-----------------------------------------------------------------------------------------
	 * Thread's detached status.
	 * -----------------------------------------------------------------------------------------*/
	bool BaseThread::isDetached()
	{
		return detached;
	}

	void BaseThread::setDetached(bool detachedState)
	{
		this->detached = detachedState;
	}

	/**-----------------------------------------------------------------------------------------
	 * Thread id for display or logging purposes.
	 * -----------------------------------------------------------------------------------------*/
	pthread_t BaseThread::getThreadId()
	{
		return threadId;
	}

	void BaseThread::setThreadId(int id)
	{
		this->threadId = id;
	}

	/**-----------------------------------------------------------------------------------------
	// Channel id.
	* -----------------------------------------------------------------------------------------*/
	int BaseThread::getChannelId()
	{
		return channelId;
	}

	void BaseThread::setChannelId(int chId)
	{
		this->channelId = chId;
	}

