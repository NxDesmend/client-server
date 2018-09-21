#include "TCPServer.h" 
#include "common.h"

queue<json> TCPServer::QJson;

void* TCPServer::Task(void *arg)
{
    LOG_INFO("enter into Task");
	int n;
	int newsockfd = (long)arg;
	char msg[MAXPACKETSIZE];
	pthread_detach(pthread_self());
	while(1)
	{
		n=recv(newsockfd,msg,MAXPACKETSIZE,0);
		if(n==0)
		{
		   close(newsockfd);
		   break;
		}
		msg[n]=0;
		json j = json::parse(string(msg));
		j.find("header")->emplace("newsockfd", newsockfd);
		QJson.push(j);
    }
	return 0;
}

void TCPServer::setup(int port)
{
	sockfd=socket(AF_INET,SOCK_STREAM,0);
 	memset(&serverAddress,0,sizeof(serverAddress));
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
	serverAddress.sin_port=htons(port);
	bind(sockfd,(struct sockaddr *)&serverAddress, sizeof(serverAddress));
 	listen(sockfd,5);
}

string TCPServer::receive()
{
	LOG_INFO("enter into receive");
	string str;
	while(1)
	{
		socklen_t sosize  = sizeof(clientAddress);
		int newsockfd = accept(sockfd,(struct sockaddr*)&clientAddress,&sosize);
		str = inet_ntoa(clientAddress.sin_addr);
		pthread_create(&serverThread,NULL,&Task,(void *)newsockfd);
	}
	return str;
	LOG_INFO("out receive");
}

json TCPServer::getMessage()
{
	if(QJson.empty()){
		return EMP;
	}
	json j = QJson.front();
    QJson.pop();
	return j;
}

void TCPServer::Send(const json& msg)
{
	LOG_INFO("enter into Send");
	std::string smsg = msg.dump();
	int newsockfd = *(msg.find("header")->find("newsockfd"));
	send(newsockfd,smsg.c_str(),smsg.length(),0);
	LOG_INFO("out Send");
}

void TCPServer::clean()
{
	//jMessage = "";
	//msg = "";
}

void TCPServer::detach()
{
	close(sockfd);
	close(newsockfd);
} 
