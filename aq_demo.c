
#include <stdlib.h>
#include <stdio.h>

#include <assert.h>

#include "aq.h"

#include "aux.h"

/** 
 * Sequential program that sends and receives a few integer messages 
 * in order to demonstrate the use of the sequential Alarm Queue Library
 *
 * May also be used as a first simple test
 * 
 * Elaborate on your own
 */

int main(int argc, char ** argv) {

  AlarmQueue q = aq_create();
  if (q == NULL) {
    printf("Alarm queue could not be created\n");
    exit(1);
  }

  put_normal(q, 1);
  put_normal(q, 2);
  put_alarm (q, 3);
  assert( put_alarm (q, 4) == AQ_NO_ROOM );
  put_normal(q, 5);

  /* Now there should be 4 messages in the queue */
  assert(print_sizes(q) == 4);

  /* First received should be the alarm message */
  assert( get(q) == 3 );

  put_alarm (q, 6);
  put_normal(q, 7);
  assert( put_alarm (q, 8) == AQ_NO_ROOM );
  put_normal(q, 9);

  assert( print_sizes(q) == 6 );

  assert( get(q) == 6 );
  assert( get(q) == 1 );
  assert( get(q) == 2 );
  assert( get(q) == 5 );
  assert( get(q) == 7 );
  assert( get(q) == 9 );

  /* Now the queue should be empty */
  assert( print_sizes(q) == 0 );

  /* Next get should give error */
  assert( get(q) == AQ_NO_MSG );

  return 0;
}
