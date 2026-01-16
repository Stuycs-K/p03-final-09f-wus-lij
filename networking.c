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

void turn_messaging(int socket, char * socket_name, char * buff, int turn, int is_server){
  fd_set read_fds;
  int game_started = 0;
  int target_number = 0;

  while(1){

      FD_ZERO(&read_fds);
      FD_SET(STDIN_FILENO, &read_fds);
      FD_SET(socket,&read_fds);
      int i = select(socket+1, &read_fds, NULL, NULL, NULL);

      //if standard in, use fgets
      if (FD_ISSET(STDIN_FILENO, &read_fds)) {
          fgets(buff, sizeof(buff), stdin);
          buff[strlen(buff)-1]=0;
          
          if(strcmp(buff, "start") == 0 && game_started == 0 && is_server){
            game_started = 1;
            srand(time(NULL));
            target_number = rand() % 11;
            printf("Game started! Opponent has to guess 0-10.\n");
            char start_msg[20];
            sprintf(start_msg, "START:%d", target_number);
            send(socket, start_msg, strlen(start_msg), 0);
            turn = 1 - turn;
            continue;
          }
          if(turn == 1){
            send(socket, buff, strlen(buff), 0);
            if(game_started && is_number(buff)){
              int guess;
              sscanf(buff, "%d", &guess);
              printf("You: %s\n", buff);
              if(guess == target_number){
                printf("You won!\n");
                game_started = 0;
              }
              else if(guess < target_number){
                printf("Higher!\n");
              }
              else{
                printf("Lower!\n");
              }
            }
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
          
          if(strncmp(buff, "START:", 6) == 0){
            game_started = 1;
            sscanf(buff + 6, "%d", &target_number);
            printf("Game started by %s! Guess 0-10.\n", socket_name);
            turn = 1 - turn;
            printf("You: ");
            fflush(stdout);
          }
          else{
            printf("%s: %s\n", socket_name, buff);
            if(game_started && is_number(buff)){
              int guess;
              sscanf(buff, "%d", &guess);
              if(guess == target_number){
                if(is_server){
                  printf("%s won! say 'start' to play again.\n", socket_name);
                }
                else{
                  printf("%s won! wait for 'start' to play again.\n", socket_name);
                }
                game_started = 0;
              }
              else if(guess < target_number){
                printf("Higher!\n");
              }
              else{
                printf("Lower!\n");
              }
            }
            turn = 1 - turn;
            printf("You: ");
            fflush(stdout);
          }
      }
  }

}

int is_number(char* str){
  int i = 0;
  while(str[i] != '\0'){
    if(str[i] < '0' || str[i] > '9'){
      return 0;
    }
    i++;
  }
  return 1;
}