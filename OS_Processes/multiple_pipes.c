#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
// A parent process and two child process will flow a
// variable x , at child 1 it will increased by 5 and
// at child 2 ,x will increased by 5;
int main(int argc, char *argv[])
{
    int fd[3][2]; // 3 process
    for (int i = 0; i < 3; i++)
    {
        if (pipe(fd[i]) < 0)
        {
            return 1;
        }
    }

    int id1 = fork();
    if (id1 < 0)
    {
        return 2;
    }

    if (id1 == 0)
    {
        // child process 1
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[2][0]);
        close(fd[2][1]);

        int x;
        if (read(fd[0][0], &x, sizeof(int)) < 0)
        {
            return 3;
        }
        x += 5;
        if (write(fd[1][1], &x, sizeof(int)) < 0)
        {
            return 4;
        }

        close(fd[0][0]);
        close(fd[1][1]);

        return 0;
    }

    int id2 = fork();
    if (id2 < 0)
    {
        return 5;
    }

    if (id2 == 0)
    {
        // child process 2
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][0]);

        int x;

        if (read(fd[1][0], &x, sizeof(int)) < 0)
        {
            return 6;
        }
        x += 5;
        if (write(fd[2][1], &x, sizeof(int)) < 0)
        {
            return 7;
        }

        close(fd[1][0]);
        close(fd[2][1]);

        return 0;
    }

    // Parent process

    close(fd[0][0]);
    close(fd[1][0]);
    close(fd[1][1]);
    close(fd[2][1]);
    int x;
    printf("Give the value of x: ");
    scanf("%d", &x);
    if (write(fd[0][1], &x, sizeof(int)) < 0)
    {
        return 8;
    }
    if (read(fd[2][0], &x, sizeof(int)) < 0)
    {
        return 9;
    }

    printf("Result is: %d\n", x);
    close(fd[0][1]);
    close(fd[2][0]);

    wait(NULL);

    return 0;
}