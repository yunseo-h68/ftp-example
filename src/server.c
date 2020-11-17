#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "ftp_socket.h"
#include "ftp_command.h"

int main(int argc, char *argv[])
{
	int i = 0;
	int serv_sock = 0;
	int clnt_sock = 0;

	socklen_t clnt_addr_size;
	struct sockaddr_in clnt_addr;
	struct command *cmd = (struct command*)malloc(sizeof(struct command));

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
		// 명령 수신 및 로그 출력
		recv(clnt_sock, cmd, sizeof(struct command), 0);
		if (cmd->code == CMD_NONE) {
			// 정의되지 않는 명령의 경우 이후 작업을 수행하지 않고
			// 다시 명령을 수신한다.
			continue;
		}
		printf("Request : %s(%d)\n", cmd_to_str(cmd->code), cmd->code);
		printf("Args(%d) : \n", cmd->argc);
		for (i = 0; i < cmd->argc; i++) {
			printf("- \'%s\'\n", cmd->argv[i]);
		}
		printf("\n");
	}

	free(cmd);
	close(clnt_sock);
	close(serv_sock);
}
