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
} AlarmQueueStruct;

AlarmQueue aq_create() {
    AlarmQueueStruct *aq = (AlarmQueueStruct *) malloc(sizeof(AlarmQueueStruct));
    if (!aq) return NULL;
    aq->alarm_msg = NULL;
    aq->normal_msgs = (void **) malloc(sizeof(void *) * 100);
    aq -> mutex = PTHREAD_MUTEX_INITIALIZER;
    int returnCode = pthread_mutex_init(mutex);
    if (returnCode != 0 || !aq->normal_msgs) {
        free(aq);
        return NULL;
    }
    aq->normal_count = 0;
    aq->max_normal_msgs = 100;

    return aq;
}

int aq_send( AlarmQueue aq, void * msg, MsgKind k){
  return AQ_NOT_IMPL;
}

int aq_recv( AlarmQueue aq, void * * msg) {
  return AQ_NOT_IMPL;
}

int aq_size( AlarmQueue aq) {
  return 0;
}

int aq_alarms( AlarmQueue aq) {
  return 0;
}



