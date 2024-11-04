/**
 * @file   aq.c
 * @Author 02335 team
 * @date   October, 2024
 * @brief  Alarm queue skeleton implementation
 */

#include "aq.h"
#include <pthread.h>
#include <stdlib.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int shared_data = 0;

typedef struct {
    void *alarm_msg;
    void **normal_msgs;
    int normal_count;
    int max_normal_msgs;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} AlarmQueueStruct;

AlarmQueue aq_create() {
    AlarmQueueStruct *aq = (AlarmQueueStruct *) malloc(sizeof(AlarmQueueStruct));
    if (!aq) return NULL;

    aq->alarm_msg = NULL;
    aq->normal_msgs = (void **) malloc(sizeof(void *) * 100);
    aq->normal_count = 0;
    aq->max_normal_msgs = 100;

    if (pthread_mutex_init(&aq->mutex, NULL) != 0 || pthread_cond_init(&aq->cond, NULL) != 0 || !aq->normal_msgs) {
        //if mutex init or malloc fails, free the allocated memory and return NULL
        free(aq);
        return NULL;
    }
    aq->normal_count = 0;
    aq->max_normal_msgs = 100;
    return aq;
}


#include <pthread.h>

int aq_send(AlarmQueue aq, void *msg, MsgKind k) {
    AlarmQueueStruct *queue = (AlarmQueueStruct *)aq;
    int result = -1; // Assume failure

    pthread_mutex_lock(&queue->mutex); // Lock the mutex or halt until it is unlocked

    // Block if necessary until there is room in the queue
    while ((k == AQ_ALARM && queue->alarm_msg != NULL) ||
           (k == AQ_NORMAL && queue->normal_count >= queue->max_normal_msgs)) {
        pthread_cond_wait(&queue->cond, &queue->mutex); //wait for signal and temporarily unlock the mutex
    }
    // Place the message in the queue. If there is no room, something went wrong
    if (k == AQ_ALARM && queue->alarm_msg == NULL) {
        queue->alarm_msg = msg;
        result = 0;
    } else if (k == AQ_NORMAL && queue->normal_count < queue->max_normal_msgs) {
        queue->normal_msgs[queue->normal_count++] = msg;
        result = 0;
    }
    // Notify other threads that may be waiting for space
    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->mutex);
    return result;
}

int aq_recv(AlarmQueue aq, void * * pmsg) {
    AlarmQueueStruct *queue = (AlarmQueueStruct *)aq;
    int result = -1; // Assume failure

    pthread_mutex_lock(&queue->mutex);

    while (queue->alarm_msg == NULL && queue->normal_count == 0) {
        pthread_cond_wait(&queue->cond, &queue->mutex); //wait for signal and temporarily unlock the mutex
    }

    if (queue -> alarm_msg != NULL){
        *pmsg = queue -> alarm_msg;
        queue -> alarm_msg = NULL;
        result = AQ_ALARM;
        //return AQ_ALARM;
    } else if (queue -> normal_count > 0){
        //Dequeue the first message
        *pmsg = queue -> normal_msgs[0];

        for (int i = 1; i < queue -> normal_count; ++i){
            //shift the messages forward
            queue -> normal_msgs[i - 1] = queue -> normal_msgs[i];
        }
        queue -> normal_count--;
        result = AQ_NORMAL; //success
        //return AQ_NORMAL;
    }
    pthread_cond_signal(&queue -> cond);
    pthread_mutex_unlock(&queue->mutex);
    return result;
}


int aq_size( AlarmQueue aq) {
    AlarmQueueStruct *queue = (AlarmQueueStruct *)aq;
    pthread_mutex_lock(&queue -> mutex);
    int size = queue -> normal_count + (queue -> alarm_msg ? 1 : 0);
    pthread_mutex_unlock(&queue -> mutex);

  return size;
}

int aq_alarms( AlarmQueue aq) {
    AlarmQueueStruct  *queue = (AlarmQueueStruct *)aq;
    pthread_mutex_lock(&queue -> mutex);
    int alarms = queue -> alarm_msg ? 1 : 0;
    pthread_mutex_unlock(&queue -> mutex);

  return alarms;
}



