#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "QballPrinterThread.h"
#include "PulseTimer.h"

#ifndef qballprinter_h
#define qballprinter_h

//-----------------------------------------------------------------------------------------
/** QballPrinter interface.
 *  Wrapper around QBall printer services.
 *  Prints QBlall sensor data stored in the sensor data holder at regular intervals.
 *  Is driven by the pulse timer instance with custom time interval.
 */
//-----------------------------------------------------------------------------------------
class QballPrinter
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		QballPrinter(QballData*, double);

		// destructor
		~QballPrinter();

		// returns reference to printer thread instance
		QballPrinterThread* getPrinterThread();

		// returns reference to pulse timer instance
		PulseTimer* getPulseTimer();

		// starts data printer
		void start();

		// stops data printer
		void stop();

	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
    private:

		QballPrinterThread* qballPrinterThread;
		PulseTimer* qballPrintTimer;
};

#endif
