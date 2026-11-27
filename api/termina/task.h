/**
 * @file
 * @ingroup termina__osal__api
 *
 * @brief Interface of the tasks and of their priorities.
 */

#ifndef TERMINA__TASK_H__
#define TERMINA__TASK_H__

#include <stdint.h>

#include <termina/types.h>

/* Priorities of the tasks: 0 is reserved for the runtime, 254 for the test
   cases of a test build and 255 for the idle task. */
/** @brief Highest priority of an application task. */
#define TERMINA__TASK__MAXIMUM_PRIORITY 1U
/** @brief Priority immediately below the lowest one of an application task,
 *         which is TERMINA__TASK__MINIMUM_PRIORITY - 1. */
#define TERMINA__TASK__MINIMUM_PRIORITY 254U
/** @brief Priority of the idle task. */
#define TERMINA__TASK__IDLE_PRIORITY 255U
/** @brief Number of task priorities. */
#define TERMINA__TASK__NUMBER_OF_PRIORITIES (TERMINA__TASK__IDLE_PRIORITY + 1U)

/**
 * @brief Type of the task priority.
 */
typedef uint32_t termina__task_prio_t;

/**
 * @brief Type of the task entry function.
 */
typedef void (*termina__task_entry_t)(void * const);

/**
 * @brief Initializes a task.
 *
 * @param[in]   task_id     Identifier of the task.
 * @param[in]   priority    Priority of the task.
 * @param[in]   stack_size  Size of the stack of the task in bytes.
 * @param[in]   entry       Entry function of the task.
 * @param[in]   arg         Argument that the entry function receives.
 * @param[out]  status      Status of the operation: `termina__error__none`,
 *                          or `termina__error__task_init` if the identifier
 *                          is out of range or the task cannot be created.
 */
void termina__task__init(const termina__id_t task_id,
                          const termina__task_prio_t priority,
                          const size_t stack_size,
                          termina__task_entry_t entry,
                          void * arg,
                          termina__error_code_t * const status);

/**
 * @brief Sets the current priority of the calling task.
 *
 * The priority is the one of an application task, from
 * `TERMINA__TASK__MAXIMUM_PRIORITY` to `TERMINA__TASK__MINIMUM_PRIORITY` - 1.
 * The function must not be called while the task holds a mutex.
 *
 * @param[in]   priority  New priority of the task.
 * @param[out]  status    Status of the operation: `termina__error__none`,
 *                        `termina__error__invalid_priority`, or the error
 *                        code that the back-end returns.
 */
void termina__task__set_current_priority(const termina__task_prio_t priority,
                                         termina__error_code_t * const status);

/**
 * @brief Restores the current priority of the calling task to the one it was
 *        created with.
 *
 * The function must not be called while the task holds a mutex.
 *
 * @param[out]  status  Status of the operation: `termina__error__none`,
 *                      `termina__error__invalid_id` if the caller is not an
 *                      application task, or the error code that the back-end
 *                      returns.
 */
void termina__task__reset_priority(termina__error_code_t * const status);

#endif // TERMINA__TASK_H__
