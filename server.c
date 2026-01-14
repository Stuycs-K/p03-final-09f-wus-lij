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

  printf("Your opponent: %s", client_name);
  send(client_socket, server_name, strlen(server_name), 0);
  size_t t = strcspn(client_name, "\n");
  client_name[t] = '\0';

  char input[BUFFER_SIZE];
  char eInput[BUFFER_SIZE];
  char turn;
  turn = 0;

    fd_set read_fds;
    char buff[1025]="";
while(1){

    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(client_socket,&read_fds);
    int i = select(client_socket+1, &read_fds, NULL, NULL, NULL);

    //if standard in, use fgets
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
        fgets(buff, sizeof(buff), stdin);
        buff[strlen(buff)-1]=0;
        if(turn == 1){
          printf("You: ");
          send(client_socket, buff, strlen(buff), 0);
          turn= 1 - turn;
        }
        else{
          printf("It's not your turn! It is %s's turn right now.\n", client_name);
        }
    }

    // if socket
    if (FD_ISSET(client_socket, &read_fds)) {
        int bytes = recv(client_socket, buff, BUFFER_SIZE, 0);
        if(bytes <= 0){
          break;
        }
        buff[bytes] = '\0';
        printf("%s: %s\n", client_name, buff);
        turn = 1 - turn;
    }
}

}