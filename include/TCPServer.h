#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <queue>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

using namespace std;

#define MAXPACKETSIZE 4096

class TCPServer
{
	public:
	int sockfd, newsockfd, n, pid;
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;
	pthread_t serverThread;
	json msg;
	//static string Message;
	static queue<json> QJson;

	void setup(int port);
	string receive();
	json getMessage();
	void Send(const json& msg);
	void detach();
	void clean();

	private:
	static void * Task(void * argv);
};

#endif
