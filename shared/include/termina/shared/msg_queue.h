/**
 * @file
 * @ingroup termina__osal__shared
 *
 * @brief Table of the message queues and the queue operations that each
 *        operating system implements.
 */

#ifndef TERMINA__SHARED__MSG_QUEUE_H__
#define TERMINA__SHARED__MSG_QUEUE_H__


#include "config.h"

#include <termina.h>

#include <stdbool.h>


/**
 * @brief Type of message queues.
 */
typedef struct {

    //! Identifier of the message queue.
    termina__id_t msg_queue_id;

    //! Size of the messages in bytes.
    size_t message_size;

    //! Maximum number of messages that the queue holds.
    size_t message_queue_size;

} termina__shared__msg_queue_t;


#ifndef TERMINA__APP_CONFIG__MESSAGE_QUEUES
#error "config.h must define TERMINA__APP_CONFIG__MESSAGE_QUEUES"
#else
#if (TERMINA__APP_CONFIG__MESSAGE_QUEUES > 0)

/**
 * @brief Size of the message queue object tables.
 */
#define TERMINA__SHARED__MSG_QUEUE_TABLE_SIZE TERMINA__APP_CONFIG__MESSAGE_QUEUES

/**
 * @brief Checks whether a message queue identifier is valid.
 *
 * @param[in] msg_queue_id  Identifier of the message queue.
 *
 * @return True if the identifier is less than the number of message queues
 *         of the application, false otherwise.
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

/** @brief Table of the message queues, indexed by identifier. */
extern termina__shared__msg_queue_t termina__shared__msg_queue_object_table[TERMINA__SHARED__MSG_QUEUE_TABLE_SIZE];

/**
 * @brief Gets the message queue object of an identifier, which must be valid.
 *
 * @param[in] msg_queue_id  Identifier of the message queue.
 *
 * @return Pointer to the message queue object.
 */
static inline termina__shared__msg_queue_t * termina__shared__msg_queue__get_queue(const termina__id_t msg_queue_id) {
    return &termina__shared__msg_queue_object_table[msg_queue_id];
}

/**
 * @brief Creates a message queue in the operating system.
 * 
 * Each operating system implements this function. The implementation reads
 * the size of the messages and of the queue from the object table, and the
 * caller has already validated the identifier.
 * 
 * @param[in]  queue_id  Identifier of the message queue.
 * @param[out] status    Status of the operation: `termina__error__none`, or
 *                       the error code of the back-end.
 */
void termina__os__msg_queue__init(const termina__id_t queue_id,
                                  termina__error_code_t * const status);

/**
 * @brief Sends a message through a queue.
 *
 * @param[in]   queue_id  Identifier of the message queue.
 * @param[in]   data      Pointer to the message to send.
 * @param[out]  status    Status of the operation: `termina__error__none`, or
 *                        the error code of the back-end.
 */
void termina__os__msg_queue__send(const termina__id_t queue_id,
                                  const void * const data,
                                  termina__error_code_t * const status);

/**
 * @brief Receives a message through a queue, blocking until one arrives.
 *
 * @param[in]   queue_id  Identifier of the message queue.
 * @param[out]  data      Pointer to the buffer into which the message is
 *                        received.
 * @param[out]  status    Status of the operation: `termina__error__none`, or
 *                        the error code of the back-end.
 */
void termina__os__msg_queue__recv(const termina__id_t queue_id,
                                  void * const data,
                                  termina__error_code_t * const status);

/**
 * @brief Receives a message through a queue without blocking.
 *
 * @param[in]   queue_id  Identifier of the message queue.
 * @param[out]  data      Pointer to the buffer into which the message is
 *                        received.
 * @param[out]  received  True if a message was received.
 * @param[out]  status    Status of the operation: `termina__error__none`, or
 *                        the error code of the back-end.
 */
void termina__os__msg_queue__try_recv(const termina__id_t queue_id,
                                      void * const data,
                                      _Bool * const received,
                                      termina__error_code_t * const status);

/**
 * @brief Gets the number of messages pending in a queue.
 *
 * @param[in]   queue_id  Identifier of the message queue.
 * @param[out]  count     Number of messages in the queue.
 * @param[out]  status    Status of the operation: `termina__error__none`, or
 *                        the error code of the back-end.
 */
void termina__os__msg_queue__get_pending(const termina__id_t queue_id,
                                         size_t * const count,
                                         termina__error_code_t * const status);

/**
 * @brief Removes every message of a queue.
 *
 * @param[in]   queue_id  Identifier of the message queue.
 * @param[out]  status    Status of the operation: `termina__error__none`, or
 *                        the error code of the back-end.
 */
void termina__os__msg_queue__flush(const termina__id_t queue_id,
                                   termina__error_code_t * const status);

/**
 * @brief Removes every message of a queue, after checking its identifier.
 *
 * @param[in]   msg_queue_id  Identifier of the message queue.
 * @param[out]  status        Status of the operation: `termina__error__none`,
 *                            `termina__error__invalid_id`, or the error code
 *                            of the back-end.
 */
void termina__shared__msg_queue__flush(const termina__id_t msg_queue_id,
                                       termina__error_code_t * const status);


/**
 * @brief Delivers a message to a port of a task.
 *
 * The message goes to the queue of the port, and the event that notifies the
 * task goes to the queue of the task. A null message, or a send that fails,
 * raises `EMsgQueueSendError`.
 *
 * @param[in] port_msg_queue_id  Identifier of the queue of the port.
 * @param[in] message            Pointer to the message.
 * @param[in] task_msg_queue_id  Identifier of the queue of the task.
 * @param[in] event              Pointer to the event.
 * @param[in] address            Address of the call to the runtime that sent
 *                               the message, or 0 when the runtime sends it on
 *                               its own.
 */
void termina__shared__msg_queue__deliver(const termina__id_t port_msg_queue_id,
                                         const void * const message,
                                         const termina__id_t task_msg_queue_id,
                                         const termina__event_t * const event,
                                         const size_t address);

#endif // TERMINA__SHARED__MSG_QUEUE_H__
