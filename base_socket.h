#ifndef BASE_SOCKET_H
#define BASE_SOCKET_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct sockaddr* SP;

class BaseSocket
{
protected:
	int fd;							
	socklen_t addrlen;
	struct sockaddr_in addr;
	BaseSocket(int fd):fd(fd) {}
public:
	BaseSocket(int type,const char* ip,uint16_t port)
	{
	
		fd = socket(AF_INET,type,0);
    	if(0 > fd)
    	{
        	perror("UdpServer socket");
    	}

    	addr.sin_family = AF_INET;
    	addr.sin_port = htons(port);
    	addr.sin_addr.s_addr = inet_addr(ip);
    	addrlen = sizeof(addr);
	}
};

#endif//UDP_SOCKET_H
