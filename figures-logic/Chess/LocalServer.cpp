//#include "LocalServer.h"
//
////Class Client
//Client::Client(const char* ip, int port)
//{
//	WSAData wsaData;
//	DLLVersion = MAKEWORD(2, 1);
//	if (WSAStartup(DLLVersion, &wsaData) != 0)
//	{
//		exit(1);
//	}
//	addr.sin_addr.s_addr = inet_addr(ip);
//	addr.sin_port = htons(port);
//	addr.sin_family = AF_INET;
//}
//bool Client::Connnect()
//{
//	Connection = socket(AF_INET, SOCK_STREAM, NULL);
//	return connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) == 0;
//}
//void Client::sendMsg(const char* msg, int msgLen)
//{
//	send(Connection, msg, msgLen, NULL);
//}
//void Client::sendMsg(const char* msg)
//{
//	send(Connection, msg, MaxLenMsg, NULL);
//}
//char* Client::getMsg(int& outLenMsg)
//{
//	outLenMsg = -1;
//	char* msg = new char[MaxLenMsg];
//	recv(Connection, msg, MaxLenMsg, NULL);
//	for (int i = 0; i < MaxLenMsg; i++)
//		if (msg[i] == '\0') outLenMsg = i;
//	if (outLenMsg == -1) outLenMsg = MaxLenMsg;
//	return msg;
//}
//void Client::Disconnect()
//{
//	closesocket(Connection);
//}
//
//// class Server
//Server::Server(const char* ip, int port)
//{
//	DLLVersion = MAKEWORD(2, 1);
//	if (WSAStartup(DLLVersion, &wsaData) != 0)
//	{
//		exit(1);
//	}
//	addr.sin_addr.s_addr = inet_addr(ip);
//	addr.sin_port = htons(port);
//	addr.sin_family = AF_INET;
//}
//void Server::start()
//{
//	sListen = socket(AF_INET, SOCK_STREAM, NULL);
//	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
//	listen(sListen, SOMAXCONN);
//}
//SOCKET Server::getNewConnection()
//{
//	int sizeofaddr = sizeof(addr);
//	return accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
//}
//void Server::sendMsg(const char* msg, int msgLen, SOCKET client)
//{
//	send(client, msg, msgLen, NULL);
//}
//void Server::sendMsg(const char* msg, SOCKET client)
//{
//	send(client, msg, MaxLenMsg, NULL);
//}
//char* Server::getMsg(int& outLenMsg, SOCKET client)
//{
//	outLenMsg = -1;
//	char* msg = new char[MaxLenMsg];
//	recv(client, msg, MaxLenMsg, NULL);
//	for (int i = 0; i < MaxLenMsg && msg[i] != '\0'; i++)
//		outLenMsg = i;
//	if (outLenMsg == -1) outLenMsg = MaxLenMsg;
//	return msg;
//}
//std::string Server::getMyIp()
//{
//	char hn[1024];
//	struct hostent* adr;
//	if (gethostname((char*)&hn, 1024))
//	{
//		return "amogus";
//	}
//	adr = gethostbyname(hn);
//	if (adr)
//	{
//		std::string re = std::to_string((unsigned char)adr->h_addr_list[0][0]);
//		for (int i = 1; i < 4; i++) re += "." + std::to_string((unsigned char)adr->h_addr_list[0][i]);
//		return re;
//	}
//	return "abobus";
//}