#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/* mails is a shared global variable between all threads */
int mails = 0;

/* mutex is used to provide synchronization for access to the shared mails variable */
pthread_mutex_t mutex;

/* routine is the function executed by each thread */
void* routine() {
    /* Increase mails by 1, 10000000 times */
    for (int i = 0; i < 10000000; i++) {
        /* Lock the mutex before accessing the shared mails variable */
        pthread_mutex_lock(&mutex);
        mails++;
        /* Unlock the mutex after accessing the shared mails variable */
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char* argv[]) {
    /* An array of 8 threads */
    pthread_t th[8];
    int i;

    /* Initialize the mutex */
    pthread_mutex_init(&mutex, NULL);

    /* Create 8 threads and start executing the routine function */
    for (i = 0; i < 8; i++) {
        if (pthread_create(th + i, NULL, &routine, NULL) != 0) {
            perror("Failed to create thread");
            return 1;
        }
        printf("Thread %d has started\n", i);
    }

    /* Wait for all 8 threads to finish executing */
    for (i = 0; i < 8; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            return 2;
        }
        printf("Thread %d has finished execution\n", i);
    }

    /* Destroy the mutex */
    pthread_mutex_destroy(&mutex);

    /* Print the final number of mails */
    printf("Number of mails: %d\n", mails);
    return 0;
}
