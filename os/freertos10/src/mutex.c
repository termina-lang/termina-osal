
#include <termina.h>

#include <termina/shared/task.h>
#include <termina/shared/mutex.h>
#include <termina/os/freertos10/priority.h>

#include <FreeRTOS.h>
#include "task.h"

typedef struct {

    //! Task that holds the mutex, or NULL when it is free.
    TaskHandle_t owner;

    //! Priority of the owner before it took the mutex.
    UBaseType_t saved_priority;

} termina__freertos__mutex_t;


static termina__freertos__mutex_t termina__freertos__mutex_object_table[TERMINA__SHARED__MUTEX_TABLE_SIZE];

static inline termina__freertos__mutex_t * termina__freertos__mutex__get_mutex(const termina__id_t mutex_id) {
    return &termina__freertos__mutex_object_table[mutex_id];
}


void termina__os__mutex__init(const termina__id_t mutex_id,
                              int32_t * const status) {
    
    termina__freertos__mutex_t * const freertos_mutex = termina__freertos__mutex__get_mutex(mutex_id);

    /* No FreeRTOS kernel object is created. Mutual exclusion is a
     * consequence of the IPCP priority elevation performed on lock.
     * The saved priority slot is initialised but unused until the
     * first lock. */
    freertos_mutex->owner = NULL;
    freertos_mutex->saved_priority = (UBaseType_t) 0U;
    *status = 0;
    return;

}

void termina__os__mutex__lock(const termina__id_t mutex_id,
                              int32_t * const status) {

    const termina__shared__mutex_t * const shared_mutex = termina__shared__mutex__get_mutex(mutex_id);
    termina__freertos__mutex_t * const freertos_mutex = termina__freertos__mutex__get_mutex(mutex_id);

    *status = 0;

    taskENTER_CRITICAL();

    if (NULL != freertos_mutex->owner) {

        // Another task holds the mutex, which the ceiling should have ruled
        // out.
        *status = -1;

    } else {

        freertos_mutex->owner = xTaskGetCurrentTaskHandle();
        freertos_mutex->saved_priority = uxTaskPriorityGet(NULL);
        vTaskPrioritySet(NULL,
            termina__freertos__task__priority_to_freertos(shared_mutex->protocol.Ceiling._0));

    }

    taskEXIT_CRITICAL();

    return;

}

void termina__os__mutex__unlock(const termina__id_t mutex_id,
                                int32_t * const status) {

    termina__freertos__mutex_t * const freertos_mutex = termina__freertos__mutex__get_mutex(mutex_id);

    *status = 0;

    taskENTER_CRITICAL();

    if (xTaskGetCurrentTaskHandle() != freertos_mutex->owner) {

        // Only the owner gives the mutex back.
        *status = -1;

    } else {

        freertos_mutex->owner = NULL;
        vTaskPrioritySet(NULL, freertos_mutex->saved_priority);

    }

    taskEXIT_CRITICAL();

    return;

}

