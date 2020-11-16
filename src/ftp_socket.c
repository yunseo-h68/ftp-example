#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "ftp_socket.h"

/* 소켓을 생성하고 bind, listen 등의 사전 작업을 수행한 후, 소켓의 fd 반환 */
int open_server(int port)
{
	int serv_sock = 0;
	struct sockaddr_in serv_addr;

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1) {
		return SOCKET_ERR;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

	if (bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
		return BIND_ERR;
	}

	if (listen(serv_sock, 5) == -1) {
		return LISTEN_ERR;
	}

	return serv_sock;
}

/* 소켓을 생성하고 서버에 connect 작업을 수행한 후, 소켓의 fd 반환 */
int open_connection(const char *host, int port)
{
	int sock = 0;
	struct sockaddr_in serv_addr;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		return SOCKET_ERR;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(host);
	serv_addr.sin_port = htons(port);

	if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
		return CONNECT_ERR;
	}

	return sock;
}

