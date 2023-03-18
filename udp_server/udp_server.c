#include "udp_server.h"
#include <stdio.h>
#include <winsock2.h>

//I made it in windows way because my computer is windows

SOCKET Socket;
struct sockaddr_in server;
char* messagebuffer = 0;
unsigned int mbuffersize = 0;
WSADATA wsa;

#pragma comment(lib,"ws2_32.lib")

void Create_UDP_Server(unsigned short port, unsigned int messagebuffersize) {
	messagebuffer = malloc(sizeof(char) * messagebuffersize);
	if (!messagebuffer) {
		printf("Not enough memory for messagebuffer.\n");
		return;
	}
	mbuffersize = messagebuffersize;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
		printf("WSAStartup Failed: %d\n", WSAGetLastError());
		return;
	}
	if ((Socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET){
		printf("socket Failed : %d\n", WSAGetLastError());
		return;
	}
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);
	if (bind(Socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR){
		printf("bind Failed : %d\n", WSAGetLastError());
		return;
	}
	printf("UDP SERVER CREATED\n");
}

void Destroy_UDP_Server(void) {
	free(messagebuffer);
	messagebuffer = 0;
	mbuffersize = 0;
	closesocket(Socket);
	WSACleanup();
	printf("UDP SERVER DESTROYED\n");
}

char* Get_UDP_Message(void) {
	if (!messagebuffer) {
		return 0;
	}
	memset(messagebuffer, '\0', mbuffersize);
	printf("UDP SERVER WAITING FOR MESSAGE\n");
	if (recvfrom(Socket, messagebuffer, mbuffersize, 0, 0, 0) == SOCKET_ERROR){
		printf("recvfrom Failed : %d\n", WSAGetLastError());
		return 0;
	}
	printf("Message: %s\n", messagebuffer);
	return messagebuffer;
}
