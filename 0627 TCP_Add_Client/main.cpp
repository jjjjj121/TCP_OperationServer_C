#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <winsock2.h>
#include <string>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main()
{
	WSAData Winsock;

	//윈속 초기화
	WSAStartup(MAKEWORD(2, 2), &Winsock);

	//주소 입력
	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN ServerADDR;
	memset(&ServerADDR, 0, sizeof(SOCKADDR_IN));

	ServerADDR.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerADDR.sin_port = htons(5001);
	ServerADDR.sin_family = PF_INET;



	if (connect(ServerSocket, (SOCKADDR*)&ServerADDR, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		cout << "Connet Failed" << endl;
		exit(-1);
	}


	while (true)
	{



		int ResultA = 0;
		int ResultB = 0;
		int ResultC = 0;
		int ResultD = 0;
		string ASendMessage;


		cout << "숫자 입력 : ";
		getline(cin, ASendMessage);
		send(ServerSocket, ASendMessage.c_str(), strlen(ASendMessage.c_str()), 0);


		cout << "더 할 숫자 입력 : ";
		getline(cin, ASendMessage);
		send(ServerSocket, ASendMessage.c_str(), strlen(ASendMessage.c_str()), 0);



		char RecvMessage[1024] = {};

		recv(ServerSocket, RecvMessage, sizeof(RecvMessage), 0);
		
		memcpy(&ResultA, RecvMessage, 4);
		memcpy(&ResultB, &RecvMessage[4], 4);
		memcpy(&ResultC, &RecvMessage[8], 4);
		memcpy(&ResultD, &RecvMessage[12], 4);

		cout <<"결과값 : " << RecvMessage << endl;

		
		

	}


	//종료
	closesocket(ServerSocket);
	


	WSACleanup;


	return 0;
}