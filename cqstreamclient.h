/*
 * cqstreamclient.h
 *
 *  Created on: 2014-02-17
 *      Author: eugen, oleg
 */

#ifndef CQSTREAMCLIENT_H_
#define CQSTREAMCLIENT_H_

class cqstreamclient
{
private:
	pthread_t thread_id;
	pthread_mutex_t mutex;

	int stop_req;
	double rcv_data[100];
	bool is_data_copied2buff, is_data_sent;
	friend void * thread_stud(void* arg);
public:
	int port;
	int sample_time;
	int ch_size;
	char hostaddress[200];
	cppsocket s;

	cqstreamclient(char * hostaddress, int port,int sample_time,int ch_size);
	~cqstreamclient();

	int new_data_is_sent();
	void get_data_array(double * databuff);
	double get_data(int i);
	void stop();
	void start();
	void client();

};

#endif /* CQSTREAMCLIENT_H_ */
