#include <stdlib.h>
#include <string.h>
#include "ftp_command.h"

/* 문자열로 된 명령의 상수값을 반환한다. */
int str_to_cmd(const char *str)
{
	if (!strcmp(str, "cd")) return CMD_CD;
	else if (!strcmp(str, "ls")) return CMD_LS;
	else if (!strcmp(str, "get")) return CMD_GET;
	else if (!strcmp(str, "put")) return CMD_PUT;
	else if (!strcmp(str, "mget")) return CMD_MGET;
	else if (!strcmp(str, "mput")) return CMD_MPUT;
	else if (!strcmp(str, "close")) return CMD_CLOSE;
	return CMD_NONE;
}

/* 명령어 상수를 명령어 문자열로 변환한다. */
const char* cmd_to_str(int cmd)
{
	switch (cmd) {
		case CMD_CLOSE:
			return "close";
		case CMD_CD:
			return "cd";
		case CMD_LS:
			return "ls";
		case CMD_GET:
			return "get";
		case CMD_PUT:
			return "put";
		case CMD_MGET:
			return "mget";
		case CMD_MPUT:
			return "mput";
	}
	return "none";
}

/* 문자열로 된 명령을 command 구조체로 변환한다. */
struct command* new_command(char *str)
{
	int i = 0;
	char *temp_ptr = NULL;
	char *command = NULL;
	struct command *cmd = (struct command*)malloc(sizeof(struct command));

	// 명령 문자열을 코드로 변환
	command = strtok(str, " ");
	cmd->code = str_to_cmd(command);

	// 인자 파싱
	// 문자열을 공백을 기준으로 자른 후 argv 필드에 복사
	temp_ptr = strtok(NULL, " ");
	for (i = 0; temp_ptr != NULL && i < ARG_MAX_COUNT; i++) {
		if (strlen(temp_ptr) + 1 > ARG_MAX_SIZE) {
			// 인자의 길이가 너무 길 경우 오류
			cmd->code = ARG_SIZE_OVER;
			return cmd;
		}
		strncpy(cmd->argv[i], temp_ptr, strlen(temp_ptr) + 1);
		temp_ptr = strtok(NULL, " ");
	}

	// 인자의 개수
	cmd->argc = i;

	return cmd;
}
