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

	printf("client\n");

	int Numnber1 = 0;
	int Numnber2 = 0;

	scanf("%d", &Numnber1);
	scanf("%d", &Numnber2);

	char Buffer1[1024] = { 0, };

	connect(ServerSocket, (SOCKADDR*)&ServerAddrIn, sizeof(SOCKADDR_IN));

	memcpy(Buffer1, &Numnber1, 4);
	memcpy(&Buffer1[4], &Numnber2, 4);
	send(ServerSocket, Buffer1, 8, 0);

	char Buffer3[1024] = { 0, };
	int RecvLength = 0;
	int TotalRecvLength = 0;
	do
	{
		RecvLength = recv(ServerSocket, &Buffer3[TotalRecvLength], sizeof(Buffer3) - TotalRecvLength, 0);  // 16바이트 다 받았냐?
		printf("RecvLength : %d\n", RecvLength);
		TotalRecvLength += RecvLength;
	} while (TotalRecvLength < 16);

	int Number3 = 0;
	int Number4 = 0;
	int Number5 = 0;
	int Number6 = 0;
	memcpy(&Number3, Buffer3, 4);
	memcpy(&Number4, &Buffer3[4], 4);
	memcpy(&Number5, &Buffer3[8], 4);
	memcpy(&Number6, &Buffer3[12], 4);

	printf("%d\n", Number3);
	printf("%d\n", Number4);
	printf("%d\n", Number5);
	printf("%d\n", Number6);


	WSACleanup();

	return 0;
}