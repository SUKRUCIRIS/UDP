#include "udp_client.h"
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

//I made it in windows way because my computer is windows

SOCKET Socket = 0;
WSADATA wsa;
struct sockaddr_in dest;
struct sockaddr_in local;
int destsize = 0;

#pragma comment(lib,"ws2_32.lib")

void Create_UDP_Client(unsigned short port, const char* ip) {
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("WSAStartup Failed : %d\n", WSAGetLastError());
		return;
	}
	if ((Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) {
		printf("socket Failed : %d\n", WSAGetLastError());
		return;
	}
	memset((char*)&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_port = htons(port);
	if (InetPtonW(AF_INET, (PCWSTR)ip, &(dest.sin_addr)) != 1) {
		printf("InetPtonW Failed : %d\n", WSAGetLastError());
		return;
	}
	destsize = sizeof(dest);

	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(0);

	if (bind(Socket, (struct sockaddr*)&local, sizeof(local)) == SOCKET_ERROR) {
		printf("bind Failed : %d\n", WSAGetLastError());
		return;
	}
	printf("UDP CLIENT CREATED\n");
}

void Send_UDP_Message(char* message, int messagelen) {
	if (sendto(Socket, message, messagelen, 0, (struct sockaddr*)&dest, destsize) == SOCKET_ERROR) {
		printf("sendto failed : %d\n", WSAGetLastError());
	}
	else {
		printf("Message sended: %s\n", message);
	}
	return;
}

void Destroy_UDP_Client(void) {
	closesocket(Socket);
	WSACleanup();
	printf("UDP CLIENT DESTROYED\n");
}