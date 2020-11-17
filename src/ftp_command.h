#ifndef FTP_COMMAND_H
#define FTP_COMMAND_H

#define ARG_MAX_COUNT 1024
#define ARG_MAX_SIZE  1024

#define ARG_SIZE_OVER -1
#define CMD_NONE       0
#define CMD_CD         1
#define CMD_LS         2
#define CMD_GET        3
#define CMD_PUT        4
#define CMD_MGET       5
#define CMD_MPUT       6
#define CMD_CLOSE      7

struct command {
	int code;
	int argc;
	char argv[ARG_MAX_COUNT][ARG_MAX_SIZE];
};

int str_to_cmd(const char *str);
const char* cmd_to_str(int cmd);
struct command* new_command(char *str);

#endif
