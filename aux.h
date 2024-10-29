#ifndef AUX_H_INCLUDED
#define AUX_H_INCLUDED


#include "aq.h"


/** 
 * Auxiliary helper functions for debugging the Alarm Queue Library
 *
 * Messages are simply integers which are assumed to be positive. 
 * Errors are assumed to be indicated with negative values.
 * 
 * The put and get functions return the value sent/received if ok.  Otherwise an error code.
 * This may be used e.g. for assertion checks.
 * 
 */

int put_normal(AlarmQueue q, int val);
int put_alarm(AlarmQueue q, int val);
int get(AlarmQueue q);
int print_sizes(AlarmQueue q);

/* Sleep in milliseconds */
void  msleep(int ms);

#endif /* AUX_H_INCLUDED */

