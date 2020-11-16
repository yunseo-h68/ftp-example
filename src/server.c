#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "ftp_socket.h"

int main(int argc, char *argv[])
{
	int serv_sock = 0;
	int clnt_sock = 0;

	socklen_t clnt_addr_size;
	struct sockaddr_in clnt_addr;

	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	// 서버를 위한 Socket 생성
	serv_sock = open_server(atoi(argv[1]));

	// 클라이언트와의 연결
	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);

	fputs("Connected to client\n\n", stdout);

	while (1) {
	
	}

	close(clnt_sock);
	close(serv_sock);
}
