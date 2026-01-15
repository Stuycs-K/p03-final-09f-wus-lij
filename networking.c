#include "networking.h"

/*Create and bind a socket.
* Place the socket in a listening state.
* returns the socket descriptor
*/
int server_setup() {
  //setup structs for getaddrinfo
  struct addrinfo * hints;
  struct addrinfo * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints -> ai_family = AF_INET;
  hints -> ai_socktype = SOCK_STREAM;
  hints -> ai_flags = AI_PASSIVE;
  getaddrinfo(NULL, PORT, hints, &results);
  //create the socket

  int clientd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);//store the socket descriptor here

  //this code should get around the address in use error
  int yes = 1;
  int sockOpt =  setsockopt(clientd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
  err(sockOpt,"sockopt  error");

  //bind the socket to address and port
  bind(clientd, results->ai_addr, results->ai_addrlen);
  //set socket to listen state
  listen(clientd, BUFFER_SIZE);


  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);

  return clientd;
}

/*Accept a connection from a client
 *return the socket descriptor for the new socket connected to the client
 *blocks until connection is made.
 */
int server_tcp_handshake(int listen_socket){
    int client_socket;
    socklen_t sock_size;
    struct sockaddr_storage client_address;
    sock_size = sizeof(client_address);
    //accept() the client connection
    client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
    printf("%s\n", "ACCEPTED");
    return client_socket;
}

/*Connect to the server
 *return the to_server socket descriptor
 *blocks until connection is made.*/
int client_tcp_handshake(char * server_address) {

  //getaddrinfo
  struct addrinfo * hints;
  struct addrinfo * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints -> ai_family = AF_INET;
  hints -> ai_socktype = SOCK_STREAM;
  hints -> ai_flags = AI_PASSIVE;
  getaddrinfo(server_address, PORT, hints, &results);
  //create the socket
  int serverd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);//store the socket descriptor here

  //connect() to the server
  connect(serverd, results->ai_addr, results->ai_addrlen);
  free(hints);
  freeaddrinfo(results);

  return serverd;
}
void requestInput(char * buff, char * prompt){
  printf("%s", prompt);
  fflush(stdout);
  fgets(buff, BUFFER_SIZE - 1, stdin);
  return buff;
}
void requestName(char * buff){
  requestInput(buff, "Enter your name: ");
  printf("%s\n", "Waiting for other player...");
}
void err(int i, char*message){
  if(i < 0){
	  printf("Error: %s - %s\n",message, strerror(errno));
  	exit(1);
  }
}

void game_logic(){ // guess a number
  char buff[BUFFER_SIZE];
  requestInput(buff, "Enter a number: ");
}

char* cut_string(char* str){
  size_t t = strcspn(str, "\n");
  str[t] = '\0';
}
void n_send(int outside_socket, char* buff){
  send(outside_socket, buff, strlen(buff), 0);
}
char* n_recieve(int outside_socket, char* buff){
  int bytes = recv(outside_socket, buff, BUFFER_SIZE, 0);
  if (bytes <= -1){
    perror("RECV errno:");
  } else if (bytes == 0){
    printf("Connection closed.\n");
  }
  buff[bytes] = '\0';
  return buff;
}

void turn_messaging(int socket, char * socket_name, char * buff, int turn){
  fd_set read_fds;
  int start = 0;

  while(1){

      FD_ZERO(&read_fds);
      FD_SET(STDIN_FILENO, &read_fds);
      FD_SET(socket,&read_fds);
      int i = select(socket+1, &read_fds, NULL, NULL, NULL);

      //if standard in, use fgets
      if (FD_ISSET(STDIN_FILENO, &read_fds)) {
          fgets(buff, sizeof(buff), stdin);
          buff[strlen(buff)-1]=0;
          if(turn == 1){
            if(strcmp(buff, "turn") == 0 && start == 0){
              printf("word detected. the game will now start\n");
              start = 1;
            }
            send(socket, buff, strlen(buff), 0);
            turn =1 - turn;
          }
          else{
            printf("It's not your turn! It is %s's turn right now.\n", socket_name);
          }

      }
      // if socket
      if (FD_ISSET(socket, &read_fds)) {
          int bytes = recv(socket, buff, BUFFER_SIZE, 0);
          if(bytes <= 0){
            break;
          }
          buff[bytes] = '\0';
          printf("%s: %s\n", socket_name, buff);
          turn = 1 - turn;
          printf("You: ");
          fflush(stdout);
      }
  }
}
