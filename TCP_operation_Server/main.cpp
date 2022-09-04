#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <winsock2.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

using namespace std;


int Add(int A, int B)
{

	return A + B;

}

int main()
{

	//Winsock 초기화

	WSAData Winsock;

	if (WSAStartup(MAKEWORD(2, 2), &Winsock) != 0)
	{

		cout << "WSAStartup Failed" << endl;
		exit(-1);

	}


	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "Create socket Failed" << endl;
		exit(-1);
	}


	//소켓 주소 구조체 생성/ 초기화
	SOCKADDR_IN ServerADDR;
	memset(&ServerADDR, 0, sizeof(SOCKADDR_IN));


	//소켓 주소 데이터 입력
	ServerADDR.sin_family = PF_INET;
	ServerADDR.sin_addr.s_addr = htonl(INADDR_ANY);
	ServerADDR.sin_port = htons(5001);




	if (bind(ServerSocket, (SOCKADDR*)&ServerADDR, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		cout << "Bind Failed" << endl;
		exit(-1);
	}

	SOCKADDR_IN ClientADDR;
	int ClientADDRLen = sizeof(ClientADDR);
	SOCKET ClientSocket;

	if (listen(ServerSocket, 0) == SOCKET_ERROR)
	{
		cout << "Listen Failed" << endl;
		exit(-1);
	}




	char RecvMessageA[1024] = {};
	char RecvMessageB[1024] = {};

	char Buffer[1024] = {};
	char ResultAdd[1024] = {};
	char ResultMinus[1024] = {};
	char ResultMultiply[1024] = {};
	char ResultDivide[1024] = {};

	int atoiNumA = 0;
	int atoiNumB = 0;
	int Result = 0;
	int SendLegth = 0;

	while (true)
	{

		ClientSocket = accept(ServerSocket, (SOCKADDR*)&ServerADDR, &ClientADDRLen);

		if (ClientSocket == SOCKET_ERROR)
		{
			cout << "Accept Failed" << endl;
			exit(-1);
		}

		//데이터 수신

		recv(ClientSocket, RecvMessageA, sizeof(RecvMessageA), 0);
		cout << RecvMessageA << endl;

		atoiNumA = atoi(RecvMessageA);
		

		recv(ClientSocket, RecvMessageB, sizeof(RecvMessageB), 0);
		cout << RecvMessageB << endl;

		atoiNumB = atoi(RecvMessageB);



		Result = atoiNumA + atoiNumB;
		memcpy(Buffer, &Result, 4);

		Result = atoiNumA - atoiNumB;
		memcpy(&Buffer[4], &Result, 4);

		Result = atoiNumA * atoiNumB;
		memcpy(&Buffer[8], &Result, 4);

		Result = atoiNumA / atoiNumB;
		memcpy(&Buffer[12], &Result, 4);
		



		//데이터 송신

		for (int i = 0; i < 16; ++i)
		{
			send(ClientSocket, &Buffer[i], 1, 0);
		}
		
		

		//closesocket(ClientSocket);

	}

	//종료
	closesocket(ClientSocket);
	closesocket(ServerSocket);


	WSACleanup;


	return 0;
}


