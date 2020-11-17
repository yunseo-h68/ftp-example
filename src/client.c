#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "ftp_socket.h"
#include "ftp_command.h"

int main(int argc, char *argv[])
{
	int i = 0;
	int sock = 0;
	char c = 0;
	char buf[BUFSIZ] = {0, };
	struct command *cmd = NULL;

	if (argc != 3) {
		printf("Usage : %s <IP> <Port>\n", argv[0]);
		exit(1);
	}

	// 서버와 연결된 socket 생성
	sock = open_connection(argv[1], atoi(argv[2]));

	printf("Connected to %s:%s\n\n", argv[1], argv[2]);

	while(1) {
		// 명령을 입력받는다.
		fputs("> ", stdout);
		memset(buf, 0, BUFSIZ);
		for (i = 0; (c = getchar()) != '\n' && i < (int)BUFSIZ; i++) {
			buf[i] = c;
		}
		buf[i] = '\0';
		if (strlen(buf) <= 0) continue;

		// 입력 받은 문자열을 command 구조체로 변환
		cmd = new_command(buf);

		// 명령 정보(command 구조체)를 서버로 전송
		send(sock, cmd, sizeof(struct command), 0);
	}
	free(cmd);
	close(sock);
}
