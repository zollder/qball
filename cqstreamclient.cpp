/*
 * Implementation of cqstream class
 *Created on: 2014-02-15
 *	Author: eugen, oleg
 */
/*
// standard needed header files.
#include <string.h>
#include <iostream.h>
#include <stdexcept>      // std::out_of_range

#include "cppsocket.h"
#include "PulseTimer.h"
#include "cqstreamclient.h"

using namespace std;

#define BUFLEN 1000


//Sensor description
#define Gyroscope_x-axis 0
#define Gyroscope_y-axis 1
#define Gyroscope_z-axis 2
#define Accelerometer_x-axis 3
#define Accelerometer_y-axis 4
#define Accelerometer_z-axis 5
#define Magnetometer_x-axis 6
#define Magnetometer_y-axis 7
#define Magnetometer_z-axis 8
#define Battery_voltage 9
#define Sonar 10
#define Reserved 11

cqstreamclient::cqstreamclient(char * hostaddress, int port,int sample_time,int ch_size)
{
	this->port=port;
	this->sample_time=sample_time;

	try
	{
		if( ch_size > 100 || ch_size < 1 )
			throw out_of_range ("Invalid Range of channel size, acceptable values [1-100]");
		this->ch_size=ch_size;

	}
	catch( const out_of_range &e)
	{
		cerr<<"[KPI::ERROR]: "<< e.what()<<endl;
		exit(EXIT_FAILURE);
	}

	try
	{
		strcpy(this->hostaddress,hostaddress);
	}
	catch( const length_error &e)
	{
		cerr<<"[KPI::ERROR]: "<< e.what()<<endl;
		exit(EXIT_FAILURE);
	}

	thread_id=NULL;
	pthread_mutex_init(&mutex,NULL);

	start();
}

cqstreamclient::~cqstreamclient()
{
	stop();
	pthread_mutex_destroy(&mutex);
}

void cqstreamclient::start()
{
	int i;
	stop_req=0;

	for( i = 0 ; i < ch_size ; i++ )
		rcv_data[i]=0;

	if( pthread_create( &thread_id , NULL , thread_stud , (void *) this ) != EOK )
		thread_id=NULL;
}

void cqstreamclient::stop()
{
	stop_req=1;

	if( thread_id != NULL )
		pthread_join( thread_id , NULL );

	thread_id=NULL;
}

void cqstreamclient::get_data_array( double * databuff )
{
	pthread_mutex_lock(&mutex);
	// copy the data from rcv_data to the output buffer
	pthread_mutex_unlock(&mutex);
}

double cqstreamclient::get_data(int i)
{
	pthread_mutex_lock(&mutex);
	// return the from rcv_data
	pthread_mutex_unlock(&mutex);
}
void * cqstreamclient::thread_stud(void* arg)
{
	cqstreamclient& qstream = *(cqstreamclient *) arg;
	qstream.client();

	return 0;
}


void cqstreamclient::client()
{
	int rcv_data_size=0,timeoutcnt=0;
	// initiate the timer
	while( stop_req==0)
	{
		// initialize the socket and connect to server
		cout<<"Connected to the server."<<endl;
		timeoutcnt=0;
		while( stop_req==0)
		{
			// receiving the data
		//		 if data is received
		//	 * {
		//	 * timeoutcnt=0;
		//	 * pthread_mutex_lock(& mutex);
		//	 * copy data to rcv_data buffer
		//	 * pthread_mutex_unlock(& mutex);
		//	 * }
		//	 * else
		//	 * timeoutcnt++;
			if(rcvlen==-1 || timeoutcnt>100)
				break; // there is an wait for the timer
		}
	}
	// close the socket
}
*/


