#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  
    int id = fork();
    if(id==0)
    {
        sleep(1);
    }
    printf("Process ID: %d\n", getpid());
    printf("Parent process ID: %d\n", getppid());
    printf("%d \n",id);

    int res=wait(NULL);
    if(res==-1)
    {
        printf("NO children to wait for\n");
    }
    else
    {
        printf("End of execution %d\n",res);
    }
    return 0;
}