#include "networking.h"

void subserver_logic(int client_socket){

}

int main(int argc, char *argv[] ) {
  char server_name[BUFFER_SIZE];
  char client_name[BUFFER_SIZE];
  requestName(server_name);
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

  turn_messaging(client_socket, client_name, buff, turn);

    requestInput(input, "Enter a message: ");
    n_send(client_socket, input);
  }
}
