#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netdb.h>


#ifndef NETWORKING_H
#define NETWORKING_H
#define PORT "19230"
#define BUFFER_SIZE 1024
void err(int i, char*message);
int server_setup();
int client_tcp_handshake(char*server_address);
int server_tcp_handshake(int listen_socket);
void requestInput(char* buff, char * prompt);
void requestName(char*buff);

char* cut_string(char* str);
void n_send(int outside_socket, char* buff);
char* n_recieve(int outside_socket, char* buff);

void turn_messaging(int socket, char * socket_name, char * buff, int turn, int is_server);

#endif
