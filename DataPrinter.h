#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "BaseThread.h"
#include "QballData.h"

#ifndef dataprinter_h
#define dataprinter_h

//-----------------------------------------------------------------------------------------
// DataPrinter interface.
//-----------------------------------------------------------------------------------------
class DataPrinter : public BaseThread
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		DataPrinter(QballData*);

		// destructor
		~DataPrinter();

		// overrides DataPrinter's run() method
		void* run();

	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	private:

		QballData* qballData;
		double* sensorDataLocal;
};

#endif
