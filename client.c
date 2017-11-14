#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "params.h"
#include <sys/time.h>

int warmupRound(int sockfd,char* buffer,struct timeval* tv1,struct timeval* tv2, int iterations){
    gettimeofday(tv1,NULL);
    
    int i;
    for(i=0;i<iterations;i++){
        
        write(sockfd,buffer,strlen(buffer));
    }

    //printf("i is: %d\n",i);
    read(sockfd,buffer,1);
    gettimeofday(tv2,NULL);
    return  (tv2->tv_sec-tv1->tv_sec)*1000000 + tv2->tv_usec-tv1->tv_usec;
    //printf("transitionTime is: %d \n " ,transitionTime);

}

void printResoult(int msgSize,int timeInMicroSeconds){
    printf("%d\t%d\tmicroseconds\n",msgSize,timeInMicroSeconds);
}


int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int messageToSent=0;
    int warmup=1;
    double prevTime;
    struct timeval tv1;
    struct timeval tv2;
    int transitionTime;
    char* stopString="END";
    


    char buffer[BUFFER_SIZE];
    if (argc < 2) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = serverPort;

    //Crreate CLient socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    //Detect host server        
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    //initialize the serv_address struct for connection
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);

    //trying to connect the server
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    

    
    for(int num=1;num<=1024;num = num << 1){
    
    //initialize message to sent
    memset(buffer,'a',num );



     //handels warmup rounds
     //we chose the warmup round number manually by checking after how many messages 
     //the gap between two successors messages is not to high
     //NOTE: warmupRounds is defined in params.h
    warmupRound(sockfd,buffer,&tv1,&tv2,warmupRounds);


    //wait to get from server a message for accepting the  end of  the warmup;
    //read(sockfd,buffer,BUFFER_SIZE); 
    //printf("zzzz")       ;
    // for(int i=0;i<100;i++){
    //          printf("transitionTime is: %d \n" ,transitionTime);
    //     transitionTime =  warmupRound(sockfd,buffer,&tv1,&tv2,1);   
    // }
     memset(buffer,'a',num );

     //we chose the X by running the program on lots of X values and we chose the best result
     // we compared  the change in thorughput after X messages and took where the change is minimal
     //NOTE: X is defined in params.h
     int timeOfmessage= warmupRound(sockfd,buffer,&tv1,&tv2,X);
     printResoult(num,timeOfmessage);
     bzero(buffer,BUFFER_SIZE);
    



    

    }

    
    close(sockfd);
    return 0;
}

