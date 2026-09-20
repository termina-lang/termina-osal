
#include <termina.h>

#include <termina/shared/list/list.h>
#include <termina/shared/task.h>
#include <termina/shared/mutex.h>
#include <termina/os/posix/signal.h>
#include <termina/os/posix/task.h>

/**
 * \brief Structure that represents a mutex.
 */
typedef struct {

    //! Identifier of the task that currently owns the mutex.
    // If the mutex is not owned, this field is set to TERMINA__ID__INVALID.
    termina__id_t owner;

    //! Previous priority of the current owner
    termina__task_prio_t owner_previous_priority;

    termina__shared__list_t waiting_tasks;

} termina__posix__mutex_t;

static termina__posix__mutex_t termina__posix__mutex_object_table[TERMINA__SHARED__MUTEX_TABLE_SIZE];

static inline termina__posix__mutex_t * termina__posix__mutex__get_mutex(const termina__id_t mutex_id) {
    return &termina__posix__mutex_object_table[mutex_id];
}

void termina__os__mutex__init(const termina__id_t mutex_id,
                              int32_t * const status) {
    
    termina__posix__mutex_t * mutex = termina__posix__mutex__get_mutex(mutex_id);

    mutex->owner = TERMINA__ID__INVALID;

    termina__shared__list__init(&mutex->waiting_tasks, 
                              TERMINA__SHARED_LIST__PRIORITY,
                              status);

    return;

}

void termina__os__mutex__lock(const termina__id_t mutex_id,
                              int32_t * const status) {
    
    termina__shared__mutex_t * mutex = termina__shared__mutex__get_mutex(mutex_id);
    termina__posix__mutex_t * posix_mutex = termina__posix__mutex__get_mutex(mutex_id);

    *status = 0;

    termina__posix__signal__disable();

    if (TERMINA__ID__INVALID == posix_mutex->owner) {

        termina__posix__task_t * posix_task = termina__posix__task__get_task(termina__posix__current_task_id);

        posix_mutex->owner = termina__posix__current_task_id;
        posix_mutex->owner_previous_priority = posix_task->current_priority;
        posix_task->current_priority = mutex->protocol.Ceiling._0;

        if (0 == termina__posix__task__disable_scheduling) {
            termina__posix__task__schedule();
        }


    } else {

        termina__shared__list__prio_add(&posix_mutex->waiting_tasks, 
                                        termina__posix__current_task_id, 
                                        termina__posix__task__get_current_priority(termina__posix__current_task_id), 
                                        status);

        if (0 == *status) {

            if (0 == termina__posix__task__disable_scheduling) {
                termina__posix__task__yield();
            }

        }

    }

    termina__posix__signal__enable();

    return;

}

void termina__os__mutex__unlock(const termina__id_t mutex_id,
                                int32_t * const status) {
    
    termina__posix__mutex_t * mutex = termina__posix__mutex__get_mutex(mutex_id);
    *status = 0;

    termina__posix__signal__disable();

    if (termina__posix__current_task_id != mutex->owner) {

        *status = -1;

    }

    if (0 == *status) {

        if (0 == mutex->waiting_tasks.items) {

            termina__posix__task_t * posix_task = termina__posix__task__get_task(termina__posix__current_task_id);

            posix_task->current_priority = mutex->owner_previous_priority;
            mutex->owner = TERMINA__ID__INVALID;

        } else {

            termina__id_t waiting_task_id = termina__shared__list__extract(&mutex->waiting_tasks);
            termina__posix__task_t * waiting_task = termina__posix__task__get_task(waiting_task_id);
            mutex->owner = waiting_task_id;

            termina__posix__task__insert_ready(waiting_task_id, 
                                       waiting_task->current_priority, status);
            // TODO: Check the return status

        }

        if (0 == termina__posix__task__disable_scheduling) {

            termina__posix__task__schedule();

        }

    }

    termina__posix__signal__enable();

    return;

}
