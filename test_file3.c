#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "aq.h"
#include "aux.h"

#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 3
#define NUM_MESSAGES 10

static AlarmQueue q;

void *producer_thread(void *arg) {
    for (int i = 0; i < NUM_MESSAGES; i++) {
        if (i % 3 == 0) {
            put_alarm(q, i + 100);
            printf("Sent ALARM message with value %d\n", i + 100);
        } else {
            put_normal(q, i);
            printf("Sent normal message with value %d\n", i);
        }
        msleep(rand() % 100);
    }
    return NULL;
}

void *consumer_thread(void *arg) {
    for (int i = 0; i < NUM_MESSAGES; i++) {
        int result = get(q);
        if (result >= 100) {
            printf("Received ALARM message with value %d\n", result);
        } else if (result >= 0) {
            printf("Received normal message with value %d\n", result);
        } else {
            printf("Error receiving message\n");
            assert(0);
        }
        msleep(rand() % 100);
    }
    return NULL;
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];

    // Create the alarm queue
    q = aq_create();
    if (q == NULL) {
        printf("Failed to create the alarm queue\n");
        return 1;
    }

    // Start multiple producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producers[i], NULL, producer_thread, NULL);
    }

    // Start multiple consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumers[i], NULL, consumer_thread, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    printf("Test complete. No deadlocks found.\n");
    return 0;
}
