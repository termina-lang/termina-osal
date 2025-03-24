
#include <termina.h>

#include <termina/shared/msg_queue.h>

#include <termina/os/rtems5/name.h>

#include <rtems.h>

typedef struct {

    rtems_id rtems_msg_queue_id;

} __rtems_msg_queue_t;

__rtems_msg_queue_t __rtems_msg_queue_object_table[__TERMINA_APP_CONFIG_MESSAGE_QUEUES];

static inline __rtems_msg_queue_t * __rtems_msg_queue__get_queue(const __termina_id_t queue_id) {
    return &__rtems_msg_queue_object_table[queue_id];
}

/**
 * \brief Array used to generate the names of the message queues that are
 *        created.
 */
static int8_t nmsg_queue_name[5]  = "0000";

void __termina_os_msg_queue__init(const __termina_id_t queue_id,
                                  Status * const status) {

    status->__variant = Status__Success;

    __termina_shared_msg_queue_t * msg_queue = __termina_shared_msg_queue__get_queue(queue_id);
    __rtems_msg_queue_t * rtems_queue = __rtems_msg_queue__get_queue(queue_id);

    rtems_name name;                        
                                            
    NEXT_OBJECT_NAME(nmsg_queue_name[0], nmsg_queue_name[1], nmsg_queue_name[2],
            nmsg_queue_name[3]);
    name = rtems_build_name(nmsg_queue_name[0], nmsg_queue_name[1], nmsg_queue_name[2],
                            nmsg_queue_name[3]);
    

    if (rtems_message_queue_create(name, msg_queue->message_queue_size, 
                                   msg_queue->message_size, RTEMS_FIFO, 
                                   &rtems_queue->rtems_msg_queue_id) != RTEMS_SUCCESSFUL) {

        status->__variant = Status__Error;
        status->Error.__0.__variant = Exception__InternalError;

    }

    return;
}

void __termina_os_msg_queue__send(const __termina_id_t queue_id,
                                  const void * const data,
                                  Status * const status) {

    __termina_shared_msg_queue_t * msg_queue = __termina_shared_msg_queue__get_queue(queue_id);
    __rtems_msg_queue_t * rtems_queue = __rtems_msg_queue__get_queue(queue_id);

    status->__variant = Status__Success;

    if (rtems_message_queue_send(rtems_queue->rtems_msg_queue_id, data, 
                                 msg_queue->message_size) != RTEMS_SUCCESSFUL) {

        status->__variant = Status__Error;
        status->Error.__0.__variant = Exception__InternalError;
        
    }

    return;

}

void __termina_os_msg_queue__recv(const __termina_id_t queue_id,
                                  void * const data,
                                  Status * const status) {

    __termina_shared_msg_queue_t * msg_queue = __termina_shared_msg_queue__get_queue(queue_id);
    __rtems_msg_queue_t * rtems_queue = __rtems_msg_queue__get_queue(queue_id);

    status->__variant = Status__Success;

    size_t size = 0;

    if (rtems_message_queue_receive(rtems_queue->rtems_msg_queue_id, data, 
                                    &size, RTEMS_WAIT, 
                                    RTEMS_NO_TIMEOUT) != RTEMS_SUCCESSFUL) {

        status->__variant = Status__Error;
        status->Error.__0.__variant = Exception__InternalError;
        
    }

    return;

}
