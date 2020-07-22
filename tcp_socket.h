#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H
#include "base_socket.h"

class TcpSocket:public BaseSocket
{
	
public:
	TcpSocket(int fd):BaseSocket(fd) {}
	
	TcpSocket(const char* ip,uint16_t port):BaseSocket(SOCK_STREAM,ip,port) {}
	
	int recv(void* buf,uint32_t len)
	{
		return ::recv(fd,buf,len,0);
	}	
	
	int send(void* buf,uint32_t len)
	{
		return ::send(fd,buf,len,0);
	}
	
	int send(const char* buf)
	{
		return ::send(fd,buf,strlen(buf),0);
	}
};

class TcpServer:public TcpSocket
{
public:
	TcpServer(const char* ip,uint16_t port,uint8_t listen_cnt=50):TcpSocket(ip,port)
	{
		if(bind(fd,(SP)&addr,addrlen))
    	{
        	perror("TcpServer bind");
    	}
    	
    	if(listen(fd,listen_cnt))
    	{
    		perror("TcpServer listen");
    	}
	}
	
	TcpSocket* accept(void)
	{
		int clifd = ::accept(fd,(SP)&addr,&addrlen);
		if(0 > clifd)
		{
			perror("TcpServer accept");
		}
		return new TcpSocket(clifd);
	}
};

class TcpClient:public TcpSocket
{
public:
	TcpClient(const char* ip,uint16_t port):TcpSocket(ip,port)
	{
		if(connect(fd,(SP)&addr,addrlen))
    	{
        	perror("TcpClient connect");
    	}
	}
};



#endif//TCP_SOCKET_H
