
#include <termina.h>

#include <termina/shared/task.h>
#include <termina/shared/mutex.h>

#include <FreeRTOS.h>
#include "task.h"

typedef struct {

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
    freertos_mutex->saved_priority = (UBaseType_t) 0U;
    *status = 0;
    return;

}

void termina__os__mutex__lock(const termina__id_t mutex_id,
                              int32_t * const status) {
    
    const termina__shared__mutex_t * const shared_mutex = termina__shared__mutex__get_mutex(mutex_id);
    termina__freertos__mutex_t * const freertos_mutex = termina__freertos__mutex__get_mutex(mutex_id);

    taskENTER_CRITICAL();
    freertos_mutex->saved_priority = uxTaskPriorityGet(NULL);
    vTaskPrioritySet(NULL, (UBaseType_t) shared_mutex->protocol.Ceiling._0);
    taskEXIT_CRITICAL();

    *status = 0;

    return;

}

void termina__os__mutex__unlock(const termina__id_t mutex_id,
                                int32_t * const status) {
    
    const termina__freertos__mutex_t * const freertos_mutex = termina__freertos__mutex__get_mutex(mutex_id);

    vTaskPrioritySet(NULL, freertos_mutex->saved_priority);

    *status = 0;

    return;

}

