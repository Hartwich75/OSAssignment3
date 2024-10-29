/**
 * @file   aq.h
 * @Author 02335 team
 * @date   October, 2024
 * @brief  Alarm queue header file.
 */

#ifndef LIBAQ_H_INCLUDED
#define LIBAQ_H_INCLUDED

#include <stddef.h>

/**
 * @brief Messages are transferred as pointers to blocks allocated by malloc
 */

typedef char MsgKind;

#define AQ_ALARM        1   // Message is of kind alarm
#define AQ_NORMAL       0   // Message if of kind normal

/* Error codes */
#define AQ_UNINIT      -1   // Queue has not been initialized
#define AQ_NULL_MSG    -2   // Sent message is NULL
#define AQ_NO_MSG      -3   // No messages
#define AQ_NO_ROOM     -4   // No room for message
#define AQ_NOT_IMPL  -100   // Operation is not implemented

typedef void * AlarmQueue;  // Opaque type 

/**
 * @name    aq_create
 * @brief   Creates and initializes an alarm queue
 * @retval  Handle to alarm queue if created, otherwise NULL
 */
AlarmQueue aq_create( );

/**
 * @name    aq_send
 * @brief   Sends message pointed to by msg with kind indicated.
 * @retval  0 if message was successfully sent, otherwise an error code.
 */
int aq_send( AlarmQueue aq, void * msg, MsgKind k);

/**
 * @name    aq_recv
 * @brief   Receives a message setting the supplied msg pointer. Blocks until message is ready.
 * @retval  Kind of message if message was received successfully, otherwise an error code.
 */
int aq_recv( AlarmQueue aq, void * * msg);

/**
 * @name    aq_size
 * @brief   Give size of alarm queue in terms of messages
 * @retval  Number of messages (of both kinds) currently held by the queue
 */
int aq_size( AlarmQueue aq);

/**
 * @name    aq_alarms
 * @brief   Give size of alarm messages
 * @retval  Number of alarm messages currently held by the queue
 */
int aq_alarms( AlarmQueue aq);


#endif /* LIBAQ_H_INCLUDED */

