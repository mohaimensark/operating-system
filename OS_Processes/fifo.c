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

// FIFO is similar to a regular pipe in that it allows data to be sent from one process to another, but it differs in that it has a persistent name in the file system, allowing processes to communicate with each other even if they don't have a common parent.


// If you open and write fifo for a process, it will hang untill the another process open the fifo for write.
//After opening the fifo file by cat command in terminal , the whole program runed.

int main(int argc, char *argv[])
{
    if (mkfifo("myfifo1", 0777) == -1) // this file can read anyone;
    {
        if (errno != EEXIST)
        {
            printf("Couldn't crate fifo file\n");
            return 1;
        }
    }
    printf("Opening fifo..\n");

    int fd = open("myfifo1", O_WRONLY);
    printf("Opened..\n");
    int x = 97;
    if (write(fd, &x, sizeof(x)) == -1)
    {
        return 2;
    }
    printf("Written..\n");
    close(fd);
    printf("Closed..\n");
    return 0;
}

