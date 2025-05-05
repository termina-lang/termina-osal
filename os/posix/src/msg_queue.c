
#include <termina.h>

#include <termina/shared/task.h>
#include <termina/shared/msg_queue.h>
#include <termina/os/posix/task.h>

#include <stdlib.h>
#include <string.h>

/**
 * \brief Structure that represents an element of a task list.
 */
struct __posix_msg_queue_item {

    void * data;

    //! Next task in the list
    struct __posix_msg_queue_item * next;

};

typedef struct __posix_msg_queue_item __posix_msg_queue_item_t;


/**
 * \brief Structure used to create task lists.
 */
typedef struct {

    //! Pointer to the first element of the queue.
    __posix_msg_queue_item_t * first;

    //! Pointer to the last element of the queue.
    __posix_msg_queue_item_t * last;

    //! Identifier of the task that is currently waiting for a message.
    __termina_id_t waiting_task;

    //! Number of items in the queue.
    size_t items;

} __posix_msg_queue_t;

__posix_msg_queue_t __posix_msg_queue_object_table[__TERMINA_APP_CONFIG_MESSAGE_QUEUES];

static inline __posix_msg_queue_t * __posix_msg_queue__get_queue(const __termina_id_t queue_id) {
    return &__posix_msg_queue_object_table[queue_id];
}

void __termina_os_msg_queue__init(const __termina_id_t queue_id,
                                  int32_t * const status) {

    *status = 0;

    __posix_msg_queue_t * posix_queue = __posix_msg_queue__get_queue(queue_id);

    posix_queue->first = NULL;
    posix_queue->last = NULL;
    posix_queue->waiting_task = __TERMINA_ID_INVALID;
    posix_queue->items = 0;

    return;
}

void __termina_os_msg_queue__send(const __termina_id_t queue_id,
                                  const void * const data,
                                  int32_t * const status) {

    __termina_shared_msg_queue_t * msg_queue = __termina_shared_msg_queue__get_queue(queue_id);
    __posix_msg_queue_t * posix_queue = __posix_msg_queue__get_queue(queue_id);

    *status = 0;

    __posix_signal__disable();

    if (posix_queue->items == msg_queue->message_queue_size) {

        *status = -1;

    }

    __posix_msg_queue_item_t * item = NULL;

    if (0 == *status) {

        item = (__posix_msg_queue_item_t *)malloc(sizeof(__posix_msg_queue_item_t));

        if (NULL == item) {
            *status = -1;
        }

    }

    if (0 == *status) {

        item->data = malloc(msg_queue->message_size);

        if (NULL == item) {
            *status = -1;
        }

    }

    if (0 == *status) {

        memcpy(item->data, data, msg_queue->message_size);
        item->next = NULL;

        if (NULL == posix_queue->first) {
            posix_queue->first = item;
            posix_queue->last = item;
        } else {
            posix_queue->last->next = item;
            posix_queue->last = item;
        }

        posix_queue->items = posix_queue->items + 1;

        if (__TERMINA_ID_INVALID != posix_queue->waiting_task) {

            __posix_task_t * waiting_task = __posix_task__get_task(posix_queue->waiting_task);
            __posix_task__insert_ready(posix_queue->waiting_task, 
                                       waiting_task->current_priority, status);
            // TODO: Check the return status

            if (0 == __posix_task__disable_scheduling) {

                __posix_task__schedule();

            }

        }

        *status = 0;

    }

    __posix_signal__enable();

    return;

}

void __termina_os_msg_queue__recv(const __termina_id_t queue_id,
                                  void * const data,
                                  int32_t * const status) {

    __termina_shared_msg_queue_t * msg_queue = __termina_shared_msg_queue__get_queue(queue_id);
    __posix_msg_queue_t * posix_msg_queue = __posix_msg_queue__get_queue(queue_id);

    *status = 0;

    __posix_signal__disable();

    if (posix_msg_queue->items == 0) {

        // We are assuming here that there could be only one task waiting for a
        // message (maybe we should assert this)
        posix_msg_queue->waiting_task = __posix_current_task_id;

        __posix_task__yield();

        // When we get here, it means that we were woken up by a message and
        // that the message is already in the queue and that we are no longer
        // waiting for it
        posix_msg_queue->waiting_task = __TERMINA_ID_INVALID;

    }

    // If we are here, it means that there is a message in the queue, either
    // because it was there before or because it was sent while we were waiting

    __posix_msg_queue_item_t * item = posix_msg_queue->first;

    posix_msg_queue->first = item->next;

    posix_msg_queue->items = posix_msg_queue->items - 1;

    memcpy(data, item->data, msg_queue->message_size);

    free(item->data);

    free(item);

    __posix_signal__enable();

    return;

}
