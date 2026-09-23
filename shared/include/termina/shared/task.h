#ifndef TERMINA__SHARED__TASK_H__
#define TERMINA__SHARED__TASK_H__

#include "config.h"

#include <termina.h>

#include <stdbool.h>

/**
 * \brief Termina task initialization data structure.
 * 
 * This structure is used to store task data that is defined by the application
 * architecture itself and known at compile time. The transpiler will generate an
 * instance of this structure for each of the application tasks.
 */
typedef struct {

    //! Identifier of the task
    termina__id_t task_id;

    //! The priority of the task
    termina__task_prio_t priority;

    //! Stack size
    size_t stack_size;

    //! Entry function of the task
    termina__task_entry_t entry;

    //! Pointer to the task's data structure that will be passed as argument
    void * arg;

} termina__shared__task_t;

#ifndef TERMINA__APP_CONFIG__TASKS
#error "config.h must define TERMINA__APP_CONFIG__TASKS"
#else
#if (TERMINA__APP_CONFIG__TASKS > 0)

/**
 * \brief Size of the task object tables.
 */
#define TERMINA__SHARED__TASK_TABLE_SIZE TERMINA__APP_CONFIG__TASKS

/**
 * \brief Checks whether a task identifier is valid.
 *
 * @param[in] task_id the task id.
 *
 * @return true if the identifier is less than the number of tasks defined in
 *         the application, false otherwise.
 */
static inline bool termina__shared__task__is_valid_id(const termina__id_t task_id) {
    return (task_id < TERMINA__APP_CONFIG__TASKS);
}

#else

// The application defines no tasks. ISO C does not allow arrays of size zero,
// so the tables keep one unused element, and no identifier is valid.
#define TERMINA__SHARED__TASK_TABLE_SIZE 1U

static inline bool termina__shared__task__is_valid_id(const termina__id_t task_id) {
    (void)task_id;
    return false;
}

#endif
#endif

extern termina__shared__task_t termina__shared__task_object_table[TERMINA__SHARED__TASK_TABLE_SIZE];

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
static inline termina__shared__task_t * termina__shared__task__get_task(
        const termina__id_t task_id) {
    
    return &termina__shared__task_object_table[task_id];

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
static inline termina__task_prio_t termina__shared__task__get_priority(
        const termina__id_t task_id) {
    
    return termina__shared__task_object_table[task_id].priority;

}

/**
 * \brief Initializes a task.
 * 
 * This function shall be implemented for the underlying operating system.
 *
 * @param[in]   task_id  the identifier of the task. 
 * @param[out]  status   Zero if OK or another value in case of error.
 */
void termina__os__task__init(const termina__id_t task_id,
                             int32_t * const status); 

#endif // TERMINA__SHARED__TASK_H__
