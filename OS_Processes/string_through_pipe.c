#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

// 2 processes
// 1) Child process should generates random numbers and send
// them to the parent.
// 2) Parent is going to sum all the numbers and print the result

int main(int argc, char *argv[])
{
    int fd[2];
    if (pipe(fd) == -1)
    {
        return 2;
    }

    int id = fork();

    if (id == -1)
    {
        return 1;
    }

    if (id == 0)
    {
        close(fd[0]);
        char str[200];
        printf("Input string is: \n");
        fgets(str, 200, stdin);
        str[strlen(str) - 1] = '\0';
        int n;
        n = strlen(str) + 1;
        if (write(fd[1],&n, sizeof(int)) < 0)
        {
            return 3;
        }
        if (write(fd[1], str, sizeof(char)*n) < 0)
        {
            return 3;
        }

        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        char str[200];
        int n;
        if (read(fd[0], &n,sizeof(int) ) < 0)
        {
            return 6;
        }
        if (read(fd[0], str, sizeof(char) * n) < 0)
        {
            return 4;
        }
        close(fd[0]);
        printf("The output strig is %s\n:",str);

        wait(NULL);
    }

    return 0;
}