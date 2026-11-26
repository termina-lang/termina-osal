/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Tasks and scheduler of the POSIX emulation.
 */

#ifndef TERMINA__OS__POSIX__TASK_H__
#define TERMINA__OS__POSIX__TASK_H__

#include "config.h"

#include <termina.h>
#include <termina/shared/task.h>
#include <termina/os/posix/signal.h>

#include <pthread.h>

/** @brief Identifier of the idle task. */
#define TERMINA__POSIX__ID_IDLE_TASK TERMINA__ID__INVALID

/**
 * @brief Task of the POSIX emulation, over a POSIX thread.
 */
typedef struct {

    //! Thread of the task.
    pthread_t pthread;
    //! Mutex of the resume condition.
    pthread_mutex_t resume_mutex;
    //! Condition on which the task waits to resume.
    pthread_cond_t resume_cond;
    //! True when the task is to resume.
    _Bool resume_task;

    //! Current priority of the task.
    termina__task_prio_t current_priority;

} termina__posix__task_t;

/** @brief Identifier of the running task. */
extern termina__id_t termina__posix__current_task_id;
/** @brief Object of the idle task. */
extern termina__posix__task_t termina__posix__idle_task;

/** @brief Thread of the main task. */
extern pthread_t termina__posix__main_task_pthread;

/** @brief True while the scheduling is disabled. */
extern _Bool termina__posix__task__disable_scheduling;

/**
 * @brief Table of the task objects.
 * 
 * The table contains the task objects of all the tasks of the application,
 * indexed by task identifier. The table includes an extra task object for the
 * idle task.
 */
extern termina__posix__task_t termina__posix__app_task_object_table[TERMINA__SHARED__TASK_TABLE_SIZE];

/**
 * @brief Gets the POSIX task object of a task identifier.
 * 
 * The identifier must be valid, that is, less than the number of tasks of the
 * application, or `TERMINA__POSIX__ID_IDLE_TASK`.
 * 
 * @param[in] task_id  Identifier of the task.
 * 
 * @return Pointer to the POSIX task object.
 */
static inline termina__posix__task_t * termina__posix__task__get_task(const termina__id_t task_id) {

    termina__posix__task_t * task = NULL;

    if (TERMINA__POSIX__ID_IDLE_TASK == task_id) {
        task = &termina__posix__idle_task;
    } else {
        task = &termina__posix__app_task_object_table[task_id];
    }

    return task;

}

/**
 * @brief Gets the current priority of a task.
 * 
 * The identifier must be valid, that is, less than the number of tasks of the
 * application, or `TERMINA__POSIX__ID_IDLE_TASK`.
 * 
 * @param[in] task_id  Identifier of the task.
 * 
 * @return The current priority of the task.
 */
static inline termina__task_prio_t termina__posix__task__get_current_priority(const termina__id_t task_id) {

    termina__task_prio_t prio = 0;

    if (TERMINA__POSIX__ID_IDLE_TASK == task_id) {
        prio = TERMINA__TASK__IDLE_PRIORITY;
    } else {
        prio = termina__posix__app_task_object_table[task_id].current_priority;
    }

    return prio;

}

/**
 * @brief Initializes the scheduler.
 * 
 * The platform calls this function before the initialization of the
 * application.
 *
 * @param[out] status  Status of the operation: `termina__error__none`, or the
 *                     error code of the creation of the ready lists or of the
 *                     idle task.
 */
void termina__posix__task__init_scheduler(termina__error_code_t * const status);

/**
 * @brief Inserts a task at the end of the ready queue of its priority.
 *
 * @param[in]  task_id   Identifier of the task.
 * @param[in]  priority  Priority of the task.
 * @param[out] status    Status of the operation: `termina__error__none`, or
 *                       the error code of the list.
 */
void termina__posix__task__insert_ready(const termina__id_t task_id, 
                                const termina__task_prio_t priority,
                                termina__error_code_t * const status);

/**
 * @brief Starts the scheduler.
 * 
 * The main task calls this function to start the scheduler. The function
 * resumes the first task and suspends the main task until it receives the
 * reboot signal, `SIGUSR1`, upon which the function returns.
 */
void termina__posix__task__start_scheduler(void);

/**
 * @brief Yields the processor to the next task.
 * 
 * The scheduler selects the next task; the current task is suspended and the
 * next task is resumed.
 */
void termina__posix__task__yield(void);

/**
 * @brief Selects the next task to run and switches to it.
 * 
 * The current task is added to the ready list and the scheduler selects the
 * next task. If the next task differs from the current one, the current task
 * is suspended and the next task is resumed.
 */
void termina__posix__task__schedule(void);

/**
 * @brief Suspends the execution of the current task.
 * 
 * @param[in] current_task  Pointer to the object of the current task.
 */
void termina__posix__task__suspend(termina__posix__task_t * const current_task);


#endif // TERMINA__OS__POSIX__TASK_H__
