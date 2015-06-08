/***********************************************************
   socket interface wrappers
   reference :CSAPP

************************************************************/
#include <string.h>       /* for bezro */
#include <unistd.h>
#include <fcntl.h>
#include "socket.h"
#include "error.h"

int Socket(int domain, int type, int protocol) 
{
	int rc;

    if ((rc = socket(domain, type, protocol)) < 0)
		unix_error("Socket error");
    return rc;
}

void Setsockopt(int s, int level, int optname, const void *optval, int optlen) 
{
    int rc;

    if ((rc = setsockopt(s, level, optname, optval, optlen)) < 0)
		unix_error("Setsockopt error");
}

void Bind(int sockfd, struct sockaddr *my_addr, int addrlen) 
{
    int rc;

    if ((rc = bind(sockfd, my_addr, addrlen)) < 0)
		unix_error("Bind error");
}

void Listen(int s, int backlog) 
{
    int rc;

    if ((rc = listen(s,  backlog)) < 0)
		unix_error("Listen error");
}

int Accept(int s, struct sockaddr *addr, socklen_t *addrlen) 
{
    int rc;

    if ((rc = accept(s, addr, addrlen)) < 0)
		unix_error("Accept error");
    return rc;
}

void Connect(int sockfd, struct sockaddr *serv_addr, int addrlen) 
{
    int rc;

    if ((rc = connect(sockfd, serv_addr, addrlen)) < 0)
		unix_error("Connect error");
}

/*  
	 * open_listenfd - open and return a listening socket on port
	  *     Returns -1 and sets errno on Unix error.
	   */
int open_listenfd(int port) 
{
    int listenfd, optval=1;
    struct sockaddr_in serveraddr;
		  
    /* Create a socket descriptor */
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return -1;
				 
    /* Eliminates "Address already in use" error from bind */
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, 
				   (const void *)&optval , sizeof(int)) < 0)
		return -1;

    /* Listenfd will be an endpoint for all requests to port
       on any IP address for this host */
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET; 
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    serveraddr.sin_port = htons((unsigned short)port); 
    if (bind(listenfd, (SA *)&serveraddr, sizeof(serveraddr)) < 0)
		return -1;

    /* Make it a listening socket ready to accept connection requests */
    if (listen(listenfd, LISTENQ) < 0)
		return -1;
    return listenfd;
}

int Open_listenfd(int port) 
{
    int rc;

    if ((rc = open_listenfd(port)) < 0)
		unix_error("Open_listenfd error");
    return rc;
}

/*
 * make a socket non blocking. 
 * If a listen socket is a blocking socket, after it comes out from epoll and accepts the last connection,
 * the next accpet will block, which is not what we want.
 */
int make_socket_nblk(int fd)
{
	int flag, rc;
	if ((flag = fcntl(fd, F_GETFL)) < 0) {
		unix_error("fcntl F_GETFL error");
		return -1;
	}

	flag |= O_NONBLOCK;

	if ((rc = fcntl(fd, F_SETFL, flag)) < 0) {
		unix_error("fcntl F_SETFL error");
		return -1;
	}

	return 0;
}
