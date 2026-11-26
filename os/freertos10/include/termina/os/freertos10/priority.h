/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Conversion of the Termina task priorities to FreeRTOS priorities.
 */

#ifndef TERMINA__OS__FREERTOS10__PRIORITY_H__
#define TERMINA__OS__FREERTOS10__PRIORITY_H__

#include <termina.h>

#include <FreeRTOS.h>

/**
 * @brief Converts a Termina priority to a FreeRTOS priority.
 *
 * The order is inverted: 0 is the highest priority in Termina, and
 * `configMAX_PRIORITIES` - 1 is the highest in FreeRTOS. Application tasks use
 * 1 to 254.
 *
 * @param[in] priority  Termina priority.
 *
 * @return The FreeRTOS priority.
 */
static inline UBaseType_t termina__freertos__task__priority_to_freertos(termina__task_prio_t priority) {

	return (UBaseType_t) (configMAX_PRIORITIES - 1U) - (UBaseType_t) priority;

}

#endif // TERMINA__OS__FREERTOS10__PRIORITY_H__