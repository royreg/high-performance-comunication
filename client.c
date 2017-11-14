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
    printf("%d  %d  microseconds\n",msgSize,timeInMicroSeconds);
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

    

    //we start sends messages to the server 
    //after each message we calculate the difference about the time of the round trip
    //after the gap is less then DELTA we know we pass the overhead and can start the calculation
    //can see Also the server code for the warmup
    
    for(int num=1;num<=1024;num = num << 1){
    
    //initialize message to sent
    memset(buffer,'a',num );



     //handels warmup rounds
     transitionTime=warmupRound(sockfd,buffer,&tv1,&tv2,1);

    //  while(warmup){
    //     //printf("pervtime is: %d \n" ,transitionTime);
    //     int temp =  warmupRound(sockfd,buffer,&tv1,&tv2,1);
    //     if(transitionTime-temp < DELTA){
    //         printf("endddd\n");
    //         warmup=0;
    //         bzero(buffer,BUFFER_SIZE);
    //         write(sockfd,"a",strlen(stopString));
    //     }
    //     else{
    //         transitionTime = temp;
    //     }
    // }
   // printf("End Of warmuop\n");

    warmupRound(sockfd,buffer,&tv1,&tv2,30);


    //wait to get from server a message for accepting the  end of  the warmup;
    //read(sockfd,buffer,BUFFER_SIZE); 
    //printf("zzzz")       ;
    // for(int i=0;i<100;i++){
    //          printf("transitionTime is: %d \n" ,transitionTime);
    //     transitionTime =  warmupRound(sockfd,buffer,&tv1,&tv2,1);   
    // }
     memset(buffer,'a',num );
     int timeOfmessage= warmupRound(sockfd,buffer,&tv1,&tv2,X);
     printResoult(num,timeOfmessage);
     bzero(buffer,BUFFER_SIZE);
    



    

    }




    //printf("x is:%d \n",calculateX(sockfd,buffer,&tv1,&tv2));
    //sleep(1000000);
    //this heppend after connection
    int i;
    // for(i=1;i<BUFFER_SIZE;i=i << 1 ){
    //     printf("i is :%d",i);
    //     bzero(buffer,BUFFER_SIZE);

       
    // while(messageToSent < X){
    //     //write input to stream
    //n = write(sockfd,buffer,strlen(buffer));
    //     if (n < 0) 
    //         error("ERROR writing to socket");
    //     messageToSent++;
    
    // }
        

    // //blocking untill respond is achived to read responds
    // n = read(sockfd,buffer,BUFFER_SIZE);
    // if (n < 0) 
    //      error("ERROR reading from socket");
    // printf("%s\n",buffer);

    // }
    
    close(sockfd);
    return 0;
}

