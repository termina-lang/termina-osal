
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

    termina__shared_list_t waiting_tasks;

} __posix_mutex_t;

static __posix_mutex_t __posix_mutex_object_table[TERMINA__SHARED__MUTEX_TABLE_SIZE];

static inline __posix_mutex_t * __posix_mutex__get_mutex(const termina__id_t mutex_id) {
    return &__posix_mutex_object_table[mutex_id];
}

void termina__os_mutex__init(const termina__id_t mutex_id,
                              int32_t * const status) {
    
    __posix_mutex_t * mutex = __posix_mutex__get_mutex(mutex_id);

    mutex->owner = TERMINA__ID__INVALID;

    termina__shared_list__init(&mutex->waiting_tasks, 
                              TERMINA__SHARED_LIST__PRIORITY,
                              status);

    return;

}

void termina__os_mutex__lock(const termina__id_t mutex_id,
                              int32_t * const status) {
    
    termina__shared_mutex_t * mutex = termina__shared_mutex__get_mutex(mutex_id);
    __posix_mutex_t * posix_mutex = __posix_mutex__get_mutex(mutex_id);

    *status = 0;

    __posix_signal__disable();

    if (TERMINA__ID__INVALID == posix_mutex->owner) {

        __posix_task_t * posix_task = __posix_task__get_task(__posix_current_task_id);

        posix_mutex->owner = __posix_current_task_id;
        posix_mutex->owner_previous_priority = posix_task->current_priority;
        posix_task->current_priority = mutex->protocol.Ceiling._0;

        if (0 == __posix_task__disable_scheduling) {
            __posix_task__schedule();
        }


    } else {

        termina__shared_list__prio_add(&posix_mutex->waiting_tasks, 
                                        __posix_current_task_id, 
                                        __posix_task__get_current_priority(__posix_current_task_id), 
                                        status);

        if (0 == *status) {

            if (0 == __posix_task__disable_scheduling) {
                __posix_task__yield();
            }

        }

    }

    __posix_signal__enable();

    return;

}

void termina__os_mutex__unlock(const termina__id_t mutex_id,
                                int32_t * const status) {
    
    __posix_mutex_t * mutex = __posix_mutex__get_mutex(mutex_id);
    *status = 0;

    __posix_signal__disable();

    if (__posix_current_task_id != mutex->owner) {

        *status = -1;

    }

    if (0 == *status) {

        if (0 == mutex->waiting_tasks.items) {

            __posix_task_t * posix_task = __posix_task__get_task(__posix_current_task_id);

            posix_task->current_priority = mutex->owner_previous_priority;
            mutex->owner = TERMINA__ID__INVALID;

        } else {

            termina__id_t waiting_task_id = termina__shared_list__extract(&mutex->waiting_tasks);
            __posix_task_t * waiting_task = __posix_task__get_task(waiting_task_id);
            mutex->owner = waiting_task_id;

            __posix_task__insert_ready(waiting_task_id, 
                                       waiting_task->current_priority, status);
            // TODO: Check the return status

        }

        if (0 == __posix_task__disable_scheduling) {

            __posix_task__schedule();

        }

    }

    __posix_signal__enable();

    return;

}
