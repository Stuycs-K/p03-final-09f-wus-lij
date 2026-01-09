#include "networking.h"

void clientLogic(int server_socket){
  char buff[BUFFER_SIZE];
  if (fgets(buff, BUFFER_SIZE, stdin) == NULL){
    perror("NULL on fgets");
    exit(1);
  }
}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1"; // localhost
  // char* IP = "149.89.40.107";
  //107 RIGHT 108 LEFT
  if(argc>1){
    IP=argv[1];
  }
  char client_name[BUFFER_SIZE];
  char server_name[BUFFER_SIZE];
  requestName(client_name);
  int server_socket = client_tcp_handshake(IP);
  printf("Connected!\n");
  send(server_socket, client_name, strlen(client_name), 0);
  int b = recv(server_socket, server_name, BUFFER_SIZE, 0);
  if (b > 0){
    server_name[b] = '\0';
  }
  printf("Your opponent: %s", server_name);

  char input[BUFFER_SIZE];
  char eInput[BUFFER_SIZE];
  char turn[BUFFER_SIZE];
  turn[0] = 0;
  while(1){
    if(turn[0] == 0){
      requestInput(input, "Enter a message: ");
      send(server_socket, input, strlen(input), 0);
      turn[0] = 1;
      send(server_socket, turn, strlen(turn), 0);
      int eMsg = recv(server_socket, input, BUFFER_SIZE, 0);
      printf("%s: %s", server_name, input);
    }
    printf("fetching turn\n");
    turn[0] = recv(server_socket, turn, BUFFER_SIZE, 0);
  }

  clientLogic(server_socket);
}
