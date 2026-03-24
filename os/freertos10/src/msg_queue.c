
#include <termina.h>

#include <termina/shared/msg_queue.h>

#include <termina/os/freertos10/name.h>

#include <FreeRTOS.h>
#include "queue.h"

typedef struct {

    QueueHandle_t xHandle;

} __freertos_msg_queue_t;

__freertos_msg_queue_t __freertos_msg_queue_object_table[__TERMINA_APP_CONFIG_MESSAGE_QUEUES];

static inline __freertos_msg_queue_t * __freertos_msg_queue__get_queue(const __termina_id_t queue_id) {
    return &__freertos_msg_queue_object_table[queue_id];
}



void __termina_os_msg_queue__init(const __termina_id_t queue_id,
                                  int32_t * const status) {

    *status = 0;

    __termina_shared_msg_queue_t * msg_queue = __termina_shared_msg_queue__get_queue(queue_id);
    __freertos_msg_queue_t * freertos_queue = __freertos_msg_queue__get_queue(queue_id);

    freertos_queue->xHandle = xQueueCreate(msg_queue->message_queue_size, // The number of items the queue can hold.
                                           msg_queue->message_size ); // The size of each item in the queue in bytes
    
    if (NULL == freertos_queue->xHandle) {

        // Queue was not created and must not be used.
        *status = -1;

    }

    return;
}

void __termina_os_msg_queue__send(const __termina_id_t queue_id,
                                  const void * const data,
                                  int32_t * const status) {

    __freertos_msg_queue_t * freertos_queue = __freertos_msg_queue__get_queue(queue_id);

    *status = 0;

    if (xPortIsInsideInterrupt()) {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        if (xQueueSendFromISR(freertos_queue->xHandle, data, &xHigherPriorityTaskWoken) != pdTRUE) {
            *status = -1;
        }
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    } else {
        if (xQueueSend(freertos_queue->xHandle, data, portMAX_DELAY) != pdTRUE) {
            *status = -1;
        }
    }

    return;

}

void __termina_os_msg_queue__recv(const __termina_id_t queue_id,
                                  void * const data,
                                  int32_t * const status) {

    __freertos_msg_queue_t * freertos_queue = __freertos_msg_queue__get_queue(queue_id);

    *status = 0;

    if (xQueueReceive(freertos_queue->xHandle, data, portMAX_DELAY) != pdTRUE) {

        *status = -1;
        
    }

    return;

}
