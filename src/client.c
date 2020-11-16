#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ftp_socket.h"

int main(int argc, char *argv[])
{
	int sock = 0;

	if (argc != 3) {
		printf("Usage : %s <IP> <Port>\n", argv[0]);
		exit(1);
	}

	// 서버와 연결된 socket 생성
	sock = open_connection(argv[1], atoi(argv[2]));

	printf("Connected to %s:%s\n\n", argv[1], argv[2]);

	while(1) {

	}

	close(sock);
}
