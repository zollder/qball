//=========================================================================== //=========================================================================== //=========================================================================== //===========================================================================
#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <sync.h>
#include <sys/siginfo.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <sys/syspage.h>
#include "csocket.h"


void * Sender(void* arg)
{
	csocket s;
	char buff[100];
	//cout<<"This is sender."<<endl;
	s.connect(2000, "127.0.0.1");
	//s.connect(2000,"localhost");
	s.send("This is sent by sender.",24);
	s.receive(buff,100);
	cout<<buff<<endl;
	cout<<"Done from sender."<<endl;
	return 0;
}


void * Receiver(void* arg)
{
	csocket s;
	char buff[100];
	//s.connect(2000,"127.0.0.1");
	s.bindName(2000);
	s.listenSocket(1);
	s.accept();
	s.receive(buff,100);
	cout<<"from Receiver (buffer content): "<<buff<<endl;
	s.send("This is sent by receiver.",25);
	// prompt a message
	cout<<"Done from receiver."<<endl;
	sleep(1);
	return 0;
}


int main(int argc, char *argv[])
{
	pthread_t sender_ID,receiver_ID;

	pthread_create(&receiver_ID , NULL, Receiver, NULL);
	delay(500);
	pthread_create(&sender_ID , NULL, Sender, NULL);

	pthread_join(sender_ID, NULL);
	pthread_join(receiver_ID, NULL);

	return EXIT_SUCCESS;
}
