#include "networking.h"

void clientLogic(int server_socket){
  char buff[BUFFER_SIZE];
  if (fgets(buff, BUFFER_SIZE, stdin) == NULL){
    perror("NULL on fgets");
    exit(1);
  }
}

int main(int argc, char *argv[] ) {
  // char* IP = "127.0.0.1"; // localhost
  char* IP = "149.89.40.100";
  //107 RIGHT 108 LEFT 100 MARGE
  if(argc>1){
    IP=argv[1];
  }
  char client_name[BUFFER_SIZE];
  char server_name[BUFFER_SIZE];
  requestName(client_name);
  int server_socket = client_tcp_handshake(IP);
  printf("Connected!\n");
  n_send(server_socket, client_name);
  n_recieve(server_socket, server_name);
  printf("Your opponent: %s", server_name);
  cut_string(server_name);

  char input[BUFFER_SIZE];
  char incoming_msg[BUFFER_SIZE];
  char turn;
  turn = 1;

  fd_set read_fds;
  char buff[1025]="";

  printf("kiminodebanyo! Type something...\nYou: ");
  fflush(stdout);

  turn_messaging(server_socket, server_name, buff, turn);

  clientLogic(server_socket);
}
