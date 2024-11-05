#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "aq.h"
#include "aux.h"

// Global alarm queue
static AlarmQueue q;

// Producer 1: Sends the first alarm message
void *producer1(void *arg) {
    printf("Producer 1: Attempting to send alarm message 101\n");
    put_alarm(q, 101);
    printf("Producer 1: Successfully sent alarm message 101\n");
    return NULL;
}

// Producer 2: Attempts to send a second alarm message, which should block
void *producer2(void *arg) {
    msleep(500); // Delay to ensure producer1 adds its message first
    printf("Producer 2: Attempting to send alarm message 102 (should block if queue already has an alarm)\n");
    put_alarm(q, 102);  // This should block until the first alarm is consumed
    printf("Producer 2: Successfully sent alarm message 102\n");  // Should print only after consumer removes first alarm
    return NULL;
}

// Consumer: Retrieves messages from the queue
void *consumer(void *arg) {
    msleep(1000); // Delay to allow both producers to attempt to send
    printf("Consumer: Attempting to receive a message\n");

    int result = get(q);  // This should retrieve the first alarm message (101)
    if (result == 101) {
        printf("Consumer: Received alarm message 101\n");
    }

    msleep(1000);  // Delay to allow producer2 to proceed
    printf("Consumer: Attempting to receive the next message\n");

    result = get(q);  // This should retrieve the second alarm message (102)
    if (result == 102) {
        printf("Consumer: Received alarm message 102\n");
    }

    return NULL;
}

int main() {
    // Create the alarm queue
    q = aq_create();
    if (q == NULL) {
        printf("Failed to create the alarm queue\n");
        return 1;
    }

    // Initialize threads
    pthread_t t_producer1, t_producer2, t_consumer;

    // Start threads
    pthread_create(&t_producer1, NULL, producer1, NULL);
    pthread_create(&t_producer2, NULL, producer2, NULL);
    pthread_create(&t_consumer, NULL, consumer, NULL);

    // Wait for threads to complete
    pthread_join(t_producer1, NULL);
    pthread_join(t_producer2, NULL);
    pthread_join(t_consumer, NULL);

    // Clean up
    printf("Test complete.\n");
    return 0;
}
