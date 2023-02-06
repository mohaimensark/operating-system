#include <stdlib.h> // Include the standard library header file
#include <stdio.h> 
#include <pthread.h> // Include the POSIX threads header file
#include <unistd.h> // Include the UNIX standard library header file

void* routine() { 
    printf("Hello from threads\n"); 
   

    sleep(3); 
    // Sleep for 3 seconds

    printf("Ending thread\n"); 
}

int main(int argc, char* argv[]) { 
    // Main function of the program, takes in the number of command line arguments (argc) and the array of command line arguments (argv)

    pthread_t p1, p2; 
    // Declare two variables of type pthread_t, which are used to store the IDs of the threads

    if (pthread_create(&p1, NULL, &routine, NULL) != 0) { 
    // Create the first thread using the pthread_create function. The first argument is a pointer to the pthread_t variable (p1), the second argument is a pointer to a pthread_attr_t structure (NULL means use default attributes), the third argument is a pointer to the routine function, and the fourth argument is a pointer to the argument to be passed to the routine function (NULL means no argument). If the function returns a non-zero value, return 1.

        return 1;
    }
    if (pthread_create(&p2, NULL, &routine, NULL) != 0) { 
    // Create the second thread using the pthread_create function. If the function returns a non-zero value, return 2.

        return 2;
    }
    if (pthread_join(p1, NULL) != 0) { 
    // Wait for the first thread to finish using the pthread_join function. If the function returns a non-zero value, return 3.

        return 3;
    }
    if (pthread_join(p2, NULL) != 0) { 
    // Wait for the second thread to finish using the pthread_join function. If the function returns a non-zero value, return 4.

        return 4;
    }
    return 0; 
    // Return 0 if all threads have finished successfully
}



// A thread, also known as a lightweight process, is a single flow of execution within a process. Unlike processes, which are separate and independent entities in a operating system, threads are created within a process and share the same memory space, file descriptors, and other resources.


// Threads are particularly useful for implementing tasks that can run concurrently and independently, such as network I/O, disk I/O, or user interface tasks.

