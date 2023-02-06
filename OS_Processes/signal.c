#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include<time.h>
#include<signal.h>

//signal will send notification
int main(int argc, char *argv[])
{
  
    int id = fork();
    if(id==-1){
        return 1;
    }

    if(id==0){
          while (1)
          {
            printf("some text are here\n");
          }
          
    }else{
        sleep(1);
        kill(id,SIGKILL); // sending signal for killing 
        //the child process

        wait(NULL);
    }
  
    
    return 0;
}