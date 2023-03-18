#pragma once

void Create_UDP_Server(unsigned short port, unsigned int messagebuffersize);
//creates the server, call before using the server

char* Get_UDP_Message(void);
//This will block the program until receiving message
//message will be printed and returned

void Destroy_UDP_Server(void);
//destroys the server, call when you are done with the server