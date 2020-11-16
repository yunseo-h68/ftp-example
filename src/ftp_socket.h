#ifndef FTP_SOCKET_H
#define FTP_SOCKET_H

#define SOCKET_ERR  -2
#define BIND_ERR    -3
#define LISTEN_ERR  -4
#define CONNECT_ERR -5

int open_server(int port);
int open_connection(const char *host, int port);

#endif
