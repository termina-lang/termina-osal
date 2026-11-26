/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Lookup of the Termina tasks by their RTEMS identifier.
 */

#ifndef TERMINA__OS__RTEMS__TASK_H__
#define TERMINA__OS__RTEMS__TASK_H__

#include <termina.h>

#include <rtems.h>

/**
 * @brief Finds the Termina task created with a given RTEMS identifier.
 *
 * @param[in] rtems_task_id  Identifier of the task in RTEMS.
 *
 * @return The identifier of the task, or `TERMINA__ID__INVALID` when no
 *         application task has that RTEMS identifier.
 */
termina__id_t termina__rtems__task__find_task(const rtems_id rtems_task_id);

#endif // TERMINA__OS__RTEMS__TASK_H__
