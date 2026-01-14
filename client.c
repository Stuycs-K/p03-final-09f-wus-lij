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
  request_input(client_name, "Enter your username: ");
  printf("Waiting for your opponent...\n");
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

while(1){

    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(server_socket,&read_fds);
    int i = select(server_socket+1, &read_fds, NULL, NULL, NULL);

    //if standard in, use fgets
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
        fgets(buff, sizeof(buff), stdin);
        buff[strlen(buff)-1]=0;
        if(turn == 1){
          send(server_socket, buff, strlen(buff), 0);
          turn =1 - turn;
        }
        else{
          printf("It's not your turn! It is %s's turn right now.\n", server_name);
        }

    }
    // if socket
    if (FD_ISSET(server_socket, &read_fds)) {
        int bytes = recv(server_socket, buff, BUFFER_SIZE, 0);
        if(bytes <= 0){
          break;
        }
        buff[bytes] = '\0';
        printf("%s: %s\n", server_name, buff);
        turn = 1 - turn;
        printf("You: ");
        fflush(stdout);
    }
}

  clientLogic(server_socket);
}
