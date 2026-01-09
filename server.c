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

<<<<<<< HEAD
  char input[BUFFER_SIZE];
  char eInput[BUFFER_SIZE];
  char turn[BUFFER_SIZE];
  while(1){
    if(turn[0] == 1){
      requestInput(input, "Enter a message: ");
      send(client_socket, input, strlen(input), 0);
      turn[0] = 0;
      send(client_socket, turn, strlen(turn), 0);
      int eMsg = recv(client_socket, input, BUFFER_SIZE, 0);
      printf("%s: %s", client_name, input);
    }
    turn[0] = recv(client_socket, turn, BUFFER_SIZE, 0);
    printf("%s\n", turn);
  }

=======
>>>>>>> c853f83b590f8af7df5fc3eda5da71d93bda9dca
}
