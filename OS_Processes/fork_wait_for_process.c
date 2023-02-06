#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// call fork once , then I want print number 1 to 10. first 5 should be printed by child process.And others
// should be printed by the main process
int main(int argc, char *argv[])
{
  
    int id2 = fork();
    int n;
    if (id2 == 0)
    {
        n = 1;
    }
    else
    {
        n = 6;
    }

    if(id2!=0)
       wait();

    //  The wait function suspends the execution of the parent process until one of its child processes terminates

    for(int i = n;i<n+5;i++)
    { 
        
        printf("%d ",i);
     
       
    }

    if(id2!=0)
    printf("Hello world\n"); 
    fflush(stdout);


        // fflush(stdout) is used to flush the output buffer of the stdout stream. The output buffer is a buffer in memory that holds the data to be written to a file or other output stream. In normal circumstances, the output buffer is flushed automatically when it is full or when the program terminates.
}