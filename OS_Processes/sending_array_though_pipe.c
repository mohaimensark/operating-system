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
        int n;
        int arr[10];
        srand(time(NULL));

        n = rand() % 10 + 1;
        int i;
        printf("The initial array:\n");
        for (i = 0; i < n; i++)
        {
            arr[i] = rand() % 11;
            printf("%d\n", arr[i]);
        }
        if (write(fd[1], &n, sizeof(int)) < 0)
        {
            return 5;
        }

        if (write(fd[1], arr, sizeof(int) * n) < 0)
        {
            return 3;
        }
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        int arr[10];
        int n;
        if (read(fd[0], &n, sizeof(int)) < 0)
        {
            return 6;
        }
        if (read(fd[0], arr, sizeof(int) * 10) < 0)
        {
            return 4;
        }
        close(fd[0]);
        int sum = 0;
        printf("The received array is: \n");
        for (int i = 0; i < n; i++)
        {
            sum += arr[i];
            printf("%d\n", arr[i]);
        }
        printf("The sum from parent is %d \n", sum);

        wait(NULL);
    }

    return 0;
}