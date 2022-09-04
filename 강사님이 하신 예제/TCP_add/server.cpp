#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")


int main()
{
	WSAData wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN ServerAddrIn;
	memset(&ServerAddrIn, 0, sizeof(SOCKADDR_IN));
	ServerAddrIn.sin_family = PF_INET;
	ServerAddrIn.sin_addr.s_addr = INADDR_ANY;
	ServerAddrIn.sin_port = htons(1234);

	bind(ServerSocket, (SOCKADDR*)&ServerAddrIn, sizeof(SOCKADDR_IN));

	listen(ServerSocket, 0);

	SOCKADDR_IN ClientAddrIn;
	memset(&ClientAddrIn, 0, sizeof(SOCKADDR_IN));
	int ClientAddrInSize = sizeof(SOCKADDR_IN);

	SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddrIn, &ClientAddrInSize);

	char Buffer1[1024] = { 0, };
	char Buffer2[1024] = { 0, };
	recv(ClientSocket, Buffer1, sizeof(Buffer1) - 1, 0);
	recv(ClientSocket, Buffer2, sizeof(Buffer2) - 1, 0);

	int Number1 = atoi(Buffer1);
	int Number2 = atoi(Buffer2);
	int Number3 = Number1 + Number2;
	char Buffer3[1024] = { 0, };

	_itoa(Number3, Buffer3, 10);

	send(ClientSocket, Buffer3, sizeof(Buffer3), 0);

	printf("%d", Number3);


	WSACleanup();

	return 0;
}