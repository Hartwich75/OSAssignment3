
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "aux.h"


typedef struct {
  int value;
} Msg;


int put_normal(AlarmQueue q, int val) {
  Msg * m = malloc(sizeof(Msg));
  m->value = val;
  int ret = aq_send(q, m, AQ_NORMAL);
  if (ret < 0) {
    printf("ERRROR: put_normal %d got %d\n", val, ret);
    return ret;
  }
   
 printf("Sent normal message with value %d\n", val);
 return val;
}

int put_alarm(AlarmQueue q, int val) {
  Msg * m = malloc(sizeof(Msg));
  m->value = val;
  int ret = aq_send(q, m, AQ_ALARM);
  if (ret < 0) {
    printf("WARNING: put_alarm %d got %d\n", val, ret);
    return ret;
  }
  
  printf("Sent ALARM  message with value %d\n", val);
 return val;

}

int get(AlarmQueue q) {
  Msg * m = malloc(sizeof(Msg));
  int ret = aq_recv(q, (void**) &m);
  if       (ret < 0) {
    printf("WARNING: get got %d\n", ret);
    return ret;
  }
  
  if ( m == NULL) {
    printf("ERROR: get got null message of kind %d\n", ret);
    return AQ_NULL_MSG;
  }

  printf("Received %s message with value %d\n", (ret ? "ALARM " : "normal"), m->value);
  ret = m->value;  
  free(m);
  return ret;
}

int print_sizes(AlarmQueue q) {
  int size = aq_size(q);
  int alarms = aq_alarms(q);
  printf("Current size = %d, alarms = %d\n", size, alarms);
  return size;  
}


/* Sleep in milliseconds */
void  msleep(int ms) {
    struct timespec dur;
    dur.tv_sec = ms/1000;
    dur.tv_nsec = (ms % 1000)*1000*1000;
    nanosleep(&dur, NULL);
}

