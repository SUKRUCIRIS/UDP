#include "udp_server.h"

int main() {
	Create_UDP_Server(8888, 1024);
	while (1) {
		Get_UDP_Message();
	}
	Destroy_UDP_Server();
	return 0;
}