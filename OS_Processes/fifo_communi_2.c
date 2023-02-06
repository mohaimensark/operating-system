#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// For fifo
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#include <time.h>

int main(int argc, char *argv[])
{

    int arr[5];

    int fd = open("sum", O_RDONLY);
    if (fd == -1)
    {
        return 1;
    }

    if (read(fd, arr, sizeof(int) * 5) == -1)
    {
        return 2;
    }

    close(fd);
    int sum = 0;
    for (int i = 0; i < 5; i++)
    {

        sum += arr[i];
    }

    printf("Sum is %d\n", sum);

    return 0;
}
