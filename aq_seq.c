/**
 * @file   aq.c
 * @Author 02335 team
 * @date   October, 2024
 * @brief  Alarm queue skeleton implementation
 */

#include "aq.h"
#include <stdlib.h>

typedef struct {
    void *alarm_msg;
    void **normal_msgs;
    int normal_count;
    int max_normal_msgs;
} AlarmQueueStruct;

AlarmQueue aq_create( ) {
    AlarmQueueStruct *aq = (AlarmQueueStruct *) malloc(sizeof (AlarmQueueStruct));

    if (!aq) return NULL;

    aq -> alarm_msg = NULL;
    aq -> normal_msgs = (void **) malloc(sizeof (void *) * 100);
    aq -> normal_count = 0;
    aq -> max_normal_msgs = 100;

    return (AlarmQueue)aq;
}

int aq_send(AlarmQueue aq, void * msg, MsgKind k){
    AlarmQueueStruct *queue = (AlarmQueueStruct *)aq;

    if (k == AQ_ALARM) {
        if(queue -> alarm_msg != NULL){
            return AQ_NO_ROOM;
        }
        queue -> alarm_msg = msg;

        return 0;

    } else if (k == AQ_NORMAL){
        if (queue -> normal_count >= queue -> max_normal_msgs){
            return AQ_NO_ROOM;
        }
        queue -> normal_msgs[queue -> normal_count++] = msg;

        return 0;
    }

    return -1;
}

int aq_recv( AlarmQueue aq, void * * pmsg) {
    AlarmQueueStruct *queue = (AlarmQueueStruct *)aq;

    if (queue -> alarm_msg != NULL){
        *pmsg = queue -> alarm_msg;
        queue -> alarm_msg = NULL;

        return AQ_ALARM;
    } else if (queue -> normal_count > 0){
        *pmsg = queue -> normal_msgs[0];

        for (int i = 1; i < queue -> normal_count; ++i){
            queue -> normal_msgs[i - 1] = queue -> normal_msgs[i];
        }
        queue -> normal_count--;
        return AQ_NORMAL;
    }

    return AQ_NO_MSG;
}

int aq_size( AlarmQueue aq) {
    AlarmQueueStruct *queue = (AlarmQueueStruct *)aq;
    return queue -> normal_count + (queue -> alarm_msg ? 1 : 0);
}

int aq_alarms( AlarmQueue aq) {
    AlarmQueueStruct *queue = (AlarmQueueStruct *)aq;
    return queue -> alarm_msg ? 1 : 0;
}



