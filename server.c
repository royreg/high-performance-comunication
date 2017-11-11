/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    
    
     int sockfd, newsockfd, portno;    //this are variables for client ,socket and port number
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     //cheks if prot number was entered as command line argument
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     
     //open a new socket , AF_INET = IPv4 Internet protocols 
     //SOCK_STREAM =STreams of data and not chunk
     // third argument is for protocol , In our case the system will choose TCP for Stream Sockets
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");


     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     //connect the socket to the server adress 
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");

              
     fprintf(stdout,"Server Is Listenning on Port %d..\n",portno);
     listen(sockfd,5);
     clilen = sizeof(cli_addr);

     //accept block process until a client connection is established
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    //this section is only after a client connect to the server                 
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,256);

     //read data sent from client
     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     

     //sent data back to client
     n = write(newsockfd,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);
     return 0; 
}