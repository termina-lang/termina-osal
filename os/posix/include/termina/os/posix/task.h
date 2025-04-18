#ifndef __TERMINA__OS__POSIX__TASK_H__
#define __TERMINA__OS__POSIX__TASK_H__

#include "config.h"

#include <termina.h>
#include <termina/os/posix/signal.h>

#include <pthread.h>

#define __POSIX_ID_IDLE_TASK __TERMINA_ID_INVALID

typedef struct {

    pthread_t pthread;
    pthread_mutex_t resume_mutex;
    pthread_cond_t resume_cond;
    _Bool resume_task;

    __termina_task_prio_t current_priority;

} __posix_task_t;

extern __termina_id_t __posix_current_task_id;
extern __posix_task_t __posix_idle_task;

extern pthread_t __posix_main_task_pthread;

extern _Bool __posix_task__disable_scheduling;

/**
 * \brief The task object table.
 * 
 * This table contains the task objects for all the tasks defined in the application.
 * The table is indexed by the task id. The table includes an extra task object
 * for the idle task.
 */
extern __posix_task_t __posix_app_task_object_table[__TERMINA_APP_CONFIG_TASKS];

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
static inline __posix_task_t * __posix_task__get_task(const __termina_id_t task_id) {

    __posix_task_t * task = NULL;

    if (__POSIX_ID_IDLE_TASK == task_id) {
        task = &__posix_idle_task;
    } else {
        task = &__posix_app_task_object_table[task_id];
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
static inline __termina_task_prio_t __posix_task__get_current_priority(const __termina_id_t task_id) {

    __termina_task_prio_t prio = 0;

    if (__POSIX_ID_IDLE_TASK == task_id) {
        prio = __TERMINA_TASK_MINIMUM_PRIORITY;
    } else {
        prio = __posix_app_task_object_table[task_id].current_priority;
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
void __posix_task__init_scheduler(Status * const status);

/**
 * \brief Inserts a task in the ready queues.
 *
 * This function inserts a task in the ready queues. The task is inserted at the
 * end of the queue corresponding to its priority.
 * 
 * @param[in] task_id the identifier of the task to insert.
 * @param[in] priority the priority of the task.
 * @param[out] status Success if OK, error otherwise.
 */
void __posix_task__insert_ready(const __termina_id_t task_id, 
                                const __termina_task_prio_t priority,
                                Status * const status);

/**
 * \brief Start task scheduler.
 * 
 * This function must be called from the main task to start the task scheduler.
 * It will schedule the first task to be executed and suspend the execution 
 * of the main task. If the function returns, it means that the 
 */
void __posix_task__start_scheduler(void);

/**
 * \brief Yields the processor to the next task.
 * 
 * This function is called by the task to yield the processor to the next task.
 * The next task is selected by the scheduler. The current task is suspended and
 * the next task is resumed.
 */
void __posix_task__yield(void);

/**
 * \brief Finds the next task to execute and schedules it.
 * 
 * The current task is added to the ready list and the next task is selected
 * by the scheduler. If the next task is different from the current task, the
 * current task is suspended and the next task is resumed.
 */
void __posix_task__schedule(void);

/**
 * \brief Suspends the execution of the current task.
 * 
 * @param[in] current_task the structure corresponding to the current task.
 */
void __posix_task__suspend(__posix_task_t * const current_task);


#endif // __TERMINA__OS__POSIX__TASK_H__