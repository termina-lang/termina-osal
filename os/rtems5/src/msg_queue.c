
#include <termina.h>

#include <termina/shared/msg_queue.h>

#include <termina/os/rtems5/name.h>

#include <rtems.h>

typedef struct {

    rtems_id rtems_msg_queue_id;

} termina__rtems__msg_queue_t;

termina__rtems__msg_queue_t termina__rtems__msg_queue_object_table[TERMINA__SHARED__MSG_QUEUE_TABLE_SIZE];

static inline termina__rtems__msg_queue_t * termina__rtems__msg_queue__get_queue(const termina__id_t queue_id) {
    return &termina__rtems__msg_queue_object_table[queue_id];
}

/**
 * \brief Array used to generate the names of the message queues that are
 *        created.
 */
static int8_t nmsg_queue_name[5]  = "0000";

void termina__os__msg_queue__init(const termina__id_t queue_id,
                                  int32_t * const status) {

    *status = 0;

    termina__shared__msg_queue_t * msg_queue = termina__shared__msg_queue__get_queue(queue_id);
    termina__rtems__msg_queue_t * rtems_queue = termina__rtems__msg_queue__get_queue(queue_id);

    rtems_name name;                        
                                            
    NEXT_OBJECT_NAME(nmsg_queue_name[0], nmsg_queue_name[1], nmsg_queue_name[2],
            nmsg_queue_name[3]);
    name = rtems_build_name(nmsg_queue_name[0], nmsg_queue_name[1], nmsg_queue_name[2],
                            nmsg_queue_name[3]);
    

    if (rtems_message_queue_create(name, msg_queue->message_queue_size, 
                                   msg_queue->message_size, RTEMS_FIFO, 
                                   &rtems_queue->rtems_msg_queue_id) != RTEMS_SUCCESSFUL) {

        *status = -1;

    }

    return;
}

void termina__os__msg_queue__send(const termina__id_t queue_id,
                                  const void * const data,
                                  int32_t * const status) {

    termina__shared__msg_queue_t * msg_queue = termina__shared__msg_queue__get_queue(queue_id);
    termina__rtems__msg_queue_t * rtems_queue = termina__rtems__msg_queue__get_queue(queue_id);

    *status = 0;

    if (rtems_message_queue_send(rtems_queue->rtems_msg_queue_id, data, 
                                 msg_queue->message_size) != RTEMS_SUCCESSFUL) {

        *status = -1;
        
    }

    return;

}

void termina__os__msg_queue__recv(const termina__id_t queue_id,
                                  void * const data,
                                  int32_t * const status) {

    termina__rtems__msg_queue_t * rtems_queue = termina__rtems__msg_queue__get_queue(queue_id);

    *status = 0;

    size_t size = 0;

    if (rtems_message_queue_receive(rtems_queue->rtems_msg_queue_id, data, 
                                    &size, RTEMS_WAIT, 
                                    RTEMS_NO_TIMEOUT) != RTEMS_SUCCESSFUL) {

        *status = -1;
        
    }

    return;

}
