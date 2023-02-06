#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include<errno.h>

int main(int argc, char *argv[],char *envp[])
{
    //_execl("filepath");  // This file is also take all the memory of current process.

    char* arr[] = {
        "ping",
        "google.com",
        NULL
    };
    char* env[] = {
        "TEST=environment variable",
        NULL
    };

  _execlvp("ping","ping","google.com",NULL,env);


    // int id = fork();
  
    // printf("Process ID: %d\n", getpid());
    // printf("Parent process ID: %d\n", getppid());
    
    return 0;
}


// _execlp, _execvp, and _execl are three variants of the exec family of functions in Unix-like operating systems, used to replace the current process image with a new process image.

// _execlp: The _execlp function takes the name of the file to be executed and a variable number of arguments passed to the new process as separate arguments to the function. For example:

// execlp("ls", "ls", "-l", NULL);


// _execvp: The _execvp function takes the name of the file to be executed and a list of arguments passed to the new process in the form of an array of strings. For example:

// char *args[] = {"ls", "-l", NULL};
// execvp("ls", args);


// _execl: The _execl function is similar to _execlp, but it requires the path to the file to be executed to be specified. For example:

// execl("/bin/ls", "ls", "-l", NULL);


// Note: The "p" in _execlp and _execvp stands for "search the PATH", which means that these functions will search through the directories specified in the PATH environment variable to find the executable file. The "l" in _execl stands for "list", as the arguments are passed as a list of separate arguments to the function.