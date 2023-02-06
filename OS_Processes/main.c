#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

//Every process has a process id. 


// A process in Unix is an instance of a program that is being executed by one or many threads. It has its own separate memory space and system resources. In Unix, processes can be created, managed, and terminated by the operating system or by other processes. The process is a fundamental unit of work in the Unix operating system, and is a key component of its design and architecture.


//Fork returns an integer. Child fork is with id 0.

// "int argc": an integer argument that represents the number of arguments passed to the program, including the name of the program itself.
// "char* argv[]": an array of character pointers, each pointing to a null-terminated string that represents one of the arguments passed to the program.

int main(int argc, char* argv[]){
    fork();
    fork();
    fork();
    printf("Hello worlk\n");

}