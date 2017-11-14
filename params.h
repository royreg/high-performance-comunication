#include <stdio.h>
#include <stdlib.h>


#define X        10000  // Number of Messages to sent
#define BUFFER_SIZE        1024  // Maximum buffer size
#define DELTA              5        //this way we decide if we finish warmup for inner calculations
#define serverPort         8080     //desired server port for connection 
#define DELTA_x            200        //this way we decide if we finish warmup for inner calculations
#define warmupRounds       15         //number of warmuprounds




void error(const char *msg)
{
    perror(msg);
    exit(1);
}