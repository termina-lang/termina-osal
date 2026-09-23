
#include <termina.h>

#include <termina/shared/task.h>


termina__shared__task_t termina__shared__task_object_table[TERMINA__SHARED__TASK_TABLE_SIZE];

void termina__task__init(const termina__id_t task_id,
                          termina__task_prio_t priority,
                          size_t stack_size,
                          termina__task_entry_t entry,
                          void * arg,
                          int32_t * const status) {

    *status = 0;

    if (!termina__shared__task__is_valid_id(task_id)) {

        *status = -1;

    }

    if (0 == *status) {

        termina__shared__task_t * task = termina__shared__task__get_task(task_id);

        task->task_id = task_id;
        task->priority = priority;
        task->stack_size = stack_size;
        task->entry = entry;
        task->arg = arg;

        termina__os__task__init(task_id, status);

    }

    return;

}
