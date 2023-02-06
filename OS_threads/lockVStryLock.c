#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

// Mutex is a data structure that can be locked and unlocked by multiple threads.
pthread_mutex_t mutex;

// Routine that acquires the lock on the mutex and prints "got lock".
void *routine_lock(void *arg)
{
    // Lock the mutex.
    pthread_mutex_lock(&mutex);
    // Print that the lock has been acquired.
    printf("got lock\n");
    // Sleep for 1 second to simulate doing some work.
    sleep(1);
    // Release the lock on the mutex.
    pthread_mutex_unlock(&mutex);
}

// Routine that attempts to acquire the lock on the mutex and prints "got lock" if successful or "Didn't get lock" otherwise.
void *routine_trylock(void *arg)
{
    // Attempt to lock the mutex.
    if (pthread_mutex_trylock(&mutex) == 0)
    {
        // If the lock was acquired successfully, print "got lock".
        printf("got lock\n");
        // Sleep for 1 second to simulate doing some work.
        sleep(1);
        // Release the lock on the mutex.
        pthread_mutex_unlock(&mutex);
    }
    else
    {
        // If the lock was not acquired, print "Didn't get lock".
        printf("Didn't get lock\n");
    }
}

int main(int argc, char *argv[])
{
    // Array of 4 threads.
    pthread_t th[4];
    // Initialize the mutex.
    pthread_mutex_init(&mutex, NULL);
    // Create 4 threads, each of which calls routine_trylock().
    for (int i = 0; i < 4; i++)
    {
        // Create a new thread.
        if (pthread_create(&th[i], NULL, &routine_trylock, NULL) != 0)
        {
            // If there was an error creating the thread, print an error message.
            perror("Error at creating thread");
        }
    }
    // Wait for all 4 threads to finish.
    for (int i = 0; i < 4; i++)
    {
        // Wait for a thread to finish.
        if (pthread_join(th[i], NULL) != 0)
        {
            // If there was an error waiting for the thread to finish, print an error message.
            perror("Error at joining thread");
        }
    }
    // Destroy the mutex.
    pthread_mutex_destroy(&mutex);
    return 0;
}
