#include "tcp_socket.h"

int main()
{
	TcpClient* tcpClient = new TcpClient("192.168.0.111",6565);
	char buf[4096] = {};
	for(;;)
	{
		printf(">");
		gets(buf);
		tcpClient->send(buf);
		tcpClient->recv(buf,sizeof(buf));
		printf("recv:%s\n",buf);
	}
}
