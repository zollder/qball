/*
 * cqstreamsrv.cpp
 *
 *  Created on: 2014-03-31
 *      Author: oleg
 */

#include <string>
#include <iostream>
#include "PulseTimer.h"
#include "cqstreamsrv.h"

using namespace std;

cqstreamsrv::cqstreamsrv( int port, int sample_time )
{
	this->port=port;
	this->sample_time=sample_time;
	thread_id=NULL;
	pthread_mutex_init( &mutex,NULL );

	start();
}

cqstreamsrv::~cqstreamsrv()
{
	stop();
	pthread_mutex_destroy(&mutex);
}

void cqstreamsrv::start()
{
	int i;
	stop_req=0;
	is_data_copied2buff=false;
	is_data_sent=false;
	for( i = 0 ; i < 8 ; i++ )
		snd_data[i]=0;
	if( pthread_create( &thread_id,NULL,thread_stud_srv,(void *) this ) != EOK )
		thread_id = NULL;
}

void cqstreamsrv::stop()
{
	stop_req=1;
	if( thread_id != NULL )
		pthread_join( thread_id,NULL );
	thread_id=NULL;
}

void cqstreamsrv::send_data_array( double data[] )
{
	pthread_mutex_lock(&mutex);

	//copy data to the buffer

	is_data_copied2buff=false;
	pthread_mutex_unlock(&mutex);
}

void cqstreamsrv::send_data( double d0,double d1,double d2,double d3,double d4,double d5,double d6,double d7 )
{
	pthread_mutex_lock( &mutex );

	//copy data to the buffer

	is_data_copied2buff=false;
	pthread_mutex_unlock( &mutex );
}

int cqstreamsrv::new_data_is_sent()
{
	if( is_data_sent && is_data_copied2buff )
		return 1;
	else
		return 0;
}
void * thread_stud_srv(void* arg)
{
	cqstreamsrv& qstream = *(cqstreamsrv *) arg;
	qstream.server();
	return 0;
}

void cqstreamsrv::server()
{
	// initiate the timer

	while( stop_req == 0)
	{
		// initialize the socket and bind to the port
	}

	while( stop_req == 0)
	{
		// start listening to the port
	}

	while( stop_req == 0)
	{
		while( stop_req == 0 )
		{
			// accepts the client request
		}

		while( stop_req == 0)
		{
			pthread_mutex_lock(& mutex);

			//copy snd_data to the local buffer

			is_data_copied2buff=true;
			is_data_sent=false;

			pthread_mutex_unlock( & mutex );

			//send local buffers data

			pthread_mutex_lock( & mutex );
			is_data_sent=true;

			pthread_mutex_unlock(& mutex);

			// wait for timer
		}
	}
	// close the socket
}
