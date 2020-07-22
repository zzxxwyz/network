#include "tcp_socket.h"

int main()
{
	TcpServer* tcpServer = new TcpServer("192.168.0.111",6688);
	TcpSocket* tcpSocket = tcpServer->accept();
	char buf[4096] = {};
	for(;;)
	{
		tcpSocket->recv(buf,sizeof(buf));
		printf("recv:%s\n",buf);
		tcpSocket->send(buf);
	}
}
