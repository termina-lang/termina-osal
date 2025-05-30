
#include <termina.h>

#include <termina/shared/task.h>


__termina_shared_task_t __shared_app_task_object_table[__TERMINA_APP_CONFIG_TASKS];

void __termina_task__init(const __termina_id_t task_id,
                          __termina_task_prio_t priority,
                          size_t stack_size,
                          __termina_task_entry_t entry,
                          void * arg,
                          int32_t * const status) {

    *status = 0;

    if (task_id >= __TERMINA_APP_CONFIG_TASKS) {

        *status = -1;

    }

    if (0 == *status) {

        __termina_shared_task_t * task = __termina_shared_task__get_task(task_id);

        task->task_id = task_id;
        task->priority = priority;
        task->stack_size = stack_size;
        task->entry = entry;
        task->arg = arg;

        __termina_os_task__init(task_id, status);

    }

    return;

}
