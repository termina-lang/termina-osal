#ifndef __TERMINA__MSG_QUEUE_H__
#define __TERMINA__MSG_QUEUE_H__

#include <stdint.h>

#include <termina/types.h>
#include <termina/prelude.h>


/**
 * \brief Initializes a message queue.
 *
 * @param[in]   msg_queue  the message queue to initialize. This structure
 *                         contains all the data required to initialize the
 *                         message queue.
 * @param[out]  status     Success if OK or an error otherwise.
 */
void __termina_msg_queue__init(const __termina_id_t msg_queue_id,
                               size_t message_size,
                               size_t message_queue_size,
                               Status * const status); 

/**
 * \brief Sends a message through a queue.
 *
 * @param[in]   msg_queue  the message queue identifier.
 * @param[in]   element    pointer to the element to be sent.
 * @param[out]  status     Success if OK or an error otherwise.
 */
void __termina_msg_queue__send(const __termina_id_t msg_queue_id, 
                               const void * const element,
                               Status * const status);

 
/**
 * \brief Receives a message through a queue.
 *
 * @param[in]   msg_queue  the message queue identifier.
 * @param[in]   element    pointer to the element from which the
 *                         message will be received.
 * @param[out]  status     Success if OK or an error otherwise.
 * 
 */
void __termina_msg_queue__recv(const __termina_id_t msg_queue_id,
                               void * const element,
                               Status * const status);


#endif // __TERMINA__MSG_QUEUE_H___
