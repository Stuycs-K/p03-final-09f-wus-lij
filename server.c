#include "networking.h"

void subserver_logic(int client_socket){

}

int main(int argc, char *argv[] ) {
  char server_name[BUFFER_SIZE];
  char client_name[BUFFER_SIZE];
  request_input(server_name, "Enter your username: ");
  printf("Waiting for your opponent...\n");
  int listen_socket = server_setup();


  int client_socket = server_tcp_handshake(listen_socket);
  n_recieve(client_socket, client_name);
  printf("Your opponent: %s", client_name);
  n_send(client_socket, server_name);
  cut_string(client_name);

  char input[BUFFER_SIZE];
  char incoming_msg[BUFFER_SIZE];
  char turn;
  turn = 0;

    fd_set read_fds;
    char buff[1025]="";
    printf("wait for your opponent to send something!\n");
    fflush(stdout);
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
        printf("You: ");
        fflush(stdout);
        turn = 1 - turn;
    }
}

    request_input(input, "Enter a message: ");
    n_send(client_socket, input);
  }
}
