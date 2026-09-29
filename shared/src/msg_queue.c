
#include <termina.h>

#include <termina/shared/msg_queue.h>

termina__shared__msg_queue_t termina__shared__msg_queue_object_table[TERMINA__SHARED__MSG_QUEUE_TABLE_SIZE];

void termina__msg_queue__init(const termina__id_t msg_queue_id,
                               size_t message_size,
                               size_t message_queue_size,
                               int32_t * const status) {
    
    *status = 0;

    if (!termina__shared__msg_queue__is_valid_id(msg_queue_id)) {

        *status = -1;

    }

    if (0 == *status) {

        termina__shared__msg_queue_t * msg_queue = termina__shared__msg_queue__get_queue(msg_queue_id);

        msg_queue->msg_queue_id = msg_queue_id;
        msg_queue->message_size = message_size;
        msg_queue->message_queue_size = message_queue_size;
        
        termina__os__msg_queue__init(msg_queue_id, status);

    }

    return;

} 

void termina__msg_queue__send(const termina__id_t msg_queue_id, 
                               const void * const element,
                               int32_t * const status) {

    *status = 0;

    if (!termina__shared__msg_queue__is_valid_id(msg_queue_id)) {

        *status = -1;

    }

    if (0 == *status) {

        termina__os__msg_queue__send(msg_queue_id, element, status);

    }

    return;

}

void termina__msg_queue__recv(const termina__id_t msg_queue_id,
                               void * const element,
                               int32_t * const status) {

    *status = 0;

    if (!termina__shared__msg_queue__is_valid_id(msg_queue_id)) {

        *status = -1;

    }

    if (0 == *status) {

        termina__os__msg_queue__recv(msg_queue_id, element, status);

    }

    return;

}

void termina__shared__msg_queue__deliver(const termina__id_t port_msg_queue_id,
                                         const void * const message,
                                         const termina__id_t task_msg_queue_id,
                                         const termina__event_t * const event) {

    int32_t status = 0;

    if (NULL == message) {

        status = -1;

    } else {

        termina__msg_queue__send(port_msg_queue_id, message, &status);

    }

    if (0 != status) {

        // The message did not reach the queue of the port.
        termina__except__msg_queue_send_error(port_msg_queue_id, status);

    } else {

        // Notify the task that a message has been sent
        termina__msg_queue__send(task_msg_queue_id, event, &status);

        if (0 != status) {

            // The message is in the queue of the port, and the task would
            // never be told that it is there.
            termina__except__msg_queue_send_error(task_msg_queue_id, status);

        }

    }

}

void termina__out_port__send(const termina__event_t * const termina__ev,
                              const termina__out_port_t out_port,
                              const void * const element) {

    termina__event_t ev = {
        .emitter_id = termina__ev->emitter_id,
        .owner.type = termina__active_entity__task,
        .owner.task.task_id= out_port->task_id,
        .port_id = out_port->port_id
    };

    termina__shared__msg_queue__deliver(out_port->channel_msg_queue_id,
                                        element,
                                        out_port->task_msg_queue_id,
                                        &ev);

}
