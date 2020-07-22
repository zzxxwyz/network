#include "udp_socket.h"
#include "string.h"

int main()
{
	UdpClient* udpClient = new UdpClient("192.168.0.111",6677);
	char buf[4096] = {};
	for(;;)
	{
		printf(">");
		gets(buf);
		udpClient->send(buf,strlen(buf)+1);
		udpClient->recv(buf,sizeof(buf));
		printf("recv:%s\n",buf);
	}
}
