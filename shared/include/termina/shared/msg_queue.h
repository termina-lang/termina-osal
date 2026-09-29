#ifndef TERMINA__SHARED__MSG_QUEUE_H__
#define TERMINA__SHARED__MSG_QUEUE_H__


#include "config.h"

#include <termina.h>

#include <stdbool.h>


/**
 * \brief Type of message queues.
 */
typedef struct {

    // \brief Identifier of this message queue
    termina__id_t msg_queue_id;

    // \brief Size of the messages
    size_t message_size;

    //! Size of the message queue
    size_t message_queue_size;

} termina__shared__msg_queue_t;


#ifndef TERMINA__APP_CONFIG__MESSAGE_QUEUES
#error "config.h must define TERMINA__APP_CONFIG__MESSAGE_QUEUES"
#else
#if (TERMINA__APP_CONFIG__MESSAGE_QUEUES > 0)

/**
 * \brief Size of the message queue object tables.
 */
#define TERMINA__SHARED__MSG_QUEUE_TABLE_SIZE TERMINA__APP_CONFIG__MESSAGE_QUEUES

/**
 * \brief Checks whether a message queue identifier is valid.
 *
 * @param[in] msg_queue_id the message queue identifier.
 *
 * @return true if the identifier is less than the number of message queues
 *         defined in the application, false otherwise.
 */
static inline bool termina__shared__msg_queue__is_valid_id(const termina__id_t msg_queue_id) {
    return (msg_queue_id < TERMINA__APP_CONFIG__MESSAGE_QUEUES);
}

#else

// The application defines no message queues. ISO C does not allow arrays of
// size zero, so the tables keep one unused element, and no identifier is valid.
#define TERMINA__SHARED__MSG_QUEUE_TABLE_SIZE 1U

static inline bool termina__shared__msg_queue__is_valid_id(const termina__id_t msg_queue_id) {
    (void)msg_queue_id;
    return false;
}

#endif
#endif

extern termina__shared__msg_queue_t termina__shared__msg_queue_object_table[TERMINA__SHARED__MSG_QUEUE_TABLE_SIZE];

static inline termina__shared__msg_queue_t * termina__shared__msg_queue__get_queue(const termina__id_t msg_queue_id) {
    return &termina__shared__msg_queue_object_table[msg_queue_id];
}

/**
 * \brief Initializes a task list
 * 
 * This function shall be implemented for each operating system. The data stored
 * in the shared object table is accessible by the implementation, so there is 
 * no need to pass it again as a parameter.
 * 
 * The identifier of the message queue has been validated by the upper layer.
 * 
 * @param[in]  msg_queue_id   the identifier of the message queue to initialize.
 * @param[out] status         Zero if OK or another value in case of an error.
 */
void termina__os__msg_queue__init(const termina__id_t msg_queue_id,
                                  termina__error_code_t * const status);

/**
 * \brief Sends a message through a queue.
 * 
 * @param[in]   msg_queue  the message queue identifier.
 * @param[in]   data       pointer to the data to be sent.
 * @param[out]  status     Zero if OK or another value in case of an error.
 */
void termina__os__msg_queue__send(const termina__id_t msg_queue_id,
                                  const void * const data,
                                  termina__error_code_t * const status);

/**
 * \brief Receives a message through a queue.
 *
 * @param[in]   msg_queue  the message queue identifier.
 * @param[in]   element    pointer to the element from which the
 *                         message will be received.
 * @param[out]  status     Zero if OK or another value in case of an error.
 */
void termina__os__msg_queue__recv(const termina__id_t msg_queue_id,
                                  void * const element,
                                  termina__error_code_t * const status);


/**
 * \brief Delivers a message to a port of a task.
 *
 * The message goes to the queue of the port and the event that tells the task
 * about it to the queue of the task. A send that fails raises the exception
 * EMsgQueueSendError, since a message lost there, or one left in the queue of
 * the port with no event, puts the task out of step with its ports.
 *
 * @param[in] port_msg_queue_id  identifier of the queue of the port.
 * @param[in] message            pointer to the message.
 * @param[in] task_msg_queue_id  identifier of the queue of the task.
 * @param[in] event              pointer to the event.
 */
void termina__shared__msg_queue__deliver(const termina__id_t port_msg_queue_id,
                                         const void * const message,
                                         const termina__id_t task_msg_queue_id,
                                         const termina__event_t * const event);

#endif // TERMINA__SHARED__MSG_QUEUE_H__
