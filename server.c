/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "params.h"



int main(int argc, char *argv[])
{
     
     int run=1;
     int messageCounter=0;
     int sockfd, newsockfd, portno;    //this are variables for client ,socket and port number
     socklen_t clilen;
     char buffer[BUFFER_SIZE];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     int warmup=1;
     int calculateX=1;
     int x=1;

     //open a new socket , AF_INET = IPv4 Internet protocols 
     //SOCK_STREAM =STreams of data and not chunk
     // third argument is for protocol , In our case the system will choose TCP for Stream Sockets
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");


     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = serverPort;
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
        fprintf(stdout,"Client Connected to socket ..\n");
        //this section is only after a client connect to the server                 
        if (newsockfd < 0) 
            error("ERROR on accept");

        int num=1;
        while(1){
            
            //waits for client to calculate the end of warmup rounds
            //while the client ends the warmup round its send "END" and the server knows it can continue
            for(int i=0;i<30;i++){
                read(newsockfd,buffer,num);
                write(newsockfd,"a",1);
                bzero(buffer,BUFFER_SIZE);
                
            }

             //printf("reach End of Warmup\n");
            // break;
            
             int counter=0;

            //wait until X messages recived
            while(counter < X){
                //printf("counter is:%d\n",counter);
                read(newsockfd,buffer,num);
                counter++;
                bzero(buffer,num);
            }
            //sends  respond to Client
            write(newsockfd,"a",1);

        
        num =num << 1;
        
        if(num>1024)
            break;
        }


     close(newsockfd);
     close(sockfd);
     return 0; 
}