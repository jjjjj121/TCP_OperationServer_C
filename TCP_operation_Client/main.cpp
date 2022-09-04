#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <winsock2.h>
#include <string>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main()
{
	WSAData Winsock;

	//���� �ʱ�ȭ
	WSAStartup(MAKEWORD(2, 2), &Winsock);

	//�ּ� �Է�
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
	
	int Result = 0;
	string ASendMessage;
	string BSendMessage;
	int ResultAdd = 0;
	int ResultMinus = 0;
	int ResultMultiply = 0;
	int ResultDivide = 0;



	cout << "���� �Է� : ";
	getline(cin, ASendMessage);
	send(ServerSocket, ASendMessage.c_str(), strlen(ASendMessage.c_str()), 0);


	cout << "�� �� ���� �Է� : ";
	getline(cin, BSendMessage);
	send(ServerSocket, BSendMessage.c_str(), strlen(BSendMessage.c_str()), 0);




	char Buffer[1024] = {};
	int RecvLength = 0;
	int TotalLength = 0;

	do
	{
		RecvLength = recv(ServerSocket, &Buffer[TotalLength], sizeof(Buffer)- TotalLength, 0);
		TotalLength += RecvLength;
	} while (TotalLength < 16);


	memcpy(&ResultAdd, Buffer, 4);
	memcpy(&ResultMinus, &Buffer[4], 4);
	memcpy(&ResultMultiply, &Buffer[8], 4);
	memcpy(&ResultDivide, &Buffer[12], 4);
	

	cout << "+ : " << ResultAdd << endl;
	cout << "- : " << ResultMinus << endl;
	cout << "* : " << ResultMultiply << endl;
	cout << "/ : " << ResultDivide << endl;



	//����

	closesocket(ServerSocket);


	WSACleanup;


	return 0;
}