#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
// rtt-> round trip time
int main(int argc, char *argv[])
{
    int fd[2]; // File descriptor array to store the file descriptors for the pipe

    // Create a pipe and check for errors
    if(pipe(fd)==-1){
        return 1;
    }

    int id = fork(); // Create the first child process for running the ping command
    if(id<0){
        return 2; // Return error code 2 if fork() fails
    }  

    if(id==0){ // Child process for running ping
        // Redirect the standard output to the write end of the pipe
        dup2(fd[1],STDOUT_FILENO);
        close(fd[0]); // Close the read end of the pipe, as it is not needed in this child process
        close(fd[1]); // Close the write end of the pipe, as it is now connected to standard output
        // Execute the ping command with 5 packets
        execlp("ping","ping","-c","5","google.com",NULL);
    }

    int id2 = fork(); // Create the second child process for running the grep command
    if(id2<0){
        return 3; // Return error code 3 if fork() fails
    }

    if(id2==0){ // Child process for running grep
        // Redirect the standard input to the read end of the pipe
        dup2(fd[0],STDIN_FILENO);
        close(fd[0]); // Close the read end of the pipe, as it is now connected to standard input
        close(fd[1]); // Close the write end of the pipe, as it is not needed in this child process
        // Execute the grep command to search for "rtt"
      
        execlp("grep","grep","rtt",NULL);
    }

    // Close both ends of the pipe in the parent process
    close(fd[0]);
    close(fd[1]);
    
    // Wait for the first child process to finish
    waitpid(id,NULL,0);
    // Wait for the second child process to finish
    waitpid(id2,NULL,0);
    return 0;
}
