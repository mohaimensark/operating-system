#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int x = 0;

void handle_sigusr1(int sig)
{
    if (x == 0)
    {
        printf("Remember multiplication is repetitive addition\n");
    }
}

int main(int argc, char *argv[])
{

    int id = fork();
    if (id == -1)
    {
        return 1;
    }

    if (id == 0)
    {
        sleep(5);
        kill(getppid(), SIGUSR1);
    }
    else
    {
        struct sigaction sa = {0};
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handle_sigusr1;
        sigaction(SIGUSR1, &sa, NULL);

        
        printf("What is the result of 3 x 5: ");
        scanf("%d", &x);
        if (x == 15)
        {
            printf("Right!\n");
        }
        else
        {
            printf("Wrong!\n");
        }
        wait(NULL);
    }

    return 0;
}


// The struct sigaction contains the following elements:

// sa_handler: A pointer to the signal-handling function.

// sa_flags: A set of flags that modify the behavior of the signal-handling process.

// sa_mask: A set of signals that are blocked while the signal-handling function is executing.

// sa_restorer: (deprecated) A pointer to a function that restores the previous signal-handling behavior. This element is not used in modern systems.