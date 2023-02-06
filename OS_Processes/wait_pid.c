#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[])
{

    int id = fork();

    if (id == -1)
    {
        printf("Error creating process\n");
        return 1;
    }
    if (id == 0)
    {
        sleep(4);
        printf("FInished execution %d\n", getpid());
        return 0;
    }

    int id2 = fork();
    if (id2 == -1)
    {
        printf("Error creating process 2\n");
        return 2;
    }
    if (id2 == 0)
    {
        sleep(4);
        printf("FInished execution %d\n", getpid());
        return 0;
    }

    int id_res = waitpid(id,NULL,WNOHANG);
    // if u use -1 insted of id here ,it will work like wait
    printf("waited for %d\n", id_res);
    int id_res2 = waitpid(id2,NULL,WNOHANG);
    printf("waited for %d\n", id_res2);

    return 0;
}