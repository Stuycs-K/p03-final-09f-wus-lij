#include "networking.h"

void subserver_logic(int client_socket){

}

int main(int argc, char *argv[] ) {
  char server_name[BUFFER_SIZE];
  char client_name[BUFFER_SIZE];
  requestName(server_name);
  int listen_socket = server_setup();


  int client_socket = server_tcp_handshake(listen_socket);
  int bytes = recv(client_socket, client_name, BUFFER_SIZE, 0);
  if (bytes > 0){
    client_name[bytes] = '\0';
  }

  printf("Your opponent's name is: %s", client_name);
  send(client_socket, server_name, strlen(server_name), 0);
  size_t t = strcspn(client_name, "\n");
  client_name[t] = '\0';

  char input[BUFFER_SIZE];
  char eInput[BUFFER_SIZE];
  char turn;
  turn = 0;

  fd_set read_fds;
  char buff[1025]="";
  printf("wait for your opponent to send something!\n");
  fflush(stdout);

  turn_messaging(client_socket, client_name, buff, turn, 1);

}
