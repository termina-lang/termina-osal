/**
 * @file
 * @ingroup termina__osal__api
 *
 * @brief Interface of the message queues and of the output ports.
 */

#ifndef TERMINA__MSG_QUEUE_H__
#define TERMINA__MSG_QUEUE_H__

#include <stdint.h>

#include <termina/types.h>
#include <termina/prelude.h>


/**
 * @brief Initializes a message queue.
 *
 * @param[in]   msg_queue_id        Identifier of the message queue.
 * @param[in]   message_size        Size of each message in bytes.
 * @param[in]   message_queue_size  Maximum number of messages that the queue
 *                                  holds.
 * @param[out]  status              Status of the operation:
 *                                  `termina__error__none`, or
 *                                  `termina__error__msg_queue_init` if the
 *                                  identifier is out of range or the queue
 *                                  cannot be created.
 */
void termina__msg_queue__init(const termina__id_t msg_queue_id,
                               const size_t message_size,
                               const size_t message_queue_size,
                               termina__error_code_t * const status); 

/**
 * @brief Sends a message through a queue.
 *
 * @param[in]   msg_queue_id  Identifier of the message queue.
 * @param[in]   element       Pointer to the message to send.
 * @param[out]  status        Status of the operation: `termina__error__none`,
 *                            `termina__error__invalid_id`, or the error code
 *                            that the back-end returns.
 */
void termina__msg_queue__send(const termina__id_t msg_queue_id, 
                               const void * const element,
                               termina__error_code_t * const status);

 
/**
 * @brief Receives a message through a queue, blocking until one arrives.
 *
 * @param[in]   msg_queue_id  Identifier of the message queue.
 * @param[out]  element       Pointer to the buffer into which the message is
 *                            received.
 * @param[out]  status        Status of the operation: `termina__error__none`,
 *                            `termina__error__invalid_id`, or the error code
 *                            that the back-end returns.
 */
void termina__msg_queue__recv(const termina__id_t msg_queue_id,
                               void * const element,
                               termina__error_code_t * const status);

/**
 * @brief Receives a message through a queue without blocking.
 *
 * An empty queue is not an error: the function returns with `received` set to
 * false and `status` set to `termina__error__none`.
 *
 * @param[in]   msg_queue_id  Identifier of the message queue.
 * @param[out]  element       Pointer to the buffer into which the message is
 *                            received.
 * @param[out]  received      True if a message was received.
 * @param[out]  status        Status of the operation: `termina__error__none`,
 *                            `termina__error__invalid_id`, or the error code
 *                            that the back-end returns.
 */
void termina__msg_queue__try_recv(const termina__id_t msg_queue_id,
                                   void * const element,
                                   _Bool * const received,
                                   termina__error_code_t * const status);

/**
 * @brief Gets the number of messages pending in a queue.
 *
 * @param[in]   msg_queue_id  Identifier of the message queue.
 * @param[out]  count         Number of messages in the queue.
 * @param[out]  status        Status of the operation: `termina__error__none`,
 *                            `termina__error__invalid_id`, or the error code
 *                            that the back-end returns.
 */
void termina__msg_queue__get_pending(const termina__id_t msg_queue_id,
                                      size_t * const count,
                                      termina__error_code_t * const status);

/**
 * @brief Sends a message through an output port.
 *
 * The function puts the message in the queue of the channel and notifies the
 * receiving task. If either step fails, it raises `EMsgQueueSendError`.
 *
 * @param[in]  termina__ev  Pointer to the event that is being processed.
 * @param[in]  out_port     Output port through which the message is sent.
 * @param[in]  element      Pointer to the message to send.
 */
void termina__out_port__send(const termina__event_t * const termina__ev,
                              const termina__out_port_t out_port, 
                              const void * const element);


#endif // TERMINA__MSG_QUEUE_H__
