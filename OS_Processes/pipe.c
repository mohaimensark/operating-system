#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// FIFO
// write 512 bytes at a time in a pipe
// Read 1 byte at a time in a pipe
// fd----file descriptor
// fd[0] -> read,,,,,,,fd[1]-> write 
// pipe can be only used in same hierarchical process

int main(int argc, char *argv[])
{
  
    int fd[2];

    if(pipe(fd)==-1)
    {
        printf("Error occured with the opening the pipe\n");
        return 1;
    }

    int id=fork();

    if(id==-1){
          printf("Error occured with the fork\n");
        return 4;
    }

    if(id==0){
        close(fd[0]);
        int x;
        printf("Input a number\n");
        scanf("%d",&x);
        if((write(fd[1],&x,sizeof(int)))==-1){
            printf("Error occured with the writing the pipe\n");
            return 2;
        }
        close(fd[1]);
    }else {
        close(fd[1]);
        int y;
        if((read(fd[0],&y,sizeof(int)))==-1)
        {
             printf("Error occured with the reading the pipe\n");
             return 3;
        }
        close(fd[0]);
        printf("This is y value %d\n",y);
    }
    
    return 0;
}