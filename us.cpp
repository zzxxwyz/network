#include "udp_socket.h"
#include "string.h"

int main()
{
	UdpServer* udpServer = new UdpServer("192.168.0.111",6677);
	char buf[4096] = {};
	for(;;)
	{
		udpServer->recv(buf,sizeof(buf));
		printf("recv:%s\n",buf);
		udpServer->send(buf,strlen(buf)+1);
	}
}
