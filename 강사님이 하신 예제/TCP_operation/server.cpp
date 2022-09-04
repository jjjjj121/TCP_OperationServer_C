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

	printf("Server\n");

	while (1)
	{
		SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddrIn, &ClientAddrInSize);
		printf("connected\n");

		char Buffer1[1024] = { 0, };
		int RecvLength = 0;
		int TotalRecvLength = 0;
		do
		{
			RecvLength = recv(ClientSocket, &Buffer1[TotalRecvLength], sizeof(Buffer1) - TotalRecvLength, 0);  // 16바이트 다 받았냐?
			printf("RecvLength : %d\n", RecvLength);
			TotalRecvLength += RecvLength;
		} while (TotalRecvLength < 8);


		int Number1 = 0;
		int Number2 = 0;
		memcpy(&Number1, &Buffer1[0], 4);
		memcpy(&Number2, &Buffer1[4], 4);

		int Number3 = Number1 + Number2;
		int Number4 = Number1 - Number2;
		int Number5 = Number1 * Number2;
		int Number6 = Number1 / Number2;

		char Buffer3[1024] = { 0, };

		memcpy(Buffer3, &Number3, 4);
		memcpy(&Buffer3[4], &Number4, 4);
		memcpy(&Buffer3[8], &Number5, 4);
		memcpy(&Buffer3[12], &Number6, 4);

		for (int i = 0; i < 16; ++i)
		{
			int SentLength = send(ClientSocket, &Buffer3[i], 1, 0);
			//printf("Sent Length : %d\n", SentLength);

			//for (int j = 0; j < 1000000; ++j) //delay 한바이트씩 늦게 온다.
			//{

			//}
		}

		closesocket(ClientSocket);
	}

	closesocket(ServerSocket);


	WSACleanup();

	return 0;
}