#include <iostream>
#include "TCPServer.h"
#include "common.h"

TCPServer tcp;

void * loop(void * m)
{
	LOG_INFO("enter into loop");
    pthread_detach(pthread_self());
	while(1)
	{
		srand(time(NULL));
		json j = tcp.getMessage();
		string s = j.dump();
		if( s != "null" && s != "\"\"" && \
		    s != "" && s!= "\"emp\"")
		{		
			LOG_INFO("jMessage:%s", j.dump().c_str());
			tcp.Send(j);
			tcp.clean();
		}
		usleep(1000);
	}
	tcp.detach();
	LOG_INFO("out loop");
}

int main()
{
	pthread_t msg;
	tcp.setup(11999);
	if( pthread_create(&msg, NULL, loop, (void *)0) == 0)
	{
		tcp.receive();
	}
	return 0;
}
