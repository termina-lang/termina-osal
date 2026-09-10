#ifndef __TERMINA__SHARED__MSG_QUEUE_H__
#define __TERMINA__SHARED__MSG_QUEUE_H__


#include "config.h"

#include <termina.h>

#include <stdbool.h>


/**
 * \brief Type of message queues.
 */
typedef struct {

    // \brief Identifier of this message queue
    __termina_id_t msg_queue_id;

    // \brief Size of the messages
    size_t message_size;

    //! Size of the message queue
    size_t message_queue_size;

} __termina_shared_msg_queue_t;


#ifndef __TERMINA_APP_CONFIG_MESSAGE_QUEUES
#error "config.h must define __TERMINA_APP_CONFIG_MESSAGE_QUEUES"
#else
#if (__TERMINA_APP_CONFIG_MESSAGE_QUEUES > 0)

/**
 * \brief Size of the message queue object tables.
 */
#define __TERMINA_SHARED_MSG_QUEUE_TABLE_SIZE __TERMINA_APP_CONFIG_MESSAGE_QUEUES

/**
 * \brief Checks whether a message queue identifier is valid.
 *
 * @param[in] msg_queue_id the message queue identifier.
 *
 * @return true if the identifier is less than the number of message queues
 *         defined in the application, false otherwise.
 */
static inline bool __termina_shared_msg_queue__is_valid_id(const __termina_id_t msg_queue_id) {
    return (msg_queue_id < __TERMINA_APP_CONFIG_MESSAGE_QUEUES);
}

#else

// The application defines no message queues. ISO C does not allow arrays of
// size zero, so the tables keep one unused element, and no identifier is valid.
#define __TERMINA_SHARED_MSG_QUEUE_TABLE_SIZE 1U

static inline bool __termina_shared_msg_queue__is_valid_id(const __termina_id_t msg_queue_id) {
    (void)msg_queue_id;
    return false;
}

#endif
#endif

extern __termina_shared_msg_queue_t __shared_app_msg_queue_object_table[__TERMINA_SHARED_MSG_QUEUE_TABLE_SIZE];

static inline __termina_shared_msg_queue_t * __termina_shared_msg_queue__get_queue(const __termina_id_t msg_queue_id) {
    return &__shared_app_msg_queue_object_table[msg_queue_id];
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
void __termina_os_msg_queue__init(const __termina_id_t msg_queue_id,
                                  int32_t * const status);

/**
 * \brief Sends a message through a queue.
 * 
 * @param[in]   msg_queue  the message queue identifier.
 * @param[in]   data       pointer to the data to be sent.
 * @param[out]  status     Zero if OK or another value in case of an error.
 */
void __termina_os_msg_queue__send(const __termina_id_t msg_queue_id,
                                  const void * const data,
                                  int32_t * const status);

/**
 * \brief Receives a message through a queue.
 *
 * @param[in]   msg_queue  the message queue identifier.
 * @param[in]   element    pointer to the element from which the
 *                         message will be received.
 * @param[out]  status     Zero if OK or another value in case of an error.
 */
void __termina_os_msg_queue__recv(const __termina_id_t msg_queue_id,
                                  void * const element,
                                  int32_t * const status);


#endif // __TERMINA__SHARED__MSG_QUEUE_H__
