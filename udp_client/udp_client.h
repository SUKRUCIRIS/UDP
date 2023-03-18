#pragma once

void Create_UDP_Client(unsigned short port, const char* ip);
//creates the client, call before using the client

void Send_UDP_Message(char* message, int messagelen);
//give a string and its length, it will be sended

void Destroy_UDP_Client(void);
//destroys the client, call when you are done with the client