#ifndef _EPOLL_H_
#define _EPOLL_H

#include <sys/epoll.h>

#define MAXEVENTS 1024

extern struct epoll_event *events;

int epoll_create(int flags);
void epoll_add(int epfd, int fs, struct epoll_event *event);
void epoll_mod(int epfd, int fs, struct epoll_event *event);
void epoll_del(int epfd, int fs, struct epoll_event *event);
//int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);

#endif
