#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

// Mutex to protect access to the shared 'fuel' variable
pthread_mutex_t mutexFuel;
// Condition variable to signal the presence of fuel
pthread_cond_t condFuel;
// The shared fuel level
int fuel = 0;

// Routine for the thread responsible for filling the fuel
void *fuel_filling(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        // Lock the mutex before accessing the shared 'fuel' variable
        pthread_mutex_lock(&mutexFuel);
        fuel += 15;
        printf("Filled fuel... %d\n", fuel);
        // Release the mutex after accessing the shared 'fuel' variable
        pthread_mutex_unlock(&mutexFuel);
        // Signal the condition variable to notify the presence of fuel
        pthread_cond_signal(&condFuel);
        sleep(1);
    }
}

// Routine for the thread representing a car
void *car(void *arg)
{
    // Lock the mutex before accessing the shared 'fuel' variable
    pthread_mutex_lock(&mutexFuel);
    while (fuel < 40)
    {
        printf("No fuel. Waiting...\n");
        // Wait for the condition variable to be signaled
        pthread_cond_wait(&condFuel, &mutexFuel);
        // Equivalent to:
        // pthread_mutex_unlock(&mutexFuel);
        // wait for signal on condFuel
        // pthread_mutex_lock(&mutexFuel);
    }
    fuel -= 40;
    printf("Got fuel. Now left: %d\n", fuel);
    // Release the mutex after accessing the shared 'fuel' variable
    pthread_mutex_unlock(&mutexFuel);
}

int main(int argc, char *argv[])
{
    pthread_t th[2];
    // Initialize the mutex
    pthread_mutex_init(&mutexFuel, NULL);
    // Initialize the condition variable
    pthread_cond_init(&condFuel, NULL);
    for (int i = 0; i < 2; i++)
    {
        // Create a thread for fuel filling if i = 1
        if (i == 1)
        {
            if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0)
            {
                perror("Failed to create thread");
            }
        }
        else
        {
            // Create a thread for car otherwise
            if (pthread_create(&th[i], NULL, &car, NULL) != 0)
            {
                perror("Failed to create thread");
            }
        }
    }

    for (int i = 0; i < 2; i++)
    {
        // Wait for the threads to finish
        if (pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to join thread");
        }
    }
    // Destroy the mutex
    pthread_mutex_destroy(&mutexFuel);
    // Destroy the condition
    pthread_cond_destroy(&condFuel);
    return 0;
}