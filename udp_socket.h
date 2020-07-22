#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H
#include "base_socket.h"

class UdpSocket:public BaseSocket
{
public:
	UdpSocket(const char* ip,uint16_t port):BaseSocket(SOCK_DGRAM,ip,port) {}
	
	int recv(void* buf,uint32_t len)
	{
		return recvfrom(fd,buf,len,0,(SP)&addr,&addrlen);
	}
	
	int send(void* buf,uint32_t len)
	{
		return sendto(fd,buf,len,0,(SP)&addr,addrlen);
	}
	
	int send(const char* buf)
	{
		return sendto(fd,buf,strlen(buf)+1,0,(SP)&addr,addrlen);
	}
};

class UdpServer:public UdpSocket
{
public:
	UdpServer(const char* ip,uint16_t port):UdpSocket(ip,port)
	{
		if(bind(fd,(SP)&addr,addrlen))
    	{
        	perror("UdpServer bind");
    	}
	}
};

class UdpClient:public UdpSocket
{
public:
	UdpClient(const char* ip,uint16_t port):UdpSocket(ip,port)
	{
		/*
			UDP中调用connect内核仅仅把对端ip&port记录下来
			普通的UDP发送两个报文内核做了如下:
				1:建立连结
				2:发送报文
				3:断开连结
				4:建立连结
				5:发送报文
				6:断开连结

			采用connect方式的UDP发送两个报文内核如下处理:
				1:建立连结
				2:发送报文
				3:发送报文另外一点,  每次发送报文内核都由可能要做路由查询.

			采用connect的UDP发送接受报文可以调用send,write和recv,read操作.当然也可以调用sendto,recvfrom.
		*/
		if(connect(fd,(SP)&addr,addrlen))
    	{
        	perror("UdpClient connect");
    	}
	}
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
		return ::send(fd,buf,strlen(buf)+1,0);
	}
};

#endif//UDP_SOCKET_H
