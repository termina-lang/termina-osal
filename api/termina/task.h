#ifndef TERMINA__TASK_H__
#define TERMINA__TASK_H__

#include <stdint.h>

#include <termina/types.h>

/* Priorities of the application tasks: 0 is reserved for the runtime and
   255 for the idle task. */
#define TERMINA__TASK__MAXIMUM_PRIORITY 1U
#define TERMINA__TASK__MINIMUM_PRIORITY 254U
#define TERMINA__TASK__IDLE_PRIORITY 255U
#define TERMINA__TASK__NUMBER_OF_PRIORITIES (TERMINA__TASK__IDLE_PRIORITY + 1U)

/**
 * \brief Type of the task priority.
 */
typedef uint32_t termina__task_prio_t;

/**
 * \brief Type of the task entry function.
 */
typedef void (*termina__task_entry_t)(void * const);

/**
 * \brief Initializes a task.
 *
 * @param[in]   task_id  the identifier of the task. 
 * @param[out]  status   Success if OK or an error otherwise.
 */
void termina__task__init(const termina__id_t task_id,
                          const termina__task_prio_t priority,
                          const size_t stack_size,
                          termina__task_entry_t entry,
                          void * arg,
                          termina__error_code_t * const status);

/**
 * \brief Sets the current priority of the calling task.
 *
 * The priority is the one of an application task, from
 * TERMINA__TASK__MAXIMUM_PRIORITY to TERMINA__TASK__MINIMUM_PRIORITY - 1. The
 * function must not be called while the task holds a mutex.
 *
 * @param[in]   priority  the new priority of the task.
 * @param[out]  status    Success if OK or an error otherwise.
 */
void termina__task__set_current_priority(const termina__task_prio_t priority,
                                         termina__error_code_t * const status);

/**
 * \brief Brings the current priority of the calling task back to the one it
 *        was created with.
 *
 * The function must not be called while the task holds a mutex.
 *
 * @param[out]  status  Success if OK or an error otherwise.
 */
void termina__task__reset_priority(termina__error_code_t * const status);

#endif // TERMINA__TASK_H__
