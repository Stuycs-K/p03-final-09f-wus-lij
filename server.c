#include "networking.h"

void subserver_logic(int client_socket){

}

int main(int argc, char *argv[] ) {
  printf("%s", "Enter your name: ");
  fflush(stdout);
  char buff[BUFFER_SIZE];
  fgets(buff, BUFFER_SIZE - 1, stdin);
  printf("%s\n", "Waiting for other player...");
  int listen_socket = server_setup();


  int client_socket = server_tcp_handshake(listen_socket);

}
