#include <sys/types.h >
#include <sys/socket.h >
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv[]){
  int sokcfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent  *server;

  char buffer[256];

  if(argc<3){
    fprintf(stderr, "usage %s hostname port\n", argv[0]);
    return(0);
  }
  portno = atoi(argv[2]);

  // Create a socket point
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if(sockfd < 0)
  {
    perror("ERROR opening socket");
    return(1);
  }
  server = gethostbyname(argv[1]);

  if(server ==NULL){
    fprintf(stderr, "ERROR, no such host\n");
    return(0);
  }

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family=AF_INET;
  memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
  serv_addr.sin_port = htons(portno);

}
