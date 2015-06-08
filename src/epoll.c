#include <stdlib.h>
#include "epoll.h"
#include <stdio.h>
#include "error.h"
struct epoll_event *events;

int epoll_create(int flags) {
    int fd = epoll_create1(flags);

    events = (struct epoll_event *)malloc(sizeof(struct epoll_event) * MAXEVENTS);
    return fd;
}

void epoll_add(int epfd, int fd, struct epoll_event *event) {

    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, event);
    return;
}

void epoll_mod(int epfd, int fd, struct epoll_event *event) {
    epoll_ctl(epfd, EPOLL_CTL_MOD, fd, event);
    return;
}

void epoll_del(int epfd, int fd, struct epoll_event *event) {
    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, event);
	return;
}


