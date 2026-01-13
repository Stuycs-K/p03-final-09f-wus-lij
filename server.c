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
while(1){
    n_recieve(client_socket, incoming_msg);
    printf("%s: %s", client_name, incoming_msg);

    requestInput(input, "Enter a message: ");
    n_send(client_socket, input);
  }
}
