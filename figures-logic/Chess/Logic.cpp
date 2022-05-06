#include <string>
#include <winsock2.h>
#include "LocalServer.h"
using namespace std;

Server server("127.0.0.1", 1111);
Client client("127.0.0.1", 1111);
SOCKET cl;
bool isServer = false;

void CreateServer(string ip, int port)
{
	server = Server(ip.c_str(), port);
	isServer = true;
	server.start();
	cl = server.getNewConnection();
}
void CreateClient(string ip, int port)
{
	client = Client(ip.c_str(), port);
	client.Connnect();
}
void Send(char lastPos, char newPos)
{
	if (isServer) server.sendMsg(string({ (char)lastPos, (char)newPos, '\0' }).c_str(), cl);
	else client.sendMsg(string({ (char)lastPos, (char)newPos, '\0' }).c_str());
}
string Get()
{
	char* msg;
	int lenMsg;
	if (isServer) msg = server.getMsg(lenMsg, cl);
	else msg = client.getMsg(lenMsg);
	return string(msg);
}