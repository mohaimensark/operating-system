#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void handle_sigtstp(int sig)
{
    printf("Stop not allowed\n");
}

void handle_sigcont(int sig){
    printf("Input number: ");
    fflush(stdout);
}

int main(int argc, char *argv[])
{
    // Create a sigaction struct to handle the SIGTSTP signal
    struct sigaction sa;
    sa.sa_handler = &handle_sigcont; // Set the handler function to handle_sigtstp
    sa.sa_flags = SA_RESTART;        // Set the flag to restart any system calls that were interrupted by this signal

    // Register the sigaction struct with the SIGTSTP signal
    sigaction(SIGTSTP, &sa, NULL);

     /*It will do the same task as the above task
    signal(SIGTSTP, &handle_sigtstp);*/

    int x;
    scanf("%d", &x);
    return 0;
}