#include <stdlib.h>

struct Message {
    struct Message *next;
    int isAlarm;
};

struct AlarmQueue {
    struct Message *alarm;
    struct Message *head;
    struct Message *tail;
};

struct AlarmQueue * aq_create() {
    struct AlarmQueue *aq = malloc(sizeof(struct AlarmQueue));
    if (aq == NULL) {
        return NULL;
    }
    /* maybe we want to define these?
    aq->alarm = NULL;
    aq->head = NULL;
    aq->tail = NULL;
     */
    return aq;
}
void qMsg(struct AlarmQueue* aq, struct Message* msg)
{
    // if the queue is empty
    if(aq->head == NULL)
    {
        aq->head = msg;
        aq->tail = msg;
    }
    //add the message to the end of the queue
    else
    {
        aq->tail->next = msg;
        aq->tail = msg;
    }
}