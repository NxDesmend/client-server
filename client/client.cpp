#include <iostream>
#include <unistd.h>
#include <signal.h>
#include "TCPClient.h"
#include "AboutJson.h"
#include "common.h"

TCPClient tcp;

aaaaa
void sig_exit(int s)
{
	tcp.exit();
	exit(0);
}

int getJsonPathByCurDir(string &filename){
	char buf[512] = "";
	char *str = getcwd(buf, 512);
	if(!str){
		LOG_INFO("getcwd error!");
		return -1;
	}
	string cwpath = str;
    filename = cwpath + "/../jsonfile/message.json";
	return 0;
}

int main(int argc, char *argv[])
{
	signal(SIGINT, sig_exit);

	tcp.setup("127.0.0.1",11999);
	AboutJson aj;
	string filename = "";
	getJsonPathByCurDir(filename);
	aj.readFile(filename);
	LOG_INFO("jMessage:%s", aj.getjMessage().dump().c_str());
	tcp.Send(aj.getjMessage());
	string rec = tcp.receive();
	if( rec != "" )
	{
		cout << "Server Response:" << rec << endl;
	}
	while(1);

	return 0;
}
