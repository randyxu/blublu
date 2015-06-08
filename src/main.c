/*
 * event_loop
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "blublu.h"
#include "socket.h"
#include "rio.h"
#include "epoll.h"
#include "error.h"

int main(int argc, char *argv[])
{
	int epfd;
	int listenfd, connfd;
	int n, i;	
	socklen_t addrlen;	
	struct sockaddr_in clientaddr;
	struct epoll_event event;

	printf("Welcome to BluBlu!\n");
	
	addrlen = sizeof(clientaddr);
	listenfd = Open_listenfd(8080);
	make_socket_nblk(listenfd);
	epfd = epoll_create(0);	
printf("epfd = %d, listen fd = %d.\n", epfd, listenfd);
	event.data.fd = listenfd;
	event.events = EPOLLIN | EPOLLET;

	epoll_add(epfd, listenfd, &event);

	while (1) {
        n = epoll_wait(epfd, events, MAXEVENTS, -1);

        for (i = 0; i < n; i++) {
        	if ((events[i].events & EPOLLERR) ||
		        (events[i].events & EPOLLHUP) ||
		        (!(events[i].events & EPOLLIN))) {
				/* An error has occured on this fd, or the socket is not ready for reading */
			    unix_error( "epoll error");
			    close (events[i].data.fd);
			    continue;
			} else if (events[i].data.fd == listenfd) {
				/* liseten fd */
				connfd = Accept(listenfd, (SA *)&clientaddr, &addrlen);
				if (connfd < 0)
					break; /* errno == EAGAIN) || (errno == EWOULDBLOCK) || other error, anyway, we break.*/
				else {
					/* handle new connection*/
					make_socket_nblk(listenfd);
					event.data.fd = listenfd;
					event.events = EPOLLIN | EPOLLET;
					epoll_add(epfd, listenfd, &event);
					/* TODO: handling*/
				}
				continue;
			} else {
				/* connected fd */
				/* read data and provide http service*/
				/* serve_client(client_fd)*/

				continue;
			}

		}

	}
	free (events);
    close (listenfd);

	return 0;
}
