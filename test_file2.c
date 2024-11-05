#include <stdio.h>
#include <pthread.h>
#include "aq.h"
#include "aux.h"

static AlarmQueue q;

void *producer_with_delay(void *arg) {
    msleep(200);
    put_normal(q, 1);
    msleep(100);
    put_alarm(q, 99);
    msleep(200);
    put_normal(q, 2);
    return NULL;
}

void *consumer_with_delay(void *arg) {
    msleep(300);
    get(q);
    msleep(100);
    get(q);
    get(q);
    return NULL;
}

int main() {
    q = aq_create();
    pthread_t producer, consumer;
    pthread_create(&producer, NULL, producer_with_delay, NULL);
    pthread_create(&consumer, NULL, consumer_with_delay, NULL);
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);
    return 0;
}