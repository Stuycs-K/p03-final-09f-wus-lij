#include "networking.h"

void clientLogic(int server_socket){
  char buff[BUFFER_SIZE];
  if (fgets(buff, BUFFER_SIZE, stdin) == NULL){
    perror("NULL on fgets");
    exit(1);
  }
}

int main(int argc, char *argv[] ) {
  // char* IP = "127.0.0.1";
  char* IP = "149.89.40.107";
  //107 RIGHT 108 LEFT
  if(argc>1){
    IP=argv[1];
  }
  requestName();
  int server_socket = client_tcp_handshake(IP);
  printf("Connected!\n");
  clientLogic(server_socket);
}
