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
  char turn;
  turn = 1;
while(1){
  if(turn == 1){
    requestInput(input, "Enter a message: ");
    send(server_socket, input, strlen(input), 0);
    turn =1 - turn;
  }
  else{
    int bytes = recv(server_socket, input, BUFFER_SIZE, 0);
    if(bytes <= 0){
      break;
    }
    input[bytes] = '\0';
    printf("%s: %s", server_name, input);
    turn = 1 - turn;
  }
}

  clientLogic(server_socket);
}
