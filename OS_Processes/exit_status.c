#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int id = fork();

    if (id == -1)
    {
        printf("Fork creation problem\n");
        return 1;
    }
    if (id == 0)
    {
         int err = execlp("ping","ping","-c","3","google.com",NULL);  
         if(err==-1){
            printf("Could not found the program to execute\n");
            return 2;
         }
         printf("This line shouldn't print\n");
    }
    else
    {
        int wstatus;
        wait(&wstatus); // It won't wait for child

        if(WIFEXITED(wstatus)){
            int statusCode = WEXITSTATUS(wstatus);
            if(statusCode==0){
                printf("Success !\n");
            }
            else
            {
                printf("Failure with status code %d\n",statusCode);
            }
        }

      
        printf("Some post processing gose here\n");

    }

    return 0;
}