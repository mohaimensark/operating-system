#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

// there are a shared buffer  or memory,we can compare it with
// producer(browser) and consumer(server)

// we have to solve:
// 1)Manage shared memory access
// 2)Checking for if buffer is full.
// 3)Checking for if the buffer is empty.

#define THREAD_NUM 8

sem_t semEmpty;
sem_t semFull;

pthread_mutex_t mutexBuffer;

int buffer[10];
int count = 0;

void *producer(void *args)
{
    while (1)
    {
        // Produce
        int x = rand() % 100;
        sleep(1);

        // Add to the buffer
        sem_wait(&semEmpty);
        pthread_mutex_lock(&mutexBuffer);
        buffer[count] = x;
        count++;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semFull);
    }
}

void *consumer(void *args)
{
    while (1)
    {
        int y;

        // Remove from the buffer
        sem_wait(&semFull);
        pthread_mutex_lock(&mutexBuffer);
        y = buffer[count - 1];
        count--;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semEmpty);

        // Consume
        printf("Got %d\n", y);
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexBuffer, NULL);
    sem_init(&semEmpty, 0, 5);
    sem_init(&semFull, 0, 0);
    int i;
    for (i = 0; i < THREAD_NUM; i++)
    {
        if (i > 3)
        {
            if (pthread_create(&th[i], NULL, &producer, NULL) != 0)
            {
                perror("Failed to create thread");
            }
        }
        else
        {
            if (pthread_create(&th[i], NULL, &consumer, NULL) != 0)
            {
                perror("Failed to create thread");
            }
        }
    }
    for (i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to join thread");
        }
    }
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    pthread_mutex_destroy(&mutexBuffer);
    return 0;
}

// The producer process generates data and stores it in the buffer, and the consumer process takes the data from the buffer and uses it. The goal is to ensure that the producer and consumer processes are synchronized, so that the consumer does not attempt to take data from an empty buffer and the producer does not attempt to add data to a full buffer.

// There are several synchronization mechanisms available to solve the producer-consumer problem, such as semaphores, monitors, and mutexes. The choice of synchronization mechanism depends on the specific requirements of the system, such as the number of producers and consumers, the size of the buffer, and the desired behavior of the system in case of overflow or underflow.

// In the case of semaphores, the producer increments a semaphore when it stores data in the buffer and the consumer decrements the semaphore when it takes data from the buffer. The semaphore acts as a counter, keeping track of the number of elements in the buffer.