
#include <termina.h>

#include <termina/shared/task.h>


termina__shared__task_t termina__shared__task_object_table[TERMINA__SHARED__TASK_TABLE_SIZE];

void termina__task__init(const termina__id_t task_id,
                          const termina__task_prio_t priority,
                          const size_t stack_size,
                          termina__task_entry_t entry,
                          void * arg,
                          termina__error_code_t * const status) {

    *status = termina__error__none;

    if (!termina__shared__task__is_valid_id(task_id)) {

        *status = termina__error__invalid_id;

    }

    if (termina__error__none == *status) {

        termina__shared__task_t * task = termina__shared__task__get_task(task_id);

        task->task_id = task_id;
        task->priority = priority;
        task->stack_size = stack_size;
        task->entry = entry;
        task->arg = arg;

        termina__os__task__init(task_id, status);

    }

    if (termina__error__none != *status) {

        *status = termina__error__task_init;

    }

    return;

}

void termina__task__set_current_priority(const termina__task_prio_t priority,
                                         termina__error_code_t * const status) {

    *status = termina__error__none;

    if ((priority < TERMINA__TASK__MAXIMUM_PRIORITY)
        || (priority >= TERMINA__TASK__MINIMUM_PRIORITY)) {

        *status = termina__error__invalid_priority;

    } else {

        termina__os__task__set_current_priority(priority, status);

    }

    return;

}

void termina__task__reset_priority(termina__error_code_t * const status) {

    *status = termina__error__none;

    termina__id_t task_id = termina__os__task__current_id();

    if (!termina__shared__task__is_valid_id(task_id)) {

        *status = termina__error__invalid_id;

    } else {

        termina__os__task__set_current_priority(termina__shared__task__get_priority(task_id),
                                                status);

    }

    return;

}
