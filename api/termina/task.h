#ifndef __TERMINA__TASK_H__
#define __TERMINA__TASK_H__

#include <stdint.h>

#include <termina/types.h>

#define __TERMINA_TASK_MINIMUM_PRIORITY 255
#define __TERMINA_TASK_NUMBER_OF_PRIORITIES (__TERMINA_TASK_MINIMUM_PRIORITY + 1)

/**
 * \brief Type of the task priority.
 */
typedef uint8_t __termina_task_prio_t;

/**
 * \brief Type of the task entry function.
 */
typedef void (*__termina_task_entry_t)(void * const);

/**
 * \brief Initializes a task.
 *
 * @param[in]   task_id  the identifier of the task. 
 * @param[out]  status   Success if OK or an error otherwise.
 */
void __termina_task__init(const __termina_id_t task_id,
                          __termina_task_prio_t priority,
                          size_t stack_size,
                          __termina_task_entry_t entry,
                          void * arg,
                          Status * const status); 

#endif // __TERMINA__TASK_H__