#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")


int main()
{
	WSAData wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	hostent* infos = gethostbyname("naver.com");

	for (int i = 0; infos->h_aliases[i]; ++i)
	{
		printf("alias %s\n", infos->h_aliases[i]);
	}

	for (int i = 0; infos->h_addr_list[i]; ++i)
	{
		printf("ip %s\n", inet_ntoa(*(IN_ADDR*)infos->h_addr_list[i]));
	}

	printf("address type %s", infos->h_addrtype == AF_INET ? "AF_INET" : "AF_INET6");


	WSACleanup();

	return 0;
}