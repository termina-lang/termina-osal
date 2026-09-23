
#include <termina.h>

#include <termina/shared/task.h>

#include <termina/os/freertos10/name.h>
#include <termina/os/freertos10/priority.h>

#include <FreeRTOS.h>
#include "task.h"


typedef struct {

    TaskHandle_t freertos_task_id;

} termina__freertos__task_t;

termina__freertos__task_t termina__freertos__task_object_table[TERMINA__SHARED__TASK_TABLE_SIZE];

static inline termina__freertos__task_t * termina__freertos__task__get_task(const termina__id_t task_id) {
    return &termina__freertos__task_object_table[task_id];
}

/**
 * \brief Array used to generate the names of the tasks that are
 *        created.
 */
static char ntask_name[5]  = "0000";

static void termina__freertos__task__entry (void * arg) {

    termina__id_t * task_id = (termina__id_t *)arg;

    termina__shared__task_t * task = termina__shared__task__get_task(*task_id);

    // This function call shall never return
    task->entry(task->arg);

    return;

}

void termina__os__task__init(const termina__id_t task_id,
                             int32_t * const status) {

    *status = 0;

    termina__shared__task_t * task = termina__shared__task__get_task(task_id);
    termina__freertos__task_t * freertos_task = termina__freertos__task__get_task(task_id);
                                            
    NEXT_OBJECT_NAME(ntask_name[0], ntask_name[1], ntask_name[2],
            ntask_name[3]);

    UBaseType_t task_priority = termina__os__task__priority2freertos(task->priority);

    size_t stack_size_in_words = task->stack_size / sizeof(StackType_t);

    // Consider the case where the stack size is not multiple of StackType_t
    if (task->stack_size % sizeof(StackType_t) != 0) {
        stack_size_in_words = stack_size_in_words + 1;
    }

    if (xTaskCreate(termina__freertos__task__entry, ntask_name,
            stack_size_in_words,
            task->arg, task_priority,
            &freertos_task->freertos_task_id) != pdPASS) {
        
        *status = -1;

    }

    return;
}

