#include "networking.h"

char* rotX(char*s, int x){
  for (int i = 0; i < strlen(s); i++){
    if (isupper(s[i])){
      s[i] = (s[i] + x + 26 - 'A') % 26 + 'A';
    } else if (islower(s[i])){
      s[i] = (s[i] + x + 26 - 'a') % 26 + 'a';
    }
  }
  return s;
}

void subserver_logic(int client_socket){

}

int main(int argc, char *argv[] ) {
  int listen_socket = server_setup();


  int client_socket = server_tcp_handshake(listen_socket);

}