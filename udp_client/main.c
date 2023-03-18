#include "udp_client.h"
#include <string.h>
#include <stdio.h>

#pragma warning(disable:4996)

int main() {
	Create_UDP_Client(8888, L"127.0.0.1");//Must be L at the start of the ip name because windows use wide char
	//I gave 127.0.0.1 as ip adress because I run the server program on the same computer
	//If you wont run on the same computer, give the ip adress of the remote computer

	char message[50] = { 0 };

	sprintf(message, "HELLO UDP");
	Send_UDP_Message(message, strlen(message));

	sprintf(message, "HOW ARE YOU?");
	Send_UDP_Message(message, strlen(message));

	Destroy_UDP_Client();
	return 0;
}