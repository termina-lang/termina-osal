
#include <termina.h>

#include <termina/shared/task.h>

#include <termina/os/freertos10/name.h>
#include <termina/os/freertos10/priority.h>

#include <FreeRTOS.h>
#include "task.h"


typedef struct {

    TaskHandle_t freertos_task_id;

} __freertos_task_t;

__freertos_task_t __freertos_task_object_table[__TERMINA_APP_CONFIG_TASKS];

static inline __freertos_task_t * __freertos_task__get_task(const __termina_id_t task_id) {
    return &__freertos_task_object_table[task_id];
}

/**
 * \brief Array used to generate the names of the tasks that are
 *        created.
 */
static char ntask_name[5]  = "0000";

static void __freertos_task__entry (void * arg) {

    __termina_id_t * task_id = (__termina_id_t *)arg;

    __termina_shared_task_t * task = __termina_shared_task__get_task(*task_id);

    // This function call shall never return
    task->entry(task->arg);

    return;

}

void __termina_os_task__init(const __termina_id_t task_id,
                             int32_t * const status) {

    *status = 0;

    __termina_shared_task_t * task = __termina_shared_task__get_task(task_id);
    __freertos_task_t * freertos_task = __freertos_task__get_task(task_id);
                                            
    NEXT_OBJECT_NAME(ntask_name[0], ntask_name[1], ntask_name[2],
            ntask_name[3]);

    UBaseType_t task_priority = __termina_os_task__priority2freertos(task->priority);

    uint16_t stack_size_in_words = task->stack_size / sizeof(StackType_t);

    // Consider the case where the stack size is not multiple of StackType_t
    if (task->stack_size % sizeof(StackType_t) != 0) {
        stack_size_in_words = stack_size_in_words + 1;
    }

    if (xTaskCreate(__freertos_task__entry, ntask_name,
            stack_size_in_words,
            task->arg, task_priority,
            &freertos_task->freertos_task_id) != pdPASS) {
        
        *status = -1;

    }

    return;
}

