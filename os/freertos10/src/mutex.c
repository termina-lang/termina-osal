
#include <termina.h>

#include <termina/shared/task.h>
#include <termina/shared/mutex.h>

#include <FreeRTOS.h>
#include "task.h"

typedef struct {

    UBaseType_t saved_priority;

} __freertos_mutex_t;


static __freertos_mutex_t __freertos_mutex_object_table[__TERMINA_APP_CONFIG_MUTEXES];

static inline __freertos_mutex_t * __freertos_mutex__get_mutex(const __termina_id_t mutex_id) {
    return &__freertos_mutex_object_table[mutex_id];
}


void __termina_os_mutex__init(const __termina_id_t mutex_id,
                              int32_t * const status) {
    
    __freertos_mutex_t * const freertos_mutex = __freertos_mutex__get_mutex(mutex_id);

    /* No FreeRTOS kernel object is created. Mutual exclusion is a
     * consequence of the IPCP priority elevation performed on lock.
     * The saved priority slot is initialised but unused until the
     * first lock. */
    freertos_mutex->saved_priority = (UBaseType_t) 0U;
    *status = 0;
    return;

}

void __termina_os_mutex__lock(const __termina_id_t mutex_id,
                              int32_t * const status) {
    
    const __termina_shared_mutex_t * const shared_mutex = __termina_shared_mutex__get_mutex(mutex_id);
    __freertos_mutex_t * const freertos_mutex = __freertos_mutex__get_mutex(mutex_id);

    taskENTER_CRITICAL();
    freertos_mutex->saved_priority = uxTaskPriorityGet(NULL);
    vTaskPrioritySet(NULL, (UBaseType_t) shared_mutex->prio_ceiling);
    taskEXIT_CRITICAL();

    *status = 0;

    return;

}

void __termina_os_mutex__unlock(const __termina_id_t mutex_id,
                                int32_t * const status) {
    
    const __freertos_mutex_t * const freertos_mutex = __freertos_mutex__get_mutex(mutex_id);

    vTaskPrioritySet(NULL, freertos_mutex->saved_priority);

    *status = 0;

    return;

}

