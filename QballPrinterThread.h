#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "BaseThread.h"
#include "QballData.h"

#ifndef qballprinterthread_h
#define qballprinterthread_h

//-----------------------------------------------------------------------------------------
// QballPrinterThread interface.
//-----------------------------------------------------------------------------------------
class QballPrinterThread : public BaseThread
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		QballPrinterThread(QballData*);

		// destructor
		~QballPrinterThread();

		// overrides QballPrinterThread's run() method
		void* run();

	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	private:

		QballData* qballData;
		double* sensorDataLocal;
};

#endif
