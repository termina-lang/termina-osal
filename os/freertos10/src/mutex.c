
#include <termina.h>

#include <termina/shared/task.h>
#include <termina/shared/mutex.h>

#include <FreeRTOS.h>
#include "semphr.h"

typedef struct {

    SemaphoreHandle_t xHandle;

} __freertos_mutex_t;


static __freertos_mutex_t __freertos_mutex_object_table[__TERMINA_APP_CONFIG_MUTEXES];

static inline __freertos_mutex_t * __freertos_mutex__get_mutex(const __termina_id_t mutex_id) {
    return &__freertos_mutex_object_table[mutex_id];
}


void __termina_os_mutex__init(const __termina_id_t mutex_id,
                              int32_t * const status) {
    
    __freertos_mutex_t * freertos_mutex = __freertos_mutex__get_mutex(mutex_id);

    *status = -1;

    freertos_mutex->xHandle = xSemaphoreCreateMutex();

    if (freertos_mutex->xHandle != NULL) {
        *status = 0;
        return;
    }


   return;

}

void __termina_os_mutex__lock(const __termina_id_t mutex_id,
                              int32_t * const status) {
    
    __freertos_mutex_t * freertos_mutex = __freertos_mutex__get_mutex(mutex_id);

    *status = 0;

    if (xSemaphoreTake(freertos_mutex->xHandle, portMAX_DELAY) != pdTRUE) {
        *status = -1;
    }

    return;

}

void __termina_os_mutex__unlock(const __termina_id_t mutex_id,
                                int32_t * const status) {
    
    __freertos_mutex_t * freertos_mutex = __freertos_mutex__get_mutex(mutex_id);

    *status = 0;

    if (xSemaphoreGive(freertos_mutex->xHandle) != pdTRUE) {

        *status = -1;

    }

    return;

}

