#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>

// signal will send notification
int main(int argc, char *argv[])
{

    int id = fork();
    if (id == -1)
    {
        return 1;
    }

    if (id == 0)
    {
        while (1)
        {
            printf("some text are here\n");
            usleep(50000);
        }
    }
    else
    {
        kill(id, SIGSTOP); // it will stop the child process
        // without any delay.

        int t;
        do
        {
            printf("Time id seconds for execution: ");
            scanf("%d", &t);
            if (t > 0)
            {
                kill(id, SIGCONT); // it will contiune again
                sleep(t);
                kill(id, SIGSTOP);
            }
        } while (t > 0);

        kill(id, SIGKILL);
        wait(NULL);
    }

    return 0;
}