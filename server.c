#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct sockaddr SA;

#define LISTENQ 5
#define MAXLINE 1024

int open_listen_socket(int port)
{
	int listen_socket, optval = 1;
	struct sockaddr_in server_addr;

	listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);

	if (bind(listen_socket, (SA *) &server_addr, sizeof(server_addr)) < 0) {
		printf("bind faid\n");
		return -1;
	}

	listen(listen_socket, LISTENQ);
	return listen_socket;
}

void doit(int fd)
{
	char method[100], uri[100], version[100];
    char filename[100];
	char buf[1024];
	char buf2[1024];
	char buf3[1024];
	int n =0;	

	while (n = read(fd, buf, MAXLINE - 1)){
		buf[MAXLINE - 1] = '\0';
		printf("%s", buf);
		break;
	}

	sscanf(buf,"%s %s %s", method, uri, version);
	printf("method:%s.\n", method);

	sprintf(buf2, "HTTP/1.0 200 OK\r\n");
	sprintf(buf2, "%sServer:webwheel\r\n", buf2);
	sprintf(buf2, "%sContent-length:30\r\n", buf2);
	sprintf(buf2, "%sContent-type:text/html\r\n\r\n", buf2);
	n = write(fd, buf2, strlen(buf2));
	sprintf(buf3, "<html><p> myhtml </p></html>\r\n");
	n = write(fd, buf3, strlen(buf3));
}


int main(int argc, char **argv)
{
	int listenfd = 0, connfd = 0;
	int n;
	struct sockaddr_in client_addr;
	char buf[MAXLINE] = {0};
	int len = sizeof(client_addr);

	listenfd = open_listen_socket(8080);

	while (1){
		connfd = accept(listenfd, (SA *) &client_addr, &len);
		doit(connfd);
		close(connfd);
	}

	return 0;

}
