#ifndef TERMINA__OS__POSIX__TASK_H__
#define TERMINA__OS__POSIX__TASK_H__

#include "config.h"

#include <termina.h>
#include <termina/shared/task.h>
#include <termina/os/posix/signal.h>

#include <pthread.h>

#define TERMINA__POSIX__ID_IDLE_TASK TERMINA__ID__INVALID

typedef struct {

    pthread_t pthread;
    pthread_mutex_t resume_mutex;
    pthread_cond_t resume_cond;
    _Bool resume_task;

    termina__task_prio_t current_priority;

} termina__posix__task_t;

extern termina__id_t termina__posix__current_task_id;
extern termina__posix__task_t termina__posix__idle_task;

extern pthread_t termina__posix__main_task_pthread;

extern _Bool termina__posix__task__disable_scheduling;

/**
 * \brief The task object table.
 * 
 * This table contains the task objects for all the tasks defined in the application.
 * The table is indexed by the task id. The table includes an extra task object
 * for the idle task.
 */
extern termina__posix__task_t termina__posix__app_task_object_table[TERMINA__SHARED__TASK_TABLE_SIZE];

/**
 * \brief Get the POSIX-specific task object from the task id.
 * 
 * This function returns the POSIX-specific task object from the task id. It assumes that the
 * task id is valid, i.e., it is less than the number of tasks defined in the application.
 * 
 * @param task_id the task id.
 * 
 * @return a pointer to the POSIX-specific task object.
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
 * \brief Get the current (instant) priority of a task.
 * 
 * This function returns the priority of a task. The function assumes
 * that the task id is valid, i.e., it is less than the number of tasks
 * defined in the application.
 * 
 * @param[in] task_id the task id.
 * 
 * @return the current priority of the task.
 */
static inline termina__task_prio_t termina__posix__task__get_current_priority(const termina__id_t task_id) {

    termina__task_prio_t prio = 0;

    if (TERMINA__POSIX__ID_IDLE_TASK == task_id) {
        prio = TERMINA__TASK__MINIMUM_PRIORITY;
    } else {
        prio = termina__posix__app_task_object_table[task_id].current_priority;
    }

    return prio;

}

/**
 * \brief Initializes the scheduling mechanism.
 * 
 * This function must be called from the platform code to initialize the scheduling
 * mechanism. It must be called before calling the application-specific
 * initialization function.
 */
void termina__posix__task__init_scheduler(int32_t * const status);

/**
 * \brief Inserts a task in the ready queues.
 *
 * This function inserts a task in the ready queues. The task is inserted at the
 * end of the queue corresponding to its priority.
 * 
 * @param[in]  task_id   the identifier of the task to insert.
 * @param[in]  priority  the priority of the task.
 * @param[out] status    Zero if OK, another value in case of error.
 */
void termina__posix__task__insert_ready(const termina__id_t task_id, 
                                const termina__task_prio_t priority,
                                int32_t * const status);

/**
 * \brief Start task scheduler.
 * 
 * This function must be called from the main task to start the task scheduler.
 * It will schedule the first task to be executed and suspend the execution 
 * of the main task. If the function returns, it means that the 
 */
void termina__posix__task__start_scheduler(void);

/**
 * \brief Yields the processor to the next task.
 * 
 * This function is called by the task to yield the processor to the next task.
 * The next task is selected by the scheduler. The current task is suspended and
 * the next task is resumed.
 */
void termina__posix__task__yield(void);

/**
 * \brief Finds the next task to execute and schedules it.
 * 
 * The current task is added to the ready list and the next task is selected
 * by the scheduler. If the next task is different from the current task, the
 * current task is suspended and the next task is resumed.
 */
void termina__posix__task__schedule(void);

/**
 * \brief Suspends the execution of the current task.
 * 
 * @param[in] current_task the structure corresponding to the current task.
 */
void termina__posix__task__suspend(termina__posix__task_t * const current_task);


#endif // TERMINA__OS__POSIX__TASK_H__
