
#include <termina.h>

#include <termina/shared/msg_queue.h>

#include <termina/os/freertos10/name.h>

#include <FreeRTOS.h>
#include "queue.h"

typedef struct {

    QueueHandle_t xHandle;

} termina__freertos__msg_queue_t;

termina__freertos__msg_queue_t termina__freertos__msg_queue_object_table[TERMINA__SHARED__MSG_QUEUE_TABLE_SIZE];

static inline termina__freertos__msg_queue_t * termina__freertos__msg_queue__get_queue(const termina__id_t queue_id) {
    return &termina__freertos__msg_queue_object_table[queue_id];
}



void termina__os__msg_queue__init(const termina__id_t queue_id,
                                  termina__error_code_t * const status) {

    *status = termina__error__none;

    termina__shared__msg_queue_t * msg_queue = termina__shared__msg_queue__get_queue(queue_id);
    termina__freertos__msg_queue_t * freertos_queue = termina__freertos__msg_queue__get_queue(queue_id);

    freertos_queue->xHandle = xQueueCreate(msg_queue->message_queue_size, // The number of items the queue can hold.
                                           msg_queue->message_size ); // The size of each item in the queue in bytes
    
    if (NULL == freertos_queue->xHandle) {

        // Queue was not created and must not be used.
        *status = termina__error__os_failure;

    }

    return;
}

void termina__os__msg_queue__send(const termina__id_t queue_id,
                                  const void * const data,
                                  termina__error_code_t * const status) {

    termina__freertos__msg_queue_t * freertos_queue = termina__freertos__msg_queue__get_queue(queue_id);

    *status = termina__error__none;

    if (xPortIsInsideInterrupt()) {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        if (xQueueSendFromISR(freertos_queue->xHandle, data, &xHigherPriorityTaskWoken) != pdTRUE) {
            *status = termina__error__queue_full;
        }
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    } else {
        // A send to a full queue fails at once instead of waiting for room,
        // as it does on the other back-ends.
        if (xQueueSend(freertos_queue->xHandle, data, 0) != pdTRUE) {
            *status = termina__error__queue_full;
        }
    }

    return;

}

void termina__os__msg_queue__recv(const termina__id_t queue_id,
                                  void * const data,
                                  termina__error_code_t * const status) {

    termina__freertos__msg_queue_t * freertos_queue = termina__freertos__msg_queue__get_queue(queue_id);

    *status = termina__error__none;

    if (xQueueReceive(freertos_queue->xHandle, data, portMAX_DELAY) != pdTRUE) {

        *status = termina__error__receive_failed;
        
    }

    return;

}
