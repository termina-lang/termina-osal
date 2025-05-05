#ifndef __TERMINA__SHARED__TASK_H__
#define __TERMINA__SHARED__TASK_H__

#include "config.h"

#include <termina.h>

/**
 * \brief Termina task initialization data structure. 
 * 
 * This structure is used to store task data that is defined by the application
 * architecture itself and known at compile time. The transpiler will generate an
 * instance of this structure for each of the application tasks.
 */
typedef struct {

    //! Identifier of the task
    __termina_id_t task_id;

    //! The priority of the task
    __termina_task_prio_t priority;

    //! Stack size
    size_t stack_size;

    //! Entry function of the task
    __termina_task_entry_t entry;

    //! Pointer to the task's data structure that will be passed as argument
    void * arg;

} __termina_shared_task_t;

extern __termina_shared_task_t __shared_app_task_object_table[__TERMINA_APP_CONFIG_TASKS];

/**
 * \brief Get the task object from the task id.
 *
 * This function returns the task object from the task id. It assumes that the
 * task id is valid, i.e., it is less than the number of tasks defined in the
 * application.
 *
 * @param[in] task_id the task id.
 *
 * @return a pointer to the task object.
 */
static inline __termina_shared_task_t * __termina_shared_task__get_task(
        const __termina_id_t task_id) {
    
    return &__shared_app_task_object_table[task_id];

}

/**
 * \brief Get the priority of a task.
 * 
 * This function returns the priority of a task. The function assumes
 * that the task id is valid, i.e., it is less than the number of tasks
 * defined in the application.
 * 
 * @param[in] task_id the task id.
 * 
 * @return the priority of the task.
 */
static inline __termina_task_prio_t __termina_shared_task__get_priority(
        const __termina_id_t task_id) {
    
    return __shared_app_task_object_table[task_id].priority;

}

/**
 * \brief Initializes a task.
 * 
 * This function shall be implemented for the underlying operating system.
 *
 * @param[in]   task_id  the identifier of the task. 
 * @param[out]  status   Zero if OK or another value in case of error.
 */
void __termina_os_task__init(const __termina_id_t task_id,
                             int32_t * const status); 

#endif // __TERMINA__SHARED__TASK_H__
