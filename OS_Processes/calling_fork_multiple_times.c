#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
    pid_t pid1, pid2, pid3;
    int status;

    pid1 = fork();

    if (pid1 == 0)
    {
        // first child process
        pid2 = fork();

        if (pid2 == 0)
        {
            // second child process
            pid3 = fork();

            if (pid3 == 0)
            {
                // third child process
                printf("Third child process, pid: %d, parent: %d\n", getpid(), getppid());
                return 0;
            }
            else
            {
                // second child process
                printf("Second child process, pid: %d, parent: %d\n", getpid(), getppid());
                waitpid(pid3, &status, 0);
                return 0;
            }
        }
        else
        {
            // first child process
            printf("First child process, pid: %d, parent: %d\n", getpid(), getppid());
            waitpid(pid2, &status, 0);
            return 0;
        }
    }
    else
    {
        // parent process
        printf("Parent process, pid: %d\n", getpid());
       wait(NULL);
    }
    
    return 0;
}
