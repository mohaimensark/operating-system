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
    }
    if (id == 0)
    {
         execlp("ping","ping","-c","3","google.com",NULL);  // execlp will take all memory and time which 
         // is allocated for the whole child process
         printf("This line shouldn't print\n");
    }
    else
    {
        wait(NULL); // It won't wait for child
        printf("Success\n");
        printf("Some post processing gose here\n");

    }

    return 0;
}