
#include <termina.h>

#include <termina/shared/msg_queue.h>

__termina_shared_msg_queue_t __shared_app_msg_queue_object_table[__TERMINA_APP_CONFIG_MESSAGE_QUEUES];

void __termina_msg_queue__init(const __termina_id_t msg_queue_id,
                               size_t message_size,
                               size_t message_queue_size,
                               int32_t * const status) {
    
    *status = 0;

    if (msg_queue_id >= __TERMINA_APP_CONFIG_MESSAGE_QUEUES) {

        *status = -1;

    }

    if (0 == *status) {

        __termina_shared_msg_queue_t * msg_queue = __termina_shared_msg_queue__get_queue(msg_queue_id);

        msg_queue->msg_queue_id = msg_queue_id;
        msg_queue->message_size = message_size;
        msg_queue->message_queue_size = message_queue_size;
        
        __termina_os_msg_queue__init(msg_queue_id, status);

    }

    return;

} 

void __termina_msg_queue__send(const __termina_id_t msg_queue_id, 
                               const void * const element,
                               int32_t * const status) {

    *status = 0;

    if (msg_queue_id >= __TERMINA_APP_CONFIG_MESSAGE_QUEUES) {

        *status = -1;

    }

    if (0 == *status) {

        __termina_os_msg_queue__send(msg_queue_id, element, status);

    }

    return;

}

void __termina_msg_queue__recv(const __termina_id_t msg_queue_id,
                               void * const element,
                               int32_t * const status) {

    *status = 0;

    if (msg_queue_id >= __TERMINA_APP_CONFIG_MESSAGE_QUEUES) {

        *status = -1;

    }

    if (0 == *status) {

        __termina_os_msg_queue__recv(msg_queue_id, element, status);

    }

    return;

}

void __termina_out_port__send(const __termina_out_port_t out_port,
                              const void * const element) {

    int32_t status = 0;

    __termina_msg_queue__send(out_port->channel_msg_queue_id,
                              element, &status);

    if (0 == status) {

        // Notify the task that a message has been sent
        __termina_msg_queue__send(out_port->task_msg_queue_id,
                                  &out_port->port_id, &status);

    }
    
}
