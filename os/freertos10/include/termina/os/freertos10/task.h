/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Lookup of the Termina tasks by their FreeRTOS handle.
 */

#ifndef TERMINA__OS__FREERTOS10__TASK_H__
#define TERMINA__OS__FREERTOS10__TASK_H__

#include <termina.h>

#include <FreeRTOS.h>
#include <task.h>

/**
 * @brief Finds the Termina task created with a given FreeRTOS handle.
 *
 * @param[in] handle  Handle of the task in FreeRTOS.
 *
 * @return The identifier of the task, or `TERMINA__ID__INVALID` when no
 *         application task has that handle.
 */
termina__id_t termina__freertos__task__find_task(const TaskHandle_t handle);

#endif // TERMINA__OS__FREERTOS10__TASK_H__
