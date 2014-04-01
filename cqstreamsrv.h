/*
 * cqstreamsrv.h
 *
 *  Created on: 2014-03-31
 *      Author: oleg, Eugen
 */

#ifndef CQSTREAMSRV_H_
#define CQSTREAMSRV_H_

#include <pthread.h>
#include "Cppsocket.h"

class cqstreamsrv
{
	private:

		pthread_t thread_id;
		pthread_mutex_t mutex;
		int stop_req;
		double snd_data[8];
		bool is_data_copied2buff, is_data_sent;
		friend void * thread_stud_srv(void* arg);

	public:

		cqstreamsrv(int ,int );
		~cqstreamsrv();

		int new_data_is_sent();
		void send_data_array(double data[]);
		void send_data(double d0,double d1,double d2,double d3,double d4,double d5,double d6,double d7);
		void stop();
		void start();
		void server();

		int port;
		int sample_time;
		Cppsocket s( std::string );

};

#endif /* CQSTREAMSRV_H_ */
