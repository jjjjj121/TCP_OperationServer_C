#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

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
	ServerAddrIn.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerAddrIn.sin_port = htons(1234);

	connect(ServerSocket, (SOCKADDR*)&ServerAddrIn, sizeof(SOCKADDR_IN));

	char Buffer1[1024] = { 0, };
	char Buffer2[1024] = { 0, };

	scanf("%s", Buffer1);
	scanf("%s", Buffer2);

	send(ServerSocket, Buffer1, sizeof(Buffer1) - 1, 0);
	send(ServerSocket, Buffer2, sizeof(Buffer2) - 1, 0);

	char Buffer3[1024] = { 0, };
	recv(ServerSocket, Buffer3, sizeof(Buffer3), 0);

	printf("%s", Buffer3);


	WSACleanup();

	return 0;
}