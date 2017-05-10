#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFFER_SIZE 1500
#define on_error(...){fprintf(stderr,__VA_ARGS__);fflush(stderr); exit(1);}
int main(int argc, char *argv[]){
  if (argc < 2) on_error("Usage: %s [port]\n", argv[0]);

  int port = atoi(argv[1]);

  int client_fd, err;
  struct sockaddr_in server, client;
  char buf[BUFFER_SIZE];

  client_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (client_fd < 0) on_error("Could not create socket\n");

  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  int opt_val = 1;
  //setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof opt_val);

  err = bind(client_fd, (struct sockaddr *) &server, sizeof(server));
  if (err < 0) on_error("Could not bind socket\n");

  while (1) {
    socklen_t client_len = sizeof(client);
    socklen_t server_len = sizeof(server);
    //client_fd = accept(client_fd, (struct sockaddr *) &client, &client_len);

    //if (client_fd < 0) on_error("Could not establish new connection\n");

    char message_accueil[] = "Bonjour !\n";
    //strcpy(buf, message_accueil);
    //err = send(client_fd, buf, strlen(message_accueil), 0);
    //if (err < 0) on_error("Client write failed\n");

    memset(buf, 0, BUFFER_SIZE);

    int read;
    while (1) {
      read = recvfrom(client_fd, buf, BUFFER_SIZE, 0, (struct sockaddr*) &client, (socklen_t*) &client_len);
      printf("%s", buf);
      fflush(stdout);

      //if (!read) break; // done reading
      if (read < 0) on_error("Client read failed\n");

      err = sendto(client_fd, buf, BUFFER_SIZE, 0, (struct sockaddr*) &client, sizeof(server));
      //if (err < 0) on_error("Client write failed\n");
    }
  }
  return 0;
}
