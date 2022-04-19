#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <winsock2.h>
#include <string>

#pragma warning(disable: 4996)
class Client
{
private:
	SOCKADDR_IN addr;
	SOCKET Connection;
	WORD DLLVersion;
public:
	int MaxLenMsg = 256;
	Client(const char* ip, int port);
	bool Connnect();
	void sendMsg(const char* msg, int msgLen);
	void sendMsg(const char* msg);
	char* getMsg(int& outLenMsg);
	void Disconnect();
};

class Server
{
private:
	WSAData wsaData;
	SOCKADDR_IN addr;
	WORD DLLVersion;
	SOCKET sListen;
public:
	int MaxLenMsg = 256;
	Server(const char* ip, int port);
	void start();
	SOCKET getNewConnection();
	void sendMsg(const char* msg, int msgLen, SOCKET client);
	void sendMsg(const char* msg, SOCKET client);
	char* getMsg(int& outLenMsg, SOCKET client);
	std::string getMyIp();
};