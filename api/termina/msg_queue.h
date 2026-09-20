#ifndef TERMINA__MSG_QUEUE_H__
#define TERMINA__MSG_QUEUE_H__

#include <stdint.h>

#include <termina/types.h>
#include <termina/prelude.h>


/**
 * \brief Initializes a message queue.
 *
 * @param[in]   msg_queue  the message queue to initialize. This structure
 *                         contains all the data required to initialize the
 *                         message queue.
 * @param[out]  status     Zero if OK or another value in case of an error.
 */
void termina__msg_queue__init(const termina__id_t msg_queue_id,
                               const size_t message_size,
                               const size_t message_queue_size,
                               int32_t * const status); 

/**
 * \brief Sends a message through a queue.
 *
 * @param[in]   msg_queue  the message queue identifier.
 * @param[in]   element    pointer to the element to be sent.
 * @param[out]  status     Zero if OK or another value in case of an error.
 */
void termina__msg_queue__send(const termina__id_t msg_queue_id, 
                               const void * const element,
                               int32_t * const status);

 
/**
 * \brief Receives a message through a queue.
 *
 * @param[in]   msg_queue  the message queue identifier.
 * @param[in]   element    pointer to the element from which the
 *                         message will be received.
 * @param[out]  status     Zero if OK or another value in case of an error.
 * 
 */
void termina__msg_queue__recv(const termina__id_t msg_queue_id,
                               void * const element,
                               int32_t * const status);

/**
 * \brief Sends a message through an output port.
 *
 * @param[in]  termina__ev      pointer to the event that will be propagated.
 * @param[in]  out_port  pointer to the output port trough which the message
 *                       will be sent.
 * @param[in]  element   pointer to the element to be sent.
 */
void termina__out_port__send(const termina__event_t * const termina__ev,
                              const termina__out_port_t out_port, 
                              const void * const element);


#endif // TERMINA__MSG_QUEUE_H__
