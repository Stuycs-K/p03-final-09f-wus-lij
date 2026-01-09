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
void prompt(char * buff, char * prompt){
  printf("%s", prompt);
  fflush(stdout);
  fgets(buff, BUFFER_SIZE - 1, stdin);
}
void requestName(char * buff){
  prompt(buff, "Enter your name: ");
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
<<<<<<< HEAD
  requestInput(buff, "Enter a number: ");
=======
  prompt(buff, "Enter a number: ");
>>>>>>> c853f83b590f8af7df5fc3eda5da71d93bda9dca
}
