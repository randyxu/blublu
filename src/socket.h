#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <sys/types.h>  /* basic system data types */
#include <sys/socket.h> /* basic socket definitions */
#include <netinet/in.h> /* sockaddr_in{} and other Internet defns */

#define LISTENQ  1024  /* Second argument to listen() */
typedef struct sockaddr SA;


/* Sockets interface wrappers */
int Socket(int domain, int type, int protocol);
void Setsockopt(int s, int level, int optname, const void *optval, int optlen);
void Bind(int sockfd, struct sockaddr *my_addr, int addrlen);
void Listen(int s, int backlog);
int Accept(int s, struct sockaddr *addr, socklen_t *addrlen);
void Connect(int sockfd, struct sockaddr *serv_addr, int addrlen);
/* Client/server helper functions */
//int open_clientfd(char *hostname, int portno);
int open_listenfd(int portno);
/* Wrappers for client/server helper functions */
//int Open_clientfd(char *hostname, int port);
int Open_listenfd(int port);
int make_socket_nblk(int fd);
#endif
