#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "QballPrinter.h"

//---------------------------------------------------------------------------------------------
// QballPrinter implementation.
//---------------------------------------------------------------------------------------------

	/**-----------------------------------------------------------------------------------------
	 * Constructor
	 * -----------------------------------------------------------------------------------------*/
	QballPrinter::QballPrinter(QballData* qballData, double timeInterval)
	{
		printf("[KPI::QBALLPRINTER]:Constructing ...\n");

		if (!qballData || !timeInterval)
		{
			printf("[KPI::QBALLPRINTER]:missing QBall data or timer interval...\n");
			exit(EXIT_FAILURE);
		}
		// instantiate objects
		qballPrinterThread = new QballPrinterThread(qballData);
		qballPrintTimer = new PulseTimer(timeInterval, qballPrinterThread->getChannelId());
	}

	/**-----------------------------------------------------------------------------------------
	 * Destructor
	 * -----------------------------------------------------------------------------------------*/
	QballPrinter::~QballPrinter()
	{
		printf("[KPI::QBALLPRINTER]:Destroying ...\n");

		delete qballPrinterThread;
		delete qballPrintTimer;
	}
	/**-----------------------------------------------------------------------------------------
	 * Prepares and starts the server:
	 * -----------------------------------------------------------------------------------------*/
	void QballPrinter::start()
	{
		qballPrinterThread->start();
		qballPrintTimer->start();
	}

	/**-----------------------------------------------------------------------------------------
	 * Stops and cleans up the server:
	 * -----------------------------------------------------------------------------------------*/
	void QballPrinter::stop()
	{
		qballPrinterThread->join();
		qballPrintTimer->stop();
	}

	/**-----------------------------------------------------------------------------------------
	 * Returns reference to printer thread instance.
	 * -----------------------------------------------------------------------------------------*/
	QballPrinterThread* QballPrinter::getPrinterThread()
	{
		return qballPrinterThread;
	}

	/**-----------------------------------------------------------------------------------------
	 * Returns reference to pulse timer instance.
	 * -----------------------------------------------------------------------------------------*/
	PulseTimer* QballPrinter::getPulseTimer()
	{
		return qballPrintTimer;
	}
