/**
 * @file
 * @ingroup termina__osal__shared
 *
 * @brief Table of the tasks and the task operations that each operating
 *        system implements.
 */

#ifndef TERMINA__SHARED__TASK_H__
#define TERMINA__SHARED__TASK_H__

#include "config.h"

#include <termina.h>

#include <stdbool.h>

/**
 * @brief Initialization data of a task.
 * 
 * The structure stores the task data that the architecture of the application
 * defines and that is known at compile time. The transpiler generates an
 * instance of this structure for each task of the application.
 */
typedef struct {

    //! Identifier of the task.
    termina__id_t task_id;

    //! Priority of the task.
    termina__task_prio_t priority;

    //! Size of the stack in bytes.
    size_t stack_size;

    //! Entry function of the task.
    termina__task_entry_t entry;

    //! Pointer to the data structure of the task, which the entry function
    //! receives as argument.
    void * arg;

} termina__shared__task_t;

#ifndef TERMINA__APP_CONFIG__TASKS
#error "config.h must define TERMINA__APP_CONFIG__TASKS"
#else
#if (TERMINA__APP_CONFIG__TASKS > 0)

/**
 * @brief Size of the task object tables.
 */
#define TERMINA__SHARED__TASK_TABLE_SIZE TERMINA__APP_CONFIG__TASKS

/**
 * @brief Checks whether a task identifier is valid.
 *
 * @param[in] task_id  Identifier of the task.
 *
 * @return True if the identifier is less than the number of tasks of the
 *         application, false otherwise.
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

/** @brief Table of the tasks, indexed by identifier. */
extern termina__shared__task_t termina__shared__task_object_table[TERMINA__SHARED__TASK_TABLE_SIZE];

/**
 * @brief Gets the task object of a task identifier.
 *
 * The identifier must be valid, that is, less than the number of tasks of the
 * application.
 *
 * @param[in] task_id  Identifier of the task.
 *
 * @return Pointer to the task object.
 */
static inline termina__shared__task_t * termina__shared__task__get_task(
        const termina__id_t task_id) {
    
    return &termina__shared__task_object_table[task_id];

}

/**
 * @brief Gets the priority of a task.
 * 
 * The identifier must be valid, that is, less than the number of tasks of the
 * application.
 * 
 * @param[in] task_id  Identifier of the task.
 * 
 * @return The priority of the task.
 */
static inline termina__task_prio_t termina__shared__task__get_priority(
        const termina__id_t task_id) {
    
    return termina__shared__task_object_table[task_id].priority;

}

/**
 * @brief Creates a task in the operating system.
 * 
 * Each operating system implements this function.
 *
 * @param[in]   task_id  Identifier of the task.
 * @param[out]  status   Status of the operation: `termina__error__none`, or
 *                       the error code of the back-end.
 */
void termina__os__task__init(const termina__id_t task_id,
                             termina__error_code_t * const status);

/**
 * @brief Gets the identifier of the calling task.
 *
 * @return The identifier of the task, or `TERMINA__ID__INVALID` when the
 *         caller is not an application task.
 */
termina__id_t termina__os__task__current_id(void);

/**
 * @brief Sets the current priority of the calling task in the operating
 *        system.
 *
 * @param[in]   priority  New priority of the task.
 * @param[out]  status    Status of the operation: `termina__error__none`, or
 *                        the error code of the back-end.
 */
void termina__os__task__set_current_priority(const termina__task_prio_t priority,
                                             termina__error_code_t * const status);

#endif // TERMINA__SHARED__TASK_H__
